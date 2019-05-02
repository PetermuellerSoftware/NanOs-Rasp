/*
    Give an entrypoint for the Raspberry bootloader, hopefully this is start as grub uses as well
*/
ENTRY(_start)

SECTIONS
{
        . = 0x80000;
        
        _text_start = .;
        _kernel_start = .;
        _start = .;
        
        .text : 
        {
            KEEP(*(.text.boot))
            *(.text)
        }
        _text_end = .;
        
        .rodata BLOCK(4K) : ALIGN(4K)
        {
            *(.rodata)
        }
        
        .data BLOCK(4K) : ALIGN(4K)
        {
            *(.data)
        }
        
                
        .bss (NOLOAD) :
        {            
            . = ALIGN(16);
            __bss_start = .;
            *(.bss .bss.*)
            *(.COMMON)
            __bss_end = .;
        }
        
        __bss_size = (__bss_end - __bss_start) >> 3;
        
        _kernel_end = .;
        _kernel_size = (_kernel_end - _kernel_start);
}
        