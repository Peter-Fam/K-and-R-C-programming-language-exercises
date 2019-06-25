#include <stdio.h>
/*
 * Exercise 23
 * Page: 34
 * Write A program to remove all comments from a C program.
 * Don't forget to handle qouted strings and characters
 * constants properly. C comments do not nest.
 * */
#define MAXLINE 1000

#define STRINGIN 0
#define STRINGOUT 1
#define COMMENTIN 2
#define COMMENTOUT 3
#define CHARIN 4
#define CHAROUT 5

#define YES 1
#define NO 0

static int get_line(/*@out@*/ char line[], int maxline);
static int decomment(char line[], int state);

int main(void) {
    int len, state;
    char line[MAXLINE];

    state = COMMENTOUT;
    while ((len = get_line(line, MAXLINE)) > 0) {
        state = decomment(line, state);
        printf("%s", line);
    }

    return 0;
}

static int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != (int)'\n'; ++i) {
        if ((i < lim - 1))
            s[i] = (char)c;
    }

    if (c == (int)'\n' && (i < lim - 1)) {
        s[i] = (char)c;
        i++;
    }

    if ((i < lim - 1)) {
        s[i] = '\0';
    } else {
        s[lim - 1] = '\0';
        s[lim - 2] = '\n';
    }

    return i;
}

static int decomment(char s[], int state) {
    int i, new_i;
    int special_char = NO;

    new_i = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (state != COMMENTIN) {
            if ((s[i] == '/') && (s[i + 1] == '*') && (state != STRINGIN) &&
                (state != CHARIN)) {
                state = COMMENTIN;
            } else {
                s[new_i++] = s[i];
            }

            if (state == STRINGIN || state == CHARIN) {
                if (s[i - 1] == '\\') {
                    if (special_char == NO)
                        special_char = YES;
                    else
                        special_char = NO;
                } else {
                    special_char = NO;
                }
            }

            if ((s[i] == '\"') && (state != CHARIN)) {
                if (state != STRINGIN) {
                    state = STRINGIN;
                } else {
                    if (special_char == NO)
                        state = STRINGOUT;
                }
            }

            if ((s[i] == '\'') && (state != STRINGIN)) {
                if (state != CHARIN) {
                    state = CHARIN;
                } else {
                    if (special_char == NO)
                        state = CHAROUT;
                }
            }
        } else {

            if ((s[i] == '*') && (s[i + 1] == '/')) {
                state = COMMENTOUT;
                i++;
            }
        }
    }
    s[new_i] = s[i];

    return state;
}
