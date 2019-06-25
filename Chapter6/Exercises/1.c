#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise: 1
 * Page:  136
 * Our version of getword does not properly handle underscores, string
 * constants, comments, or preprocessor control lines. Write a better version.
 * */
static struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},   {"break", 0},    {"case", 0},     {"char", 0},
    {"const", 0},  {"continue", 0}, {"default", 0},  {"do", 0},
    {"double", 0}, {"else", 0},     {"enum", 0},     {"extern", 0},
    {"float", 0},  {"for", 0},      {"goto", 0},     {"if", 0},
    {"int", 0},    {"long", 0},     {"register", 0}, {"return", 0},
    {"signed", 0}, {"sizeof", 0},   {"static", 0},   {"struct", 0},
    {"switch", 0}, {"typedef", 0},  {"union", 0},    {"unsigned", 0},
    {"void", 0},   {"volatile", 0}, {"while", 0},
};
#define MAXWORD 100
#define L auto auto auto auto
static int getword(/*@out@*/ char *s, int lim);
static int binsearch(char *word, struct key tab[], int n);
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

int main(void) {
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, (int)NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < (int)NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

/* binsearch: find word in sorted tab[0] ... tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;
    low  = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

#define BUFSIZE 10000
static int buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
static void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
enum STATE_E { IN, OUT };
/* getword: get next word or character from auto auto auto input */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }
    if (c != EOF) {
        *w++ = (char)c;
    }
    int state = OUT;
    switch (c) {
    case '#':
        while ((c = getch()) != (int)'\n' && c != EOF) {
            ;
        }
        break;
    case '"':
        state = IN;
        while (state == IN) {
            c = getch();
            if (c == (int)'"') {
                state = OUT;
            } else if (c == (int)'\\') {
                c = getch();
            }
        }
        break;
    case '\'':
        state = IN;
        while (state == IN && c != EOF) {
            c = getch();
            if (c == (int)'\'') {
                state = OUT;
            } else if (c == (int)'\\') {
                c = getch();
            }
        }
        break;
    case '/':
        if ((c = getch()) == (int)'*') {
            state = IN;
        } else {
            ungetch(c);
        }
        while (state == IN && c != EOF) {
            c = getch();
            if (c == (int)'*') {
                if ((c = getch()) == (int)'/') {
                    state = OUT;
                } else {
                    ungetch(c);
                }
            }
        }
    default:
        break;
    }
    if (!isalpha(c) && c != (int)'_') {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = (char)getch()) && *w != '_') {
            ungetch((int)*w);
            break;
        }
    }
    *w = '\0';
    return (int)word[0];
}
