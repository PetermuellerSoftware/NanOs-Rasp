

.global gtEl1



gtEl1:
    mrs     x0, CurrentEL       // bit [3:2] from PSTATE
    and     x0, x0, #12
    
    b       1f
    
    // Sind wir in EL3?
    cmp     x0, #0x0c
    bne     1f
    
    /* scr_el3[0]: NS   non secure      1 processor is non secure
     * scr_ele[1]: IRQ  IRQ handler     0 taken in IRQ mode, 1 in monitor mode
     * scr_ele[2]: FIQ  FIQ handler     0 taken in FIQ mode, 1 in monitor mode
     * scr_ele[3]: EA   external abort  0 taken in abort mode, 1 in monitor mode
     
     * scr_ele[4]: reserved
     * scr_ele[5]: reserved
     * scr_ele[6]: reserved
     * scr_ele[7]: SMD  SMC disabled    0 enabled in El1,2,3,  1 undefined
     
     * scr_ele[8]: HCE   hyper call enable  1 enabled
     * scr_ele[9]: SIF   sec instrc. fetch  1 permitted
     * scr_ele[10]: RW   register width     1 AArch64, 0 AArch32
     * scr_ele[11]: ST   el1 access to ...
     
     * scr_ele[12]: TWI  trap WFI       0 not trapped
     * scr_ele[13]: TWE  trap WFE       0 not trapped   
    */
    mov     x2, #0x05b1
    msr     scr_el3, x2
    
    /*
        spsr_el3[0-3]:  mode to return
        spsr_el3[4]:    return to (0=AArch64)
        spsr_el3[6]:    IRQ mask bit
        spsr_el3[7]:    FIQ mask bit
        spsr_el3[8]:    EA mask bit
        spsr_el3[9]:    DEBUG mask bit
    */    
    mov     x2, #0x03c9
    msr     spsr_el3, x2
    
    // Adresse beim zurück springen
    adr     x2, 1f
    msr     elr_el3, x2
    eret
   
    // Sind wir in EL2, sonst drüber?
1:  cmp     x0, #0x04
    beq     2f
        
    // Stack für EL1
    msr     sp_el2, x1
    
    // Erlaube CNTP für EL1
    mrs     x0, cnthctl_el2
    orr     x0,x0, #0x03
    msr     cnthctl_el2, x0         // set bit 0 and 1
    msr     cntvoff_el2, xzr        // counter virtual offset = 0
    
    // Hypervisor configuration register
    mov     x0, #(1 << 31)      // Erlaube AArch64 auf EL0 und EL1
    orr     x0, x0, #(1 << 1)   // SWIO set way invalidation override
    msr     hcr_el2, x0
    mrs     x0, hcr_el2
    
    // stored process state register für Rücksprung
    mov     x2, #0x3c4
    msr     spsr_el2, x2

    // Adresse für "Rücksprung"
    adr     x2, 2f
    msr     elr_el2, x2
    eret
    
    
2:  ret