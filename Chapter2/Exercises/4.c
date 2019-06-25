#include <limits.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise 4
 * Page: 48
 * Write an alternate version of squeeze(s1,s2) that
 * deletes each character in the string s1 that matches
 * any character in the string s2.
 * */

static void squeeze(char s[], const char char_set[]);
static void squeeze_optimized(char s[], const char char_set[]);

int main(void) {
    char s[]        = "this is a test";
    char s2[]       = "this is a test";
    char char_set[] = "adkjalidj ";
    squeeze(s, char_set);
    printf("%s\n", s);
    squeeze_optimized(s2, char_set);
    printf("%s\n", s2);
    return 0;
}

static void squeeze(char s[], const char char_set[]) {
    int i, k;
    k = 0;
    for (i = 0; s[i] != '\0'; i++) {
        int j;
        for (j = 0; char_set[j] != '\0'; j++) {
            if (char_set[j] == s[i]) {
                break;
            }
        }
        s[k] = s[i];
        if (j == (int)strlen(char_set)) {
            k++;
        }
    }
    s[k] = s[i];
}

/*
 * This solution is inspired by Partha Seetala's solution
 * for the next Exersice on clc-wiki.net
 * for more info:
 * https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_2:Exercise_5
 * */
static void squeeze_optimized(char s[], const char char_set[]) {
    unsigned int check_array[(unsigned int)UCHAR_MAX + 1] = {0};
    int i;
    for (i = 0; char_set[i] != '\0'; i++) {
        check_array[(unsigned int)char_set[i]] = 1;
    }
    int j;
    j = 0;
    for (i = 0; s[i] != '\0'; i++) {
        s[j] = s[i];
        if (check_array[(unsigned int)s[i]] != 1) {
            j++;
        }
    }
    s[j] = s[i];
}
