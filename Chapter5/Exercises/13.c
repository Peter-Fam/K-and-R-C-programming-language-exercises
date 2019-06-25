#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exersice 13
 * Page: 118
 * Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, say, but it can be changed by an optional argument,
 * so that tail -n prints the last n lines. The program should behave
 * rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage;
 * lines should be stored as in the sorting program of Section 5.6,
 * not in a two-dimensional array of fixed size.
 * note: two-dimensional array of fixed size is used here
 * TODO: change buffer type
 * */
#define MAXLEN 255
#define MAXLINES 100
#define TAIL_N 10
char lines[MAXLINES][MAXLEN];
static int get_line(char s[], int lim);
int main(int argc, char **argv) {
    int line_n_lim = TAIL_N;
    while (--argc > 0) {
        if (argc == 1) {
            line_n_lim = atoi(*(++argv));
            if (line_n_lim <= 0) {
                printf("Error:invalid argument\n");
                return -1;
            } else if (line_n_lim >= MAXLINES) {
                printf("Error:too many lines to print:\nn should be less than "
                       "%d\n",
                       MAXLINES);
                return -1;
            }
            break;
        } else {
            printf("Error:invalid number of arguments \n");
            return -1;
        }
    }
    int line_n = 0;
    while ((get_line(lines[line_n % line_n_lim], MAXLEN) > 0)) {
        line_n++;
    }

    int starting_index = line_n % line_n_lim;
    if (line_n < line_n_lim) {
        int i;
        for (i = 0; i < line_n; i++) {
            printf("%s", lines[i]);
        }
    } else {
        line_n++;
        while (starting_index != line_n % line_n_lim) {
            printf("%s", lines[line_n++ % line_n_lim]);
        }
    }

    return 0;
}
int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while ((c = getchar()) != EOF && c != (int)'\n' && --lim > 0) {
        s[i++] = (char)c;
    }
    if (c == (int)'\n') {
        s[i++] = (char)c;
    }
    s[i] = '\0';
    return i;
}
