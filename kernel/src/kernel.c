
#include <arch/kuart.h>
#include <arch/mbox.h>
#include <printf.h>
#include <stdint.h>
#include <libk.h>

extern void initialize_arch();

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