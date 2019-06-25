#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Exercise 14
 * Page: 121
 * Modify the sort program to handle a -r flag, which indicates sorting
 * in reverse (decreasing) order. Be sure that -r works with -n.
 * */
#define MAXLINES 5000

static char *lineptr[MAXLINES];

static int readlines(char *lineptr[], int nlines);
static void writelines(/*@in@*/ char *const lineptr[], int nlines);
static int numcmp(const char *s1, const char *s2);
static void q_sort(void *lineptr[], int left, int right,
                   int (*comp)(void *, void *), int reverse);

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0; /* 1 if numeric sort*/
    int reverse = 0;
    while (--argc > 0) {
        if (strcmp(argv[argc], "-n") == 0) {
            numeric = 1;
        } else if (strcmp(argv[argc], "-r") == 0) {
            reverse = 1;
        } else {
            printf("error: invalid argument");
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        q_sort((void **)lineptr, 0, nlines - 1,
               ((int (*)(void *, void *))(numeric == 1 ? numcmp : strcmp)),
               reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}
#define MAXLEN 1000
static int get_line(/*@out@*/ char *s, int lim);

static /*@null@*/ char *allocc(int n);

/* readlines: read input lines*/
/*this is a test*/
int strcomp(const char *s1, const char *s2);
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    p      = NULL;
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = allocc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    p = NULL;
    return nlines;
}

/*writelines: line output lines */
void writelines(char *const lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

static void swap(void *v[], int i, int j);
/* q_sort: sort v[left] ... v[right] into increasing order */
void q_sort(void *v[], int left, int right, int (*comp)(void *, void *),
            int reverse) {
    int i, last;

    if (left >= right) {
        return;
    } else {
        swap(v, left, (left + right) / 2);
        last = left;
        for (i = left + 1; i <= right; i++) {
            if (reverse ? (*comp)(v[i], v[left]) > 0
                        : (*comp)(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        q_sort(v, left, last - 1, comp, reverse);
        q_sort(v, last + 1, right, comp, reverse);
    }
}

static int numcmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}
/* getline: get line into s, return length*/
int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != (int)'\n') {
        s[i++] = (char)c;
    }
    if (c == (int)'\n') {
        s[i++] = (char)c;
    }
    s[i] = '\0';
    return i;
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *allocc(int n) { /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return (allocp - n);
    } else {
        return NULL;
    }
}
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}
