/*
    Give an entrypoint for the Raspberry bootloader, hopefully this is start as grub uses as well
*/
ENTRY(_text_start)

SECTIONS
{
        //. = 0x8000;
        
        _text_start = .;
        _start = .;
        
        .text BLOCK(4K) : ALIGN(4K)
        {
            *(.text.boot)
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
        
        .bss BLOCK(4K) : ALIGN(4K)
        {
            *(.COMMON)
            *(.bss)
        }
        
}
        