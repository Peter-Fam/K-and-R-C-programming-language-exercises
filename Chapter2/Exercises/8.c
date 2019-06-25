#include <limits.h>
#include <stdio.h>
/*
 * Exercise 8
 * Page: 49
 * Write a function rightrot(x,n) that returns the value
 * of the integer x rotated to the right by n bit positions.
 * */

static unsigned int rightrot(unsigned int x, unsigned int n);

int main(void) {
    unsigned int x = 0x0ff0;
    unsigned int n = 8;
    printf("%x", rightrot(x, n));

    return 0;
}

static unsigned int rightrot(unsigned int x, unsigned int n) {
    for (; n > 0; n--) {
        /*@i@*/ x = (x & 1) ? (x >> 1) | ~((~0u) >> 1) : (x >> 1);
    }
    return x;
}
