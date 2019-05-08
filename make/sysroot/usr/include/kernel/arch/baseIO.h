/** 
 * @file aarch64-elf/baseIO.h
 * 
 * @brief grundlegende I/O
 * 
 * definiert Funktionen für den Zugriff auf die 
 * Speicher-gemappten Ports.
 *
 * Diese Funktionen werden derart oft genutzt, dass sie inline
 * also ohne weiteren overhead definiert werden.
 */

#ifndef ARCH_BASEIO_H
#define ARCH_BASEIO_H 1 

#include <stdint.h>

/**
 * @brief holt einen Wert vom definierten Port
 * @param port Port
 * @return Der aktuelle Wert
 */
inline uint64_t get64 (volatile int64_t port) 
{
    return *(volatile uint64_t *) port;
}

/**
 * @brief schreibt einen Wert auf den definierten Port
 * @param port Port
 * @param value Der neue Wert
 */
inline void put64( volatile uint64_t port, volatile uint64_t value) 
{
    *(volatile uint64_t *) port = value;
}

#endif
