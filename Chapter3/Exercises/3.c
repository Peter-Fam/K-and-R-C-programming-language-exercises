#include <ctype.h>
#include <stdio.h>
/*
 * Exercise 3
 * Page: 63
 * Write a function expand(s1,s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent
 * complete list abc...xyz in s2 .
 * Allow for letters of either case and digits,
 * and be prepared to handle cases like a-b-c and
 * a-z0-9 and -a-z .
 * Arrange that a leading or trailing - is taken literally.
 * */
static void expand(const char s1[], /*@out@*/ char s2[]);
int main(void) {
    char s1[100] = "-a-z testing a-f a-b-c A-Za-z0-9 testing 5-9 a-d-f 1-3-6-9";
    char s2[1000];
    expand(s1, s2);
    printf("%s", s2);
    return 0;
}
static void expand(const char s1[], char s2[]) {
    int i, j;
    i = 0;
    j = 0;
    while (s1[i] != '\0') {
        if (s1[i] == '-') {
            if ((i > 0) && isalnum(s1[i - 1])) {
                if ((islower(s1[i - 1]) && islower(s1[i + 1])) ||
                    (isupper(s1[i - 1]) && isupper(s1[i + 1])) ||
                    (isdigit(s1[i - 1]) && isdigit(s1[i + 1]))) {
                    int k;
                    k = (int)(s1[i + 1] - s1[i - 1]);
                    while (k != 0) {
                        k > 0 ? k-- : k++;
                        s2[j++] = (char)((int)s1[i + 1] - k);
                    }
                    i += 2;
                } else {
                    s2[j++] = s1[i++];
                }
            } else {
                s2[j++] = s1[i++];
            }
        } else {
            s2[j++] = s1[i++];
        }
    }
    s2[j] = s1[i];
}
