
#include <arch/kuart.h>

#if __clpusplus 
EXTERN "C" 
#endif 
void kernel_init() {
    uart_init();
    
    uart_sends( "Hallo Welt, hier ist die NanOs Kernel!\n");
    
    
    
    // Endlose schleife, alles einkommende direkt zurück senden
    while (1)
        uart_send( uart_recv());
}