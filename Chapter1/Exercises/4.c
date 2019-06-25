#include <stdio.h>
/*
 * Exercise 4
 * Page: 13
 * Write a program to print the corresponding Celsius to Fahrenheit
 * */
int main(void) {
    double fahr, celsius;
    int lower, step, upper;

    lower = 0;
    upper = 300;
    step  = 20;

    celsius = (double)lower;
    printf("%12s:%12s\n", "Celsius", "Fahrenheit");
    while (celsius <= (double)upper) {
        fahr = celsius * (9.0 / 5.0) + 32;
        printf("%12.0f %12.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
