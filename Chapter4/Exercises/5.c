#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise 5
 * Page: 79
 * Add access to library functions like
 * sin , exp , and pow . See <math.h>
 * in Appendix B, Section 4.
 * */
#define NUMBER '0'
#define MAXOP 100
#define COMPLEX '1'

static int getop(/*@out@*/ char s[]);
static void push(double num);
static double pop(void);
static double peek(void);
static void duplicate(void);
static void swap_stack();
static void clear_stack();
static double complex_op(double x, char s[]);
int main(void) {
    int type, lastop;
    double op2;
    char s[MAXOP];
    lastop = (int)'0';
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case COMPLEX:
            push(complex_op(pop(), s));
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
            if (op2 > 0 || op2 < 0) {
                push(pop() / op2);
            } else {
                printf("error: Zero Divisor\n");
            }
            break;
        case '%':
            op2 = pop();
            if (op2 > 0 || op2 < 0) {
                push((double)((int)pop() % (int)op2));
            } else {
                printf("error: Zero ModDivisor\n");
            }
            break;
        case '?':
            printf("top of stack: %.7g\n", peek());
            break;
        case '\\':
            printf("saving answer\n");
            duplicate();
            break;
        case ',':
            printf("swaping stack top\n");
            swap_stack();
            break;
        case '!':
            clear_stack();
            break;
        case '\n':
            if (lastop != (int)'?' && lastop != (int)',') {
                printf("\t%.7g\n", pop());
            }
            break;
        default:
            printf("error: Unknown Command\n");
            break;
        }
        lastop = type;
    }

    return 0;
}
static double complex_op(double x, char s[]) {
    if (strcmp(s, "sqrt") == 0) {
        return sqrt(x);
    }
    if (strcmp(s, "sin") == 0) {
        return sin(x);
    }
    if (strcmp(s, "cos") == 0) {
        return cos(x);
    }
    if (strcmp(s, "asin") == 0) {
        return asin(x);
    }
    if (strcmp(s, "acos") == 0) {
        return acos(x);
    }
    printf("Unknown complex command\n");
    return x;
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
double peek(void) {
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
void clear_stack(void) {
    sp = 0;
}
void duplicate(void) {
    if (sp < MAXVAL) {
        val[sp] = val[sp - 1];
        sp++;
    } else {
        printf("error: stack full, can't duplicate");
    }
}
void swap_stack(void) {
    if (sp > 1) {
        double temp;
        temp        = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("stack too small to swap");
    }
}

#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
static int getch(void) {
    return (bufp > 0) ? (int)buf[--bufp] : getchar();
}
static void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char)c;
}

#include <ctype.h>
/*@ignore@*/
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    i    = 0;
    if (!isdigit(c) && c != '.') {
        int last = c;
        if (c != '-') {
            if (isalpha(c)) {
                if (isspace(c = getch())) {
                    return last;
                }
                ungetch(c);
            }else{
                return last;
            }
        } else {
            if (isspace(c = getch())) {
                ungetch(c);
                return last;
            }
            ungetch(c);
            s[i] = last;
        }
    }
    int return_type = NUMBER;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
        if (c == (int)'.') {
            while (isdigit(s[++i] = c = getch())) {
                ;
            }
        }
    } else if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch())) {
            ;
        }
        return_type = COMPLEX;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return return_type;
}
/*@endignore@*/

