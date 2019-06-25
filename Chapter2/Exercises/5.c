#include <limits.h>
#include <stdio.h>
/*
 * Exersice 5
 * Page: 48
 * Write the function any(s1,s2) , which returns the first location
 * in the string s1 where any character from the string s2 occurs,
 * or -1 if s1 contains no characters from s2 .
 * (The standard library function strpbrk does the same job
 * but returns a pointer to the location.)
 * */

static int any_optimized(const char s[], const char char_set[]);

int main(void) {
    char s[]="This is a test.";
    char char_set[]=". ";
    printf("%d\n",any_optimized(s,char_set));
    return 0;
}

static int any_optimized(const char s[], const char char_set[]) {
    unsigned int check_array[(unsigned int)UCHAR_MAX + 1] = {0};
    int i, ret;
    ret = -1;
    for (i = 0; char_set[i] != '\0'; i++) {
        check_array[(unsigned int)char_set[i]] = 1;
    }
    for (i = 0; s[i] != '\0'; i++) {
        if (check_array[(unsigned int)s[i]] == 1) {
            if (ret<0){
                ret=i;
            }else if (ret>i){
                ret=i;
            }
        }
    }
    return ret;
}
