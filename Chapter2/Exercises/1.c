#include <float.h>
#include <limits.h>
#include <stdio.h>
/*
 * Exercise 1
 * Page: 36
 * Write a program to determine the ranges of char, short,
 * int, and long variables, both signed and unsigned,
 * by printing appropiate values from standard headers
 * and by dirct computation.
 * Harder if you compute them;
 * determine the ranges of the various floating-point types.
 * */

int main(void) {
    printf("\nStandard Header\n");
    printf("Unsigned char max value:%u\n", (unsigned int)UCHAR_MAX);
    printf("Unsigned char min value:%u\n", 0);
    printf("Signed char max value:%d\n", (int)CHAR_MAX);
    printf("Signed char min value:%d\n", (int)CHAR_MIN);
    printf("Calculated Value:\n");
    {
        unsigned char i;
        /*@i@*/ for (i = -1; i < 0; i--) { ; }
        printf("Unsigned char max value:%u\n", (unsigned int)i);
        printf("Unsigned char min value:%u\n", 0);
    }
    {
        char i;
        /*@i@*/ for (i = -1; i < 0; i--) { ; }
        printf("Signed char max value:%d\n", (int)i);
        /*@i@*/ for (i = 1; i > 0; i++) { ; }
        printf("Signed char min value:%d\n", (int)i);
    }
    printf("\nStandard Header\n");
    printf("Unsigned short max value:%u\n", USHRT_MAX);
    printf("Unsigned short min value:%u\n", 0);
    printf("Signed short max value:%d\n", SHRT_MAX);
    printf("Signed short min value:%d\n", SHRT_MIN);
    printf("Calculated Value:\n");
    {
        unsigned short i;
        /*@i@*/ for (i = -1; i < 0; i--) { ; }
        printf("Unsigned short max value:%u\n", (unsigned int)i);
        printf("Unsigned short min value:%u\n", 0);
    }
    {
        short i;
        /*@i@*/ for (i = -1; i < 0; i--) { ; }
        printf("Signed short max value:%d\n", (int)i);
        /*@i@*/ for (i = 1; i > 0; i++) { ; }
        printf("Signed short min value:%d\n", (int)i);
    }
    printf("\nStandard Header\n");
    printf("Unsigned int max value:%u\n", UINT_MAX);
    printf("Unsigned int min value:%u\n", 0);
    printf("Signed int max value:%d\n", INT_MAX);
    printf("Signed int min value:%d\n", INT_MIN);

    printf("Calculated Value:\n");
    printf("Unsigned int max value:%u\n", (unsigned int)~0);
    printf("Unsigned int min value:%u\n", 0);
    printf("Signed int max value:%d\n", (int)(((unsigned int)~0) >> 1));
    printf("Signed int min value:%d\n", (int)~(((unsigned int)~0) >> 1));

    printf("\nStandard Header\n");
    printf("Unsigned long max value:%lu\n", ULONG_MAX);
    printf("Unsigned long min value:%lu\n", 0UL);
    printf("Signed long max value:%ld\n", LONG_MAX);
    printf("Signed long min value:%ld\n", LONG_MIN);

    printf("Calculated Value:\n");
    printf("Unsigned long max value:%lu\n", (unsigned long)~0);
    printf("Unsigned long min value:%lu\n", 0l);
    printf("Signed long max value:%ld\n", (long)(((unsigned long)~0l) >> 1));
    printf("Signed long min value:%ld\n", (long)~(((unsigned long)~0l) >> 1));

    printf("\nStandard Header\n");
    printf("Float max value:%e\n", FLT_MAX);
    printf("Float min value:%e\n", FLT_MIN);

    printf("\nStandard Header\n");
    printf("Double max value: ±%e\n", DBL_MAX);
    printf("Double min value: ±%e\n", DBL_MIN);

    return 0;
}
