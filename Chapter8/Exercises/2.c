/*
 * Exercise: 2
 * Page: 178
 * Rewrite f_open and _fill_buf with fields instead of explicit bit
 * operations,Compare code size and execution speed.
 * */
/* fields here is interpreted as bit fields since this is one of the uses for
 * bit fields mentioned in chapter 6
 * */
#define NULL 0
#define EOF (-1)
#define BUF_SIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

struct flag_t {
    int read : 1;
    int write : 1;
    int unbuf : 1;
    int eof : 1;
    int err : 1;
};
typedef struct _iobuf {
    int cnt;            /* characters left */
    char *ptr;          /* next character position */
    char *base;         /* location of buffer */
    struct flag_t flag; /* mode of file access */
    int fd;             /* file descriptor */
} FILE_F;
FILE_F _iob[OPEN_MAX] = {
    {0, (char *)NULL, (char *)NULL, {1, 0, 0, 0, 0}, 0},
    {0, (char *)NULL, (char *)NULL, {0, 1, 0, 0, 0}, 1},
    {0, (char *)NULL, (char *)NULL, {0, 1, 1, 0, 0}, 2},
};

#define std_in (&_iob[0])
#define std_out (&_iob[1])
#define std_err (&_iob[2])

int _fill_buf(FILE_F *fp);
int _flush_buf(int, FILE_F *fp);

#define f_eof(p) (((p)->flag.eof) != 0)
#define f_error(p) (((p)->flag.err) != 0)
#define file_no(p) ((p)->fd)

#define get_c(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fill_buf(p))
#define put_c(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flush_buf((x), p))

#define get_char() get_c(std_in)
#define put_char(x) put_c((x), std_out)

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMS 0666

/* f_open: open file, return file ptr */
FILE_F *f_open(char *name, char *mode) {
    int fd;
    FILE_F *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flag.read == 0 && fp->flag.write == 0) {
            break;
        }
    }
    if (fp >= _iob + OPEN_MAX) {
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, NULL)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, NULL);
    }
    if (fd == -1) {
        return NULL;
    }
    fp->fd         = fd;
    fp->cnt        = 0;
    fp->base       = NULL;
    fp->flag.read  = (*mode == 'r') ? 1 : 0;
    fp->flag.write = (*mode == 'r') ? 0 : 1;
    return fp;
}

int _fill_buf(FILE_F *fp) {
    int bufsize;

    if (fp->flag.read == 0 || fp->flag.eof == 1 || fp->flag.err == 1) {
        return EOF;
    }
    bufsize = (fp->flag.unbuf == 1) ? 1 : BUF_SIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag.eof = 1;
        } else {
            fp->flag.err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

#include <stdio.h>
int main(void) {
    int c;
    while ((c = get_char()) != EOF) {
        putchar(c);
    }
    return 0;
}
