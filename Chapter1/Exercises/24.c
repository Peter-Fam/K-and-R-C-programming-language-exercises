#include <stdio.h>
/*
 * Exercise 24
 * Page: 34
 * Write a program to check a C program for
 * rudimentary syntax errors like unbalanced parentheses,
 * brackets and braces. Don't forget about quotes,
 * both single and double, escape sequences, and comments.
 * (This program is hard if you do it in full generality.)
 * */
#define STRINGOUT 0
#define STRINGIN 1
#define CHARIN 2
#define CHAROUT 3
#define COMMENTIN 4
#define COMMENTOUT 5

#define YES 1
#define NO 0

#define MAXLINE 1000

static int get_line(/*@out@*/ char line[], int maxline);

int main(void) {
    int len, state, line_num;
    int bracket_c, dqoute_c, sqoute_c, parans_c, comment_c;
    int special_char;
    char line[MAXLINE];

    state = COMMENTOUT;

    bracket_c = 0;
    dqoute_c  = 0;
    sqoute_c  = 0;
    parans_c  = 0;
    comment_c = 0;
    line_num  = 0;

    special_char = NO;
    while ((len = get_line(line, MAXLINE)) > 0) {
        printf("%s", line);
        int i;
        for (i = 0; line[i] != '\0'; i++) {
            if (state != COMMENTIN) {
                if ((line[i] == '/') && (line[i + 1] == '*') &&
                    (state != STRINGIN) && (state != CHARIN)) {
                    state = COMMENTIN;
                    ++comment_c;
                }
                if (state == STRINGIN || state == CHARIN) {
                    if (line[i - 1] == '\\') {
                        if (special_char == NO) {
                            special_char = YES;
                        } else {
                            special_char = NO;
                        }
                    } else {
                        special_char = NO;
                    }
                } else {
                    if (line[i] == '(') {
                        ++parans_c;
                    }
                    if (line[i] == ')') {
                        --parans_c;
                    }
                    if (line[i] == '{') {
                        ++bracket_c;
                    }
                    if (line[i] == '}') {
                        --bracket_c;
                    }
                }
                if ((line[i] == '\"') && (state != CHARIN)) {
                    if (state != STRINGIN) {
                        state = STRINGIN;
                        ++dqoute_c;
                    } else {
                        if (special_char == NO) {
                            state = STRINGOUT;
                            --dqoute_c;
                        }
                    }
                }

                if ((line[i] == '\'') && (state != STRINGIN)) {
                    if (state != CHARIN) {
                        state = CHARIN;
                        ++sqoute_c;
                    } else {
                        if (special_char == NO) {
                            state = CHAROUT;
                            --sqoute_c;
                        }
                    }
                }

            } else {

                if ((line[i] == '*') && (line[i + 1] == '/')) {
                    state = COMMENTOUT;
                    i++;
                    --comment_c;
                }
            }
        }

        if (sqoute_c > 0) {
            printf("error,expected \' at line:%d\n", line_num);
            break;
        }

        if (dqoute_c > 0) {
            printf("error,expected \" at line:%d\n", line_num);
            break;
        }

        line_num++;
    }
    if (bracket_c > 0) {
        printf("Error:expected '}' at line:%d\n", line_num);
    } else if (bracket_c < 0) {
        printf("Error:unbalanced Square Brackets\n");
    }
    if (parans_c > 0) {
        printf("Error:expected ')'\n");
    } else if (parans_c < 0) {
        printf("Error:unbalanced Parentheses\n");
    }
    if (comment_c > 0) {
        printf("Error:Unclosed Comment Section\n");
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
