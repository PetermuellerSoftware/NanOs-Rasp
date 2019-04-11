#ifndef ARCH_GPFIO_H
#define ARCH_GPFIO_H 1

#include <stdint.h>

enum {
    GP_FUNC_INPUT   = 0x00,
    GP_FUNC_OUTPUT  = 0x01,
    GP_FUNC_ALT0    = 0x04,
    GP_FUNC_ALT1    = 0x05,
    GP_FUNC_ALT2    = 0x06,
    GP_FUNC_ALT3    = 0x07,
    GP_FUNC_ALT4    = 0x03,
    GP_FUNC_ALT5    = 0x02
};


enum GPF_REGISTER_ADDRESSES {
    GPF_BASE        = 0x7E200000
};

enum GP_FUNCTION_SELECTOR {
    GPFSEL0 = GPF_BASE + 0x00,
    GPFSEL1 = GPF_BASE + 0x04,
    GPFSEL2 = GPF_BASE + 0x08,
    GPFSEL3 = GPF_BASE + 0x0C,
    GPFSEL4 = GPF_BASE + 0x10,
    GPFSEL5 = GPF_BASE + 0x14
    
};

enum GPP_UP_DOWN {
    GPPUD = GPF_BASE + 0x94,
    GPPUDCLK0 = GPF_BASE + 0x98,
    GPPUDCLK1 = GPF_BASE + 0x9c    
};




void gpfio_set_func( uint8_t pin, uint8_t function); 

#endif