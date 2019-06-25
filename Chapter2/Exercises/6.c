#include <stdio.h>
/*
 * Exercise 6
 * Page:49
 * Write a function setbits(x,p,n,y) that returns x
 * with the n bits that begin at position p set to
 * the rightmost n bits of y,
 * leaving the other bits unchanged.
 * */
static unsigned int setbits(unsigned int x, unsigned int p, unsigned int n,
                            unsigned int y);

int main(void) {
    unsigned int x = 0x0000;
    unsigned int y = 0x001f;
    unsigned int p = 5;
    unsigned int n = 5;
    printf("%x", setbits(x, p, n, y));
    return 0;
}
static unsigned int setbits(unsigned int x, unsigned int p, unsigned int n,
                            unsigned int y) {

    unsigned int intrmed = 0;
    unsigned int x_mask  = 0;

    x_mask = ~x_mask;
    x_mask = x_mask << n;
    x_mask = ~x_mask;
    x_mask = x_mask << p;
    x_mask = ~x_mask;

    intrmed = ~intrmed;
    intrmed = intrmed << n;
    intrmed = ~intrmed;
    intrmed = y & intrmed;
    intrmed = intrmed << p;

    x = x & x_mask;
    x = x | intrmed;
    return x;
}
