/** @file delay.c
 * @brief Verzögerungen
 * 
 * Definiert diverse Funktionen um anhand von
 * CPU-Zyklen oder Timern zu verzögern.
 */

#include <arch/delay.h>
#include <arch/gpfio.h>
#include <arch/baseIO.h>
#include <printf.h>



/// @brief untere Adresse System Timer SYSTMR
#define SYSTMR_LO (MMIO_BASE+0x00003004)
/// @brief obere Adresse System Timer SYSTMR
#define SYSTMR_HI (MMIO_BASE+0x00003008)



/**
 * @brief Warte für n CPU-Zyklen
 * 
 * Wartet die durch cycles angegebene Anzahl an CPU Zyklen.
 * Dabei wird in aarch64 das NOP Kommando genutzt.
 * 
 * @param cycles Anzahl der zu wartenden Zyklen
 */
void wait_cycles(int cycles) {
    if (cycles) 
        while(cycles--)
            asm volatile ("nop");
}

/**
 * @brief Warte für n Microsekunden
 * 
 * Wartet die eingestellte Zeit in Mikrosekunden, dazu bedient sich die Funktion
 * des Zählerregisters "cntfrq_el0"
 * 
 * @param n die zu wartenden Mikrosekunden
 */
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


/**
 * @brief Aktueller BCM-Systemtimer
 * 
 * Gibt den aktuellen Wert des Systemtimers zurück. Findet gerade ein Überlauf
 * statt, so wird erneut gelesen.
 * 
 * @bug funktioniert nicht innerhalb der qemu Emulation
 * 
 * @return der aktuelle BCM-Systemtimer
 */
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
 * @brief Wartet die eingestellten Mikrosekunden 
 * 
 * Wartet die eingestellte Zeit durch Nutzung des BCM-Timers.
 * 
 * @bug Unter Qemu muss das Compilerflag __qemu gesezt sein, da qemu
 * diesen Timer nicht emuliert. Stattdessen wird dann intern
 * die wait_msec(n) verwendet.
 * 
 * @param n die zu wartenden Mikrosekunden
 */
void wait_msec_st(unsigned int n)
{
    #ifndef __qemu
        unsigned long t=get_system_timer();
        while(get_system_timer() < t+n);
    #else
        wait_msec(n);
    #endif
}