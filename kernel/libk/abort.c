





#include <stdint.h>
#include <printf.h>

extern uint32_t* _start;
extern void _halt();

void abort() {    
    
    // Nachricht nach außen geben
    printf("Abort im Kernel aufgerufen. Es folgt die Ausgabe des Stacks:\n");
    
    // Geben wir noch den Stack aus, so gut uns das möglich ist.         
    // Dazu holen wir den aktuellen Stack Pointer
    uint32_t* sp;     
    asm volatile ( "mov %0, sp" :
                   "=r" (sp):
                   :
                   );
    int tab=0;
    while (sp < &_start)
    {
        printf("%x: 0x%08x\t", sp, *sp);
        sp++;
        if(++tab >=4) {
            tab=0;
            printf("\n");
        }
    };
    
    printf("Kern wird gestoppt!\n");
    
    // Kern anhalten
    _halt();
};

