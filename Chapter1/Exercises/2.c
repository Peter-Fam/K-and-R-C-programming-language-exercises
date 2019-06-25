#include <stdio.h>
/*
 * Exercise 2
 * Page: 8
 * Experiment to find out what happens when printf's argument string
 * contains \c, where c is some character not listed above.
 * */

int main(void) {
    printf("\nHello,\t World\\t");     /* tab*/
    printf("\nHello,\b World\\b");     /* backspace*/
    printf("\nHello,\a World\\a");     /* alert (beep) -doesn't work-*/
    printf("\nHello,\n World\\n");     /* newline*/
    printf("\nHello,\f World\\f");     /* formfeed (page break/new page)*/
    printf("\nHello,\r World\\r\e[s"); /* carriage return */
    printf("\nHello,\v World\\v");     /* vertical tab*/
    printf("\nHello,\? World\\?");     /* question mark*/
    printf("\nHello,\\ World\\");      /* backslash*/
    printf("\nHello,\' World\\\'");    /* single qoute*/
    printf("\nHello,\" World\\\"");    /* double qout*/
    printf("\nHello,\eE  World\\e");   /* escape character (non-standard)
            for more info:
        http://man7.org/linux/man-pages/man4/console_codes.4.html */
    return 0;
}
