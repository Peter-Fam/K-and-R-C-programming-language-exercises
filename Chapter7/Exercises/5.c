#include <stdio.h>
#include <stdlib.h>
/*
 * Exercise: 5
 * Page: 159
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or
 * sscanf to do the input and number conversions.
 * */
#define NUMBER 100
#define MAXOP '0'

static int getop(/*@out@*/ char s[]);
static void push(double num);
static double pop(void);

int main(void) {
    char type;
    double op2;
    char s[MAXOP];

    while ((scanf("%99s", s)) != EOF) {
        if (sscanf(s, "%lf", &op2) == 1) {
            push(op2);
        } else {
            if (sscanf(s, "%c", &type) != 1) {
                printf("Error: unknown Command");
            }
            switch (type) {
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
            case '=': /* \n was changed to = since scanf skip whitespace */
                printf("\t%.7g\n", pop());
                break;
            default:
                printf("error: Unknown Command\n");
                break;
            }
        }
    }
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
