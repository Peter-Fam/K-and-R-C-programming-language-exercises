#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise 19
 * Page:126
 * Modify undcl so that it does not add redundant parantheses to declarations
 * */
/* redundant parantheses appear around pointers only
 * so we need to only add parantheses when the type shift from pointer to a
 * function or array */
#define MAXTOKEN 1000
#define MAXLEN 10000
enum { NAME, PARENS, BRACKETS };

static int gettoken(void);
static int tokentype;
static char token[MAXTOKEN];
static char out[MAXLEN];

int main(void) {
    int type;
    char temp[MAXTOKEN];
    int last_type = (int)'\0';
    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != (int)'\n') {
            if (type == PARENS || type == BRACKETS) {
                if (last_type == (int)'*') {
                    /*@i@*/ sprintf(temp, "(%s)",
                                    out); /* buffer overflow possible */
                    strcpy(out, temp);
                }
                strcat(out, token);
            } else if (type == (int)'*') {
                /*@i@*/ sprintf(temp, "*%s",
                                out); /* buffer overflow possible */
                strcpy(out, temp);
            } else if (type == NAME) {
                /*@i@*/ sprintf(temp, "%s %s", token,
                                out); /* buffer overflow possible */
                strcpy(out, temp);
            } else if (type == EOF) {
                break;
            } else {
                printf("invaled input at %s\n", token);
            }
            last_type = type;
        }
        printf("%s\n", out);
    }
    return 0;
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

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == (int)' ' || c == (int)'\t') {
        ;
    }
    if (c == (int)'(') {
        if ((c = getch()) == (int)')') {
            strcpy(token, "()");
            return (tokentype = PARENS);
        } else {
            ungetch(c);
            return (tokentype = (int)'(');
        }
    } else if (c == (int)'[') {
        for (*p++ = (char)c; (*p++ = (char)getch()) != ']';) {
            ;
        }
        *p = '\0';
        return (tokentype = BRACKETS);
    } else if (isalnum(c)) {
        for (*p++ = (char)c; isalnum(c = getch());) {
            *p++ = (char)c;
        }
        *p = '\0';
        ungetch(c);
        return (tokentype = NAME);
    } else {
        return (tokentype = c);
    }
}
