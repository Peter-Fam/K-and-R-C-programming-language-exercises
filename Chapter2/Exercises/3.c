#include <ctype.h>
#include <stdio.h>
/*
 * Exercise 3
 * Page: 46
 * Write the function htoi(s) , which converts a string of
 * hexadecimal digits (including an optional 0x or 0X)
 * into its equivalent integer value.
 * The allowable digits are 0 through 9,
 * a through f, and A through F.
 * */

#define BASE 16

static unsigned int htoi(const char s[]);

int main(void) {
    printf("%x",(unsigned int)htoi("       ia "));
    return 0;
}

static unsigned int htoi(const char s[]) {
    int i;
    unsigned int n;
    n = 0;
    for (i = 0; (s[i] != '\0') && (isspace(s[i])); i++) {
        ;
    }
    if (s[i] == '\0') {
        return 0;
    }
    if ((s[i] == '0') && (tolower(s[i + 1]) == (int)'x')) {
        i += 2;
    }
    for (; s[i] != '\0' && (isdigit(s[i]) || (tolower(s[i]) >= (int)'a' &&
                                              tolower(s[i]) <= (int)'f'));
         i++) {
        if(isdigit(s[i])){
            n = n*BASE +(int)(s[i]-'0');
        }else{
            n = n*BASE + (int)(tolower(s[i])-'a'+10);
        }
    }

    return n;
}
