#include <stdio.h>
/*
 * Exercise 5
 * Page: 14
 * Modify the temperature conversion program to print
 * the table in reverse order,
 * that is, from 300 degrees to 0.
 * */
int main(void) {
    int fahr;

    printf("%12s:%12s\n", "Fahrenheit", "Celsius");
    for (fahr = 300; fahr >= 0; fahr -= 20) {
        printf("%12d %12.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
    }

    return 0;
}
