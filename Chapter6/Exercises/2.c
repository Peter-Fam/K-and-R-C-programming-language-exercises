#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise: 2
 * Page:  143
 * Write a program that reads a C program and prints in alphabetical
 * order each group of variable names that are identical in the first 6
 * characters but different somewhere thereafter. Don't count words within
 * strings and comments. Make 6 a parameter that can be set from the command
 * line.
 * */
struct tnode {           /* the tree node */
    char *word;          /* points to the text */
    int count;           /* number of occurrences */
    struct tnode *left;  /* left child */
    struct tnode *right; /* right child */
};

#define MAXWORD 100
static struct tnode *addtree(struct tnode *tree, char *word);
static void treeprint(struct tnode *p, char *word, int lim);
static int getword(/*@out@*/ char *s, int lim);
static struct key {
    char *word;
    int count;
} types[] = {
    {"char", 0}, {"double", 0}, {"float", 0},    {"int", 0},
    {"long", 0}, {"signed", 0}, {"unsigned", 0}, {"void", 0},
};
#define MAXWORD 100
static int binsearch(char *word, struct key tab[], int n);
#define NKEYS (sizeof(types) / sizeof(types[0]))
enum LINE_STATE_E { IN_VAR_LINE, OUT_VAR_LINE };
int main(int argc, char *argv[]) {
    int n;
    int lim;
    while (--argc > 0) {
        lim = atoi(argv[argc]);
        if (lim == 0) {
            printf("error: invalid argument");
            return 1;
        }
    }
    struct tnode *root = NULL;
    char word[MAXWORD];
    int state = OUT_VAR_LINE;
    int c;
    int last_c = '\0';
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (c == (int)';' || c == (int)'\n' || c == '=') {
            state = OUT_VAR_LINE;
        } else if (state == IN_VAR_LINE) {
            if (word[0] == '_' || isalpha(word[0])) {
                if (binsearch(word, types, (int)NKEYS) < 0) {
                    root = addtree(root, word);
                }
            }
        } else if ((n = binsearch(word, types, (int)NKEYS)) >= 0 &&
                   last_c == '\n') {
            state = IN_VAR_LINE;
        }
        last_c = c;
    }
    treeprint(root, "", lim);
    return 0;
}

static struct tnode *talloc(void);
static char *str_dup(char *str);

/*addtree : add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p        = talloc();
        p->word  = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

/* treeprint : in-order print of tree p*/
static void treeprint(struct tnode *p, char *word, int lim) {
    if (p != NULL) {
        treeprint(p->left, p->word, lim);
        if (strncmp(p->word, word, lim) != 0) {
            printf("Group: %.*s\n", lim, p->word);
        }
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right, p->word, lim);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* str_dup: make a duplicate of s */
static char *str_dup(char *s) {
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}
/* binsearch: find word in sorted tab[0] ... tab[n-1] */
static int binsearch(char *word, struct key tab[], int n) {
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
static int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isblank(c = getch())) {
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
