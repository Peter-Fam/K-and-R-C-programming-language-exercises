#include <stdio.h>
/*
 * Exercise: 7
 * Page:189
 * malloc accepts a size request without checking its plausibility;
 * free believes that block it is asked to free contains a valid sie field.
 * Improve these routines so they take more pains with error checking.
 * */
/*
 * malloc IMHO, doesn't need any more error checking, cause its only argument is
 * size so the type of error that can happen are:
 *      a negative size ( which can't happened cause the arg is unsigned int)
 *      a zero size (which will behave correctly and return a NULL)
 *      SIZE_MAX which may or may not fail depending on the system
 *
 * so the only thing malloc need is more error description so fprintf(stderr...)
 * */
/*
 * the same thing can be said about free
 * since free access the  ap - 1 address the following  errors can happen:
 *      * ap is not a valid m_alloc header and the ap-1 is not accessable by the
 *      program which will cause a segementation fault
 *      * ap is not a valid m_alloc header and the ap-1 address is accessable by
 *      the program which will cause the program to read a random size, there is
 *      no known way to check for this runtime error
 *      * ap is a valid m_alloc header but size is stored as a negative number
 *      but since free uses a cast the negative number will be read as unsigned
 *      int and this error isn't visiable to the program
 * */
typedef long Align;
union header {
    struct {
        union header *ptr;
        unsigned int size;
    } s;
    Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;
static Header *morecore(unsigned int nunits);

/* malloc: general-purpose storage allocator */
void *m_alloc(unsigned int nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0) {
        return NULL;
    }
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { /*no free list yet*/
        base.s.ptr = freep = prevp = &base;
        base.s.size                = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {     /*big enough */
            if (p->s.size == nunits) { /*exactly */
                prevp->s.ptr = p->s.ptr;
            } else { /*allocate tail end*/
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) {
            if ((p = morecore(nunits)) == NULL) {
                fprintf(stderr, "malloc: can't allocate %d bytes\n", nunits);
                return NULL;
            }
        }
    }
}

#define NALLOC 1024

#include <fcntl.h>
#include <unistd.h>

void free(void *ap);
static Header *morecore(unsigned int nu) {
    char *cp;
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1) {
        return NULL;
    }
    up         = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));
    return freep;
}

/* free: put block ap in free list */
void free(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
        }
    }
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

void *c_alloc(unsigned int n, size_t size) {

    void *p;
    char *ptr;
    if ((p = m_alloc(n * size)) == NULL) {
        return NULL;
    }
    ptr = (char *)p;
    while (ptr < (char *)p + n * size) {
        *ptr++ = (char)0;
    }
    return p;
}
#include <stdio.h>
#include <string.h>
int main(void) {
    char *s   = "tjsljfalkja;f";
    char *p   = NULL;
    char *pre = NULL;
    p         = (char *)m_alloc(strlen(s) + 1);
    pre       = p;
    while (*s) {
        *pre++ = *s++;
    }
    *pre = '\0';
    printf("%s", p);
    free(p);
    printf("%s", p);
    return 0;
}
