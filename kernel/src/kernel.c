

/**
 * @file kernel.c
 * @brief Kernel c-Hauptdatei
 * 
 * c-Hauptdatei für die Initialisierung der Kernel
 */


#include <arch/init.h>
#include <arch/kuart.h>
#include <arch/mbox.h>
#include <printf.h>
#include <stdint.h>
#include <libk.h>


/**
 * @brief kernel Einsprungpunkt
 * 
 * Dient als Einsprungpunkt für die Initialisierung der Kernel,
 * darf erst nach initialisieren der Umgebung für c-Code 
 * gerufen werden.
 */
#if __clpusplus 
EXTERN "C" 
#endif 
void kernel_init() {
    
    initialize_arch();

    printf( "Hallo Welt, hier ist die NanOs Kernel!\n");

    
    // Endlose schleife, alles einkommende direkt zurück senden
    while (1)
        uart_send( uart_recv());
}