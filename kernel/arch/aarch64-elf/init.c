
#include <printf.h>
#include <arch/kuart.h>
#include <arch/mbox.h>

void initialize_arch() {
    uart_init();

    printf("Initializing for Raspberry Pi 3B+ aarch64\n");

    printf("board model is: 0x%x \n", mbox_get_boardmodel());
    printf("board version is: 0x%x \n", mbox_get_boardrevision());    
    printf("board mac is: ");
    
    const uint8_t* mac = mbox_get_boardmac();
    for (int i=0; i<6; i++) {
        printf("%02X", mac[i]);
        if (i<5) printf(":");
    }
    printf("\n");

    printf("board serial is: 0x%x \n", mbox_get_Serial());
}