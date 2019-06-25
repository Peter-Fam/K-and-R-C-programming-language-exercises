#include <ctype.h>
#include <stdio.h>
/*
 * Exercise 2
 * Page:73
 * Extend atof to handle scientific notation of
 * the form 123.45e-6 where a floating-point
 * number may be followed by e or E and an
 * optionally signed exponent.
 * */
static double ato_f(const char s[]);
int main(void) {
    char s[] = "1.3e-10";
    printf("%g\n", ato_f(s));
    return 0;
}
double ato_f(const char s[]) {
    double val, power, epower;

    int i, sign, esign;

    for (i = 0; isspace(s[i]); i++) {
        ;
    }

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '-' || s[i] == '+') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (double)(s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (double)(s[i] - '0');
        power *= 10;
    }
    if (tolower(s[i]) == (int)'e') {
        i++;
        esign = (s[i] == '-') ? -1 : 1;

        if (s[i] == '-' || s[i] == '+') {
            i++;
        }
        for (epower = 0; isdigit(s[i]); i++) {
            epower = 10.0 * epower + (double)(s[i] - '0');
        }
        for (; epower > 0; epower--) {
            if (esign < 0) {
                power *= 10;
            } else {
                power /= 10;
            }
        }
    }
    return sign * val / power;
}
