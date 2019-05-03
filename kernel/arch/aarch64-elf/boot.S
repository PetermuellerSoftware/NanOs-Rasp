

// Wir benötigen einen definierten Einsprungpunkt, der linker erzeugt unser Image so,
// das diese Section direkt auf 0x08000 geladen wird


.global _start
.global _halt

.section ".text.boot"
_start:
    
    // Andere Kerne werden vorerst abgeschaltet
    mrs x5, mpidr_el1           // wir holen das multi processor affinity register
    and x5, x5, #0x03           // reduzieren auf die bits 0 und 1
    cbz x5,master

_halt:
    wfe
    b _halt
        
master:
    // ändere den ExecutionLevel auf EL1
    bl      gtEl1

    // Stack einrichten: dieser wächst nach unten und wird 
    // erst dekrementiert, dann beschrieben, daher ist _start eine 
    // sichere Adresse für unseren ersten Stack
    ldr x1, =_start              // Adresse von Start zu r5
    mov sp, x1                  
    
    // bss mit 0 initialisieren
        
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, 4f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b
    
    // Kernel Init ist der erste Aufruf an eine C-Funktion
4:  bl kernel_init

    b       _halt
