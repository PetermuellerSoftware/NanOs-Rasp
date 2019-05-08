#include <arch/kuart.h>

#include <arch/baseIO.h>
#include <arch/delay.h>
#include <stdint.h>
#include <arch/gpfio.h>
#include <arch/auxiliaries.h>

void uart_init() {    
    // bit 14 und 15 auf UART1 setzen (Alternative 5)
    
    gpfio_set_func(14, GP_FUNC_ALT5);
    gpfio_set_func(15, GP_FUNC_ALT5);
    
    //jegliches pull-up/down sicher entfernen
    put64(GPPUD,0);
    wait_cycles(150);
    put64(GPPUDCLK0,(1<<14)|(1<<15));
    wait_cycles(150);
    put64(GPPUDCLK0,0);
    
    // mini uart einschalten
    const uint32_t enable = get64(AUX_ENABLE);
    put64(AUX_ENABLE, enable | 0x01);
    
    // erstmal alles ausschalten, bis wir fertig initialisiert haben
    put64 (AUX_MU_CNTL_REG, 0);
    put64 (AUX_MU_IER_REG, 0);
    put64 (AUX_MU_LCR_REG, 3);
    put64 (AUX_MU_MCR_REG, 0);
    put64 (AUX_MU_IIR_REG, 0xc6);
    
    // baudrate = system_clock_freq / (8 * ( baudrate_reg + 1 ))
    // \/
    // baudrate * 8 * (baudrate-reg + 1) = system_clock_freq
    // baudrate_reg + 1 = system_clock_freq / (baudrate * 8)
    // baudrate_reg = system_clock_freq / (baudrate * 8) - 1
    uint32_t baudrate_reg = 270; //500000000 / (115200 * 8) - 1;
    put64 (AUX_MU_BAUD_REG, baudrate_reg);  // 115200 baud
    
    // und einschalten
    put64 (AUX_MU_CNTL_REG, 3);    
    
}

void uart_sends(const char* c)
{
    for (int i=0; c[i] != (const char) 0; i++)
        uart_send( c[i]);
}

void uart_send ( char c )
{
    while(1) {
        if(get64(AUX_MU_LSR_REG)&0x20) 
            break;
    }
    put64(AUX_MU_IO_REG,c);
}

char uart_recv ( void )
{
    while(1) {
        if(get64(AUX_MU_LSR_REG)&0x01) 
            break;
    }
    return(get64(AUX_MU_IO_REG)&0xFF);
}

/**
 * Display a binary value in hexadecimal
 */
void uart_hex(unsigned int d) {
    unsigned int n;
    int c;
    for(c=28;c>=0;c-=4) {
        // get highest tetrad
        n=(d>>c)&0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n+=n>9?0x37:0x30;
        uart_send(n);
    }
}

