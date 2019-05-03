

// needs 11 zero bits on the left
.p2align 11

.global _vectors

_vectors:

    // ++++++++++++++++++++++++++++
    // Current ExceptionLevel with SP0
    
    // synchronous
    .align 7    
    mov     x0, #0
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler
    

    // IRQ
    .align 7    
    mov     x0, #1
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // FIQ
    .align 7    
    mov     x0, #2
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // SError
    .align 7
    mov     x0, #3
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // ++++++++++++++++++++++++++++
    // Current ExceptionLevel with SPx
    
    // synchronous
    .align 7    
    mov     x0, #4
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler
    

    // IRQ
    .align 7    
    mov     x0, #5
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // FIQ
    .align 7    
    mov     x0, #6
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // SError
    .align 7
    mov     x0, #7
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // ++++++++++++++++++++++++++++
    // Lower ExceptionLevel using AArch64
    
    // synchronous
    .align 7    
    mov     x0, #8
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler
    

    // IRQ
    .align 7    
    mov     x0, #9
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // FIQ
    .align 7    
    mov     x0, #10
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // SError
    .align 7
    mov     x0, #11
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // ++++++++++++++++++++++++++++
    // Lower ExceptionLevel with using AArch32
    
    // synchronous
    .align 7    
    mov     x0, #12
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler
    

    // IRQ
    .align 7    
    mov     x0, #13
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // FIQ
    .align 7    
    mov     x0, #14
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler


    // SError
    .align 7
    mov     x0, #15
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exc_handler
