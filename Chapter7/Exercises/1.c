#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise :1
 * Page:153
 * Write a program that converts upper case to lower or lower case to upper,
 * depending on the name it is invoked with, as found in argv[0].
 * */
int main(int argc, char *argv[]) {
    int c;
    if (strstr(argv[0], "lower")) {
        while ((c = getchar()) != EOF) {
            (void)putchar(tolower(c));
        }
    } else {
        while ((c = getchar()) != EOF) {
            (void)putchar(toupper(c));
        }
    }
    return 0;
}
