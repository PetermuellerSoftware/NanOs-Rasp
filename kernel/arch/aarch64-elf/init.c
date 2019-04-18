
#include <printf.h>
#include <arch/kuart.h>
#include <arch/mbox.h>
#include <arch/delay.h>
#include <arch/vga.h>


void initialize_arch() {
    uart_init();

    printf("Initializing for Raspberry Pi 3B+ aarch64\n");
    
    printf("board model is: 0x%x \n", mbox_get_boardmodel());
    printf("board revision is: 0x%x \n", mbox_get_boardrevision());    
    printf("board mac is: ");
    
    const uint8_t* mac = mbox_get_boardmac();
    for (int i=0; i<6; i++) {
        printf("%02X", mac[i]);
        if (i<5) printf(":");
    }
    printf("\n");

    printf("board serial is: 0x%x \n", mbox_get_Serial());
    wait_msec( 10 * 1000);

    vga_init();
    vga_test();
}