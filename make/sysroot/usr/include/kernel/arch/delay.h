#ifndef ARCH_DELAY_H
#define ARCH_DELAY_H 1



void wait_cycles(int cycles);
void wait_msec(unsigned int n);
void wait_msec_st(unsigned int n);

#endif