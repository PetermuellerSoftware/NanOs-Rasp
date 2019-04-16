#ifndef ARCH_BASEIO_H
#define ARCHL_BASEIO_H 1

#include <stdint.h>

// Diese Funktionen werden derart oft genutzt, dass sie inline
// also ohne weiteren overhead definiert werden.

inline volatile unsigned int get64 (volatile unsigned int port) 
{
    return *(volatile unsigned int *) port;
}

inline void put64( volatile unsigned int port, volatile unsigned int value) 
{
    *(volatile unsigned int *) port = value;
}

inline void delay(uint16_t cycles)  
{
    for(uint16_t i=0; i< cycles; i++)
        asm volatile("nop");
}

#endif
