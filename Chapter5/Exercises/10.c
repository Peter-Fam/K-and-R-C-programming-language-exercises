#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise 10
 * Page: 118
 * Write the program expr , which evaluates a reverse Polish expression,
 * from the command line, where each operator or operand is a separate
 * argument., For example, expr 2 3 4 + * evaluates 2 x (3+4)
 * note : use '"' when inputing operators since some terminals see it
 * as a wildcard character
 * */
#define NUMBER '0'
#define MAXOP 100

static int getop(/*@out@*/ char s[]);
static void push(double num);
static double pop(void);

int main(int argc, char **argv) {
    int type;
    double op2;
    char *s;
    while (--argc > 0) {
        s = *(++argv);
        switch (type = getop(s)) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0) {
                push(pop() / op2);
            } else {
                printf("error: Zero Divisor\n");
            }
            break;
        default:
            printf("error: Unknown Command\n");
            break;
        }
    }
    printf("\t%.7g\n", pop());

    return 0;
}

#define MAXVAL 100
static int sp = 0;
static double val[MAXVAL];
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %f\n", f);
}
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[]) {
    int i, c;
    i = 0;
    while ((c = (int)s[i++]) == (int)' ' || c == (int)'\t') {
        ;
    }
    if (!isdigit(c) && c != (int)'.') {
        return c;
    }

    if (isdigit(c)) {
        while (isdigit(c = (int)s[i++])) {
            ;
        }
    }
    if (c == (int)'.') {
        while (isdigit(c = (int)s[i++])) {
            ;
        }
    }
    return (int)NUMBER;
}
