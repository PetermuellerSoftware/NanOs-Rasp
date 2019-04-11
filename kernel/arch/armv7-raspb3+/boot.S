
.syntax unified

// Wir benötigen einen definierten Einsprungpunkt, der linker erzeugt unser Image so,
// das diese Section direkt auf 0x08000 geladen wird
.section .text.boot

.global _start
    //.org 0x8000
_start:
    
    // Andere Kerne werden vorerst abgeschaltet
//    mrs r0, mpidr_el1         // wir holen das multi processor affinity register
    mrc p15, 0, r5, c0, c0, 5
    and r5, r5, #0xff             // reduzieren auf die bits 0 und 1
    cbz r5,master
    cmp r5, #0                  // und nutzen nur den Prozessor 0
    bne halt                      

    // Stack einrichten: dieser wächst nach unten und wird 
    // erst dekrementiert, dann beschrieben, daher ist _start eine 
    // sichere Adresse für unseren ersten Stack
master:
    ldr r5, _start              // Adresse von Start zu r5
    mov sp, r5                  
    
    // Kernel Init ist der erste Aufruf an eine C-Funktion
    // Die Register r0, r1 und r2 sollten bis hier nicht verändert 
    // sein, da sie boot-informationen enthalten
    b kernel_init;

halt:
    wfe
    b halt
