

#include <arch/delay.h>
#include <arch/gpfio.h>
#include <arch/baseIO.h>

#include <printf.h>

#define SYSTMR_LO (MMIO_BASE+0x00003004)
#define SYSTMR_HI (MMIO_BASE+0x00003008)

void wait_cycles(int cycles) {
    if (cycles) 
        while(cycles--)
            asm volatile ("nop");
}


void wait_msec(unsigned int n)
{
    register unsigned long f, t, r;
    // hole die aktuelle Frequenz
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // hole den aktuellen Zählwert
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // Berechne den Schwellwert 
    t+=((f/1000)*n)/1000;
    do{asm volatile ("mrs %0, cntpct_el0" : "=r"(r));}while(r<t);
}


// geht nicht unter qemu
unsigned long get_system_timer()
{
    unsigned int h=-1, l;
    // 2 mal einzelne 32 bit einlesen
    h=get64(SYSTMR_HI);
    l=get64(SYSTMR_LO);
    // falls gerade der höhere Wert nachgestellt wurde, nochmal lesen
    if(h!=get64(SYSTMR_HI)) {
        h=get64(SYSTMR_HI);
        l=get64(SYSTMR_LO);
    }
    // zusammen setzen
    return ((unsigned long) h << 32) | l;
}

/**
 * Wait N microsec (with BCM System Timer)
 */
void wait_msec_st(unsigned int n)
{
    // nur, wenn wir einen Wert vom Timer bekommen, da sonst 
    // unter qemu alles endlos laufen würde.   
    #ifndef __qemu
        unsigned long t=get_system_timer();
        while(get_system_timer() < t+n);
    #else
        wait_msec(n);
    #endif
}