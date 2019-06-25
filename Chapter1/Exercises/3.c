#include <stdio.h>
/*
 * Exercise 3
 * Page: 13
 * Modify the temperature conversion program
 * to print a heading above the table
 * */

int main(void) {
    double fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step  = 20;

    fahr = (double)lower;
    printf("%12s:%12s\n", "Fahrenheit", "Celsius");
    while (fahr <= (double)upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%12.0f %12.1f\n", fahr, celsius);
        fahr += step;
    }

    return 0;
}
