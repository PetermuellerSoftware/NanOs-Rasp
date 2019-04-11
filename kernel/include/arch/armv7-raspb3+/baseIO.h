#ifndef ARCH_BASEIO_H
#define ARCHL_BASEIO_H 1

#include <stdint.h>

// Diese Funktionen werden derart oft genutzt, dass sie inline
// also ohne weiteren overhead definiert werden.

inline uint32_t get32 ( uint32_t port) 
{
    return *(volatile uint32_t*) port;
}

inline void put32( uint32_t port, uint32_t value) 
{
    *(volatile uint32_t*) port = value;
}

inline void delay(uint16_t cycles)  
{
    for(uint16_t i=0; i< cycles; i++);
}

#endif
