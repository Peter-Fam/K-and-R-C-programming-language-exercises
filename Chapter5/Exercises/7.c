#include <stdio.h>
#include <string.h>
/*
 * Exercise 7
 * Page:110
 * Rewrite readlines to store lines in an array supplied by main
 * ,rather than calling alloc to maintain storage.
 * How much faster is the program?
 * */
#define MAXLINES 5000
#define MAXLEN 1000

static char *lineptr[MAXLINES];

static int readlines(/*@out@*/ char *lineptr[], int nlines,
                     /*@out@*/ char storage[][MAXLEN]);
static void writelines(/*@in@*/ char *const lineptr[], int nlines);

static void q_sort(char *lineptr[], int left, int right);

int main(void) {
    int nlines;
    char storage[MAXLINES][MAXLEN];
    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        q_sort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000
static int get_line(/*@out@*/ char *s, int lim);

/* readlines: read input lines*/

int readlines(char *lineptr[], int maxlines, char storage[][MAXLEN]) {
    int len, nlines;
    lineptr[0]=NULL;
    nlines = 0;
    while ((len = get_line(storage[nlines], MAXLEN)) > 0) {
        if (nlines > maxlines) {
            break;
        }
        lineptr[nlines]=storage[nlines];
        nlines++;
    }
    return nlines;
}

/*writelines: line output lines */
void writelines(char *const lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s", lineptr[i]);
    }
}

static void swap(char *v[], int i, int j);
/* q_sort: sort v[left] ... v[right] into increasing order */
void q_sort(char *v[], int left, int right) {
    int i, last;

    if (left >= right) {
        return;
    } else {
        swap(v, left, (left + right) / 2);
        last = left;
        for (i = left + 1; i <= right; i++) {
            if (strcmp(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        q_sort(v, left, last - 1);
        q_sort(v, last + 1, right);
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

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
