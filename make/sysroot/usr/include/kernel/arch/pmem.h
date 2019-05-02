#ifndef ARCH_PMEM_H
#define ARCH_PMEM_H 1

enum alloc_type {
    PMEM_ALLOC_DEFAULT  = 0x00,
    PMEM_ALLOC_DMA      = 0x01
};



void pmem_init();


void* pmem_alloc( int alloc_type );
void pmem_free( void* adress);

#endif