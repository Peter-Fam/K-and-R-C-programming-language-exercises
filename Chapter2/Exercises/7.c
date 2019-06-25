#include <stdio.h>
/*
 * Exercise 7\
 * Page: 49
 * Write a function invert(x,p,n) that returns x 
 * with the n bits that begin at position p inverted 
 * (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 * */

static unsigned int invert(unsigned int x,unsigned int p, unsigned int n);

int main(void){
    unsigned int x;
    unsigned int p;
    unsigned int n;
    x=0x0ff0;
    p=3;
    n=7;
    printf("%x",invert(x,p,n));


    return 0;
}


static unsigned int invert(unsigned int x,unsigned int p, unsigned int n){
    unsigned int intrmed;

    intrmed = ~0u;
    intrmed = intrmed << n;
    intrmed = ~intrmed;
    intrmed = intrmed << p;

    return (x&(~intrmed))|((~x&intrmed));
}
