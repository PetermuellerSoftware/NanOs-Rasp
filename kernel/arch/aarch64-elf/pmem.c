
#include <libk.h>


#include <stdint.h>
#include <stdbool.h>

#include <printf.h>

#include <arch/mbox.h>
#include <arch/pmem.h>

// Chunk size 4 KiB
#define PMEM_CHUNK_SIZE (1<<12)

// chunk of specified memory adress
#define PMEM_CHUNK(x) (x/PMEM_CHUNK_SIZE)

// byte position of chunk in map
#define PMEM_CHUNK_BYTE(x) (x / 8)

// bit position of chunk in map
#define PMEM_CHUNK_BIT(x) (x % 8)

#define PMEM_MAP_SIZE (2^29 / PMEM_CHUNK_SIZE)


extern void* _kernel_start;
extern void* _kernel_end;

/*************************************
 * Memory map for 4GiB = 4 * 2^30 chunked
 * in 4 Kib = 4 * 2^10, so 2^20 entries left
 * with 8 = 2^3 bits per entry.
 * map size needs to be:
 * 4*2^30/(4*2^10)/8 = 2^20/8 = 2^17
 */
 
uint8_t pmem_map[PMEM_MAP_SIZE];
int max_chunk;

void pmem_init_area(uint32_t fromChunk, uint32_t size, bool free) {
    const uint32_t toChunk = fromChunk + size - 1;
    const int startbyte = PMEM_CHUNK_BYTE(fromChunk);
    const int startbit = PMEM_CHUNK_BIT(fromChunk);
    const int endbyte = PMEM_CHUNK_BYTE(toChunk);
    const int endbit = PMEM_CHUNK_BIT(toChunk);
    const register uint8_t fullbyte = free ? 0xff : 0x0;
    
//    printf("pmem_init_area: von 0x%08x bis 0x%08x\n", fromChunk, toChunk);
//    printf("pmem_init_area: von byte 0x%08x bit %d\n", startbyte, startbit);
//    printf("pmem_init_area: bis byte 0x%08x bit %d\n", endbyte, endbit);
    
    // erste bits auffüllen
    if (startbit) {
//        printf ("erste %d chunks nicht auf 32KiB-Grenze.\n", 8-startbit);
        if (free) {
            for (int bit = startbit; bit < 8; bit++) 
                pmem_map[startbyte] |= (1<<bit);                    
        } else {
            for (int bit = startbit; bit < 8; bit++) 
                pmem_map[startbyte] &= ~(1<<bit);                                
        }
//        printf("startbyte: 0x%02x\n", pmem_map[startbyte]);
    }

    // beginne am Startbyte, oder eines danach, wenn es
    const uint8_t byteOffset = startbit ? 1 : 0;
    int byte = startbyte + byteOffset;
    while (byte < endbyte) {
        pmem_map[byte]=fullbyte;
        byte++;
    }
//    printf("letzte bytes: 0x%02x 0x%02x 0x%02x 0x%02x\n", pmem_map[endbyte-3], pmem_map[endbyte-2], pmem_map[endbyte-1], pmem_map[endbyte]);
    
    if (free) {
        for (int bit = 0; bit <= endbit; bit++) 
            pmem_map[endbyte] |= (1<<bit);                    
    } else {
        for (int bit = 0; bit <= endbit; bit++) 
            pmem_map[endbyte] &= ~(1<<bit);                                
    }
//    printf("endbyte: 0x%02x\n", pmem_map[endbyte]);
//    printf("\n");
}


/*************************************
 * physical memory initialization
 * 
 * initializes the physical memory map, 
 * therefore receives the cpu und gpu 
 * memory sizes and marks kernel
 * memory as used
 * 
 */
 
void pmem_init( ) {
    printf("Physischer Speicher wird initialisiert\n");
    
    // mailbox allgemein
    mbox[0] = 4 * 12;
    mbox[1] = MBOX_REQUEST;
    
    mbox[2] = 0x10005;
    mbox[3] = mbox[4] = 8;
    mbox[5] = 0;
    mbox[6] = 0;
    
    mbox[7] = 0x10006;
    mbox[8] = mbox[9] = 8;
    mbox[10] = 0;
    mbox[11] = 0;
    
    mbox_call(MBOX_CH_PROP, mbox);
    
//    printf("arm ram from \t0x%08x \tsize 0x%08x\n", mbox[5], mbox[6]);
//    printf("vc ram from \t0x%08x \tsize 0x%08x\n", mbox[10], mbox[11]);

//    printf("pmem_chunk_size: 0x%08x\n", PMEM_CHUNK_SIZE);

    // allen erkannten Speicher als verfügabr markieren
    const int memchunks = (mbox[6] + PMEM_CHUNK_SIZE - 1) / PMEM_CHUNK_SIZE;
    pmem_init_area( PMEM_CHUNK(mbox[5]), 
                    memchunks,
                    true);
    const int kernel_start = (int) (uint64_t) &_kernel_start;
    const int kernel_size = ((int) (uint64_t) &_kernel_end) - kernel_start;
    
    // kernel selbst natürlich wieder als belegt flaggen
    const int kernelchunks = (kernel_size + PMEM_CHUNK_SIZE - 1) / PMEM_CHUNK_SIZE;
    pmem_init_area( PMEM_CHUNK( (int) (uint64_t) kernel_start),
                    kernelchunks,
                    false);
                    
    const long availableMemory = (memchunks - kernelchunks) * PMEM_CHUNK_SIZE;
    
    printf("Der ARM hat %s verfügbar.\n", size2str((size_t) availableMemory));
    printf("Der VC  hat %s verfügbar.\n", size2str((size_t) mbox[11]));
}

void* pmem_alloc( int alloc_type) {
    switch (alloc_type) {
        case PMEM_ALLOC_DEFAULT:
            for (int chunk= max_chunk; chunk > 0; chunk++)
                if (pmem_map[PMEM_CHUNK_BYTE(chunk)] & (1 << PMEM_CHUNK_BIT(chunk))) {
                    pmem_map[PMEM_CHUNK_BYTE(chunk)] &= ~(1 << PMEM_CHUNK_BIT(chunk));
                    return (void*) (uint64_t) (chunk << 12);                    
                }
        break;
        case PMEM_ALLOC_DMA:
            abort();
        break;
    }    
} 

void pmem_free (void* address) {
    const int chunk = PMEM_CHUNK( (int) (uint64_t) address);
    pmem_map[PMEM_CHUNK_BYTE(chunk)] |= (1 << PMEM_CHUNK_BIT(chunk));
}