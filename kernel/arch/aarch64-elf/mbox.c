
#include <libk.h>
#include <printf.h>

#include <arch/mbox.h>
#include <arch/baseIO.h>

#define MBOX_LEN 8


// Mailboxen
enum {
    VIDEOCORE_MBOX_0 = MMIO_BASE+0x0000B880,
    VIDEOCORE_MBOX_1 = MMIO_BASE+0x0000B880 + 0x20,
    
};

// Register innerhalb der Mailbox
enum {
    MBOX_READ   = 0x00,
    MBOX_POLL   = 0x10,
    MBOX_SENDER = 0x14,
    MBOX_STATUS = 0x18,
    MBOX_CONFIG = 0x1c,    
};

// Zustände Statusregister
enum {
    MBOX_REQUEST = 0,
    MBOX_FULL   = 0x80000000,
    MBOX_EMPTY  = 0x40000000,
    MBOX_RESPONSE = 0x80000000
};

volatile uint32_t __attribute__((aligned(16))) mbox[ MBOX_LEN ];
uint8_t mac[6];

int mbox_call(unsigned char channel, volatile uint32_t* mbox) {
    /* Speicher muss auf 16 byte ausgerichtet sein, da 
     * die niedrigeren 4 bit für den Kanal reserviert sind. */    
    if ((unsigned long) mbox &  0xf) {
        abort();    
    }
    
    // was wollen wir schreiben? 
    uint32_t request = ( (unsigned long) mbox & ~(0xF)) | (channel & 0xF);
    //printf("reqeust: %08x ", request);
    // warten, bis das Register frei ist
    while ( get64 (VIDEOCORE_MBOX_0 + MBOX_STATUS) & MBOX_FULL)
        asm volatile("nop");
    // Daten absetzen
    put64( VIDEOCORE_MBOX_1 + MBOX_READ, request);
    //printf("was written\n");
    
    while (1) {
      //  printf("waiting for response\n");
        // Warten auf eine Antwort
        while ( get64 (VIDEOCORE_MBOX_0 + MBOX_STATUS) & MBOX_EMPTY)
            asm volatile("nop");
        
        uint32_t response = get64(VIDEOCORE_MBOX_0 + MBOX_READ);
        //printf("response was: %08x\n", response);    
        
        // Ist dies unsere Antwort? (Wenn gleiche Adresse wie unser Request)
        if (request == response) {   
            return mbox[1] == MBOX_RESPONSE;
        }
    }
    return 0;
}

void showmbox() {
    printf("\ncontent of mailbox:\n");
    for (int i=0; i < MBOX_LEN; i++)
        printf("mbox[%02x]: 0x%08x\n", i, mbox[i]);
}

void clear_mbox() {
    for (int i=0; i < MBOX_LEN; i++)
        mbox[i] = 0;
}

uint32_t mbox_get_boardmodel() {
    clear_mbox();
    
    mbox[0] = 7*4;
    //mbox[1] = MBOX_REQUEST; // von clean noch 0
    mbox[2] = MBOX_TAG_GETBOARDMODEL;
    mbox[3] = mbox[4] = 4;

    mbox_call(MBOX_CH_PROP, mbox);

    //showmbox();    
    return mbox[5];
}

uint32_t mbox_get_boardrevision() {
    clear_mbox();
    
    mbox[0] = 7*4;
    //mbox[1] = MBOX_REQUEST; // von clean noch 0
    mbox[2] = MBOX_TAG_GETBOARDREVISION;
    mbox[3] = mbox[4] = 4;

    mbox_call(MBOX_CH_PROP, mbox);

    //showmbox();    
    return mbox[5];
}

const uint8_t* mbox_get_boardmac() {
    clear_mbox();
    
    mbox[0] = 8*4;
    //mbox[1] = MBOX_REQUEST; // von clean noch 0
    mbox[2] = MBOX_TAG_GETBOARDMAC;
    mbox[3] = mbox[4] = 6;

    mbox_call(MBOX_CH_PROP, mbox);

    //showmbox();    

    mac[0] = mbox[5];
    mac[1] = mbox[5] >> 8;
    mac[2] = mbox[5] >> 16;
    mac[3] = mbox[5] >> 24;
    mac[4] = mbox[6];
    mac[5] = mbox[6] >> 8;

    return (const uint8_t*) mac;
}

uint64_t mbox_get_Serial() {    
    clear_mbox();

    mbox[0] = 8*4;                  // Nachricht Länge
    mbox[1] = MBOX_REQUEST;         // Dies ist eine Anfrage    
    mbox[2] = MBOX_TAG_GETSERIAL;   // Wir wollen die Seriennummer haben
    mbox[3] = mbox[4] = 8;

    mbox_call(MBOX_CH_PROP, mbox);

    return mbox[6] << 32 + mbox[5];
}