#include <stdio.h>
/*
 * Exercise 15
 * Page: 27
 * Rewrite the temperatute conversion program of section 1.2
 * to use a function for conversion.
 * */

#define LOWER 0
#define UPPER 300
#define STEP 20

static double toCelsius(double fahr);

int main(void) {
    double fahr;

    printf("%12s:%12s\n", "Fahrenhiet", "Celsius");
    for (fahr = LOWER; fahr <= UPPER; fahr += STEP) {
        printf("%12.0f %12.1f\n", fahr, toCelsius(fahr));
    }

    return 0;
}

static double toCelsius(double fahr) { return (5.0 / 9.0) * (fahr - 32); }
