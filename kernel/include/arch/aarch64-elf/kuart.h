#ifndef KERNEL_UART_H
#define KERNEL_UART_H 1


void uart_init( void );

void uart_send( char c);
char uart_recv( void );

void uart_sends(const char* c);


#endif