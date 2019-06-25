#include <stdio.h>
/*
 * Exercise 9
 * Page: 51
 * In a two's complement number system, x &= (x-1)
 * deletes the rightmost 1-bit in x .
 * Explain why. Use this observation to write
 * a faster version of bitcount .
 * */

/* 
 * subtraction in 2 complimen number system ,
 * flips all bits til the rightmost 1-bit and
 * &ing the result with original effectively 
 * removing the rightmost 1-bit in x
 *  */

static unsigned int bit_count(unsigned int x);

int main(void) {
    unsigned int x = 0xffff7fff;
    printf("%u",bit_count(x));
    return 0;
}

static unsigned int bit_count(unsigned int x) {
    unsigned int n = 0;
    while(x!=0){
        n++;
        x&=(x-1);
    }
    return n;
}
