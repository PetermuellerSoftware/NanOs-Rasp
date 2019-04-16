#ifndef ARCH_BASEIO_H
#define ARCHL_BASEIO_H 1

#include <stdint.h>

// Diese Funktionen werden derart oft genutzt, dass sie inline
// also ohne weiteren overhead definiert werden.

inline volatile uint64_t get64 (volatile int64_t port) 
{
    return *(volatile uint64_t *) port;
}

inline void put64( volatile uint64_t port, volatile uint64_t value) 
{
    *(volatile uint64_t *) port = value;
}

inline void delay(uint16_t cycles)  
{
    for(uint16_t i=0; i< cycles; i++)
        asm volatile("nop");
}

#endif
