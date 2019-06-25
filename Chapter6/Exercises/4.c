#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise: 3
 * Page:  143
 * Write a cross-referencer that prints a list of all words in a document, and,
 * for each word, a list of the line numbers on which it occurs. Remove noise
 * words like "the," "and," and so on.
 * */
struct tnode {           /* the tree node */
    char *word;          /* points to the text */
    int count;           /* number of occurrences */
    struct tnode *left;  /* left child */
    struct tnode *right; /* right child */
    struct lnode *nline_list;
};
struct lnode {
    int nline;
    struct lnode *next;
};
char *noise_words[] = {"a", "an", "and", "are", "is", "the", "was", "were"};

static int binsearch(char *word, char *tab[], int n);
#define NKEYS (sizeof(noise_words) / sizeof(noise_words[0]))
#define MAXWORD 100
static struct tnode *addtree(struct tnode *tree, char *word, int nline);
static struct tnode *addtree_c(struct tnode *tree, char *word,
                               struct lnode *nline_list, int count);
static struct lnode *addlist(struct lnode *list, int nline);
static void treeprint(struct tnode *p);
static void listprint(struct lnode *p);
static int getword(/*@out@*/ char *s, int lim);
static void tree_c(struct tnode *p);
static struct tnode *c_root;
int main(void) {
    struct tnode *root = NULL;
    int nline          = 0;
    char word[MAXWORD];
    int c;
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (c == (int)'\n') {
            nline++;
        } else if (isalpha(word[0])) {
            if (binsearch(word, noise_words, NKEYS) < 0) {
                root = addtree(root, word, nline);
            }
        }
    }
    tree_c(root);
    treeprint(c_root);
    return 0;
}
static struct tnode *talloc(void);
static char *str_dup(char *str);

/*addtree : add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int nline) {
    int cond;

    if (p == NULL) {
        p        = talloc();
        p->word  = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
        p->nline_list      = addlist(p->nline_list, nline);
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        p->nline_list = addlist(p->nline_list, nline);
    } else if (cond < 0) {
        p->left = addtree(p->left, w, nline);
    } else {
        p->right = addtree(p->right, w, nline);
    }
    return p;
}
struct tnode *addtree_c(struct tnode *p, char *w, struct lnode *nline_list,
                        int count) {
    int cond;

    if (p == NULL) {
        p        = talloc();
        p->word  = str_dup(w);
        p->count = count;
        p->left = p->right = NULL;
        p->nline_list      = nline_list;
    } else if (p->count < count) {
        p->left = addtree_c(p->left, w, nline_list, count);
    } else {
        p->right = addtree_c(p->right, w, nline_list, count);
    }
    return p;
}

/* treeprint : in-order print of tree p*/
static void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s", p->count, p->word);
        listprint(p->nline_list);
        printf("\n");
        treeprint(p->right);
    }
}

static void tree_c(struct tnode *p) {
    if (p != NULL) {
        tree_c(p->left);
        c_root = addtree_c(c_root, p->word, p->nline_list, p->count);
        tree_c(p->right);
    }
}
/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}
struct lnode *lalloc(void);
struct lnode *addlist(struct lnode *p, int nline) {
    if (p == NULL) {
        p        = lalloc();
        p->nline = nline;
        p->next  = NULL;
    } else {
        p->next = addlist(p->next, nline);
    }
    return p;
}

/* treeprint : in-order print of tree p*/
static void listprint(struct lnode *p) {
    if (p != NULL) {
        listprint(p->next);
        printf(",%d", p->nline);
    }
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

struct lnode *lalloc(void) {
    return (struct lnode *)malloc(sizeof(struct lnode));
}
static int binsearch(char *word, char *tab[], int n) {
    int cond;
    int low, high, mid;
    low  = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid])) < 0) {
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
