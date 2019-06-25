/*
 * Exercise: 6
 * Page: 189
 * The standard library function calloc(n,size) returns a pointer to n objects
 * of size size, with the storage initialized to zero, Write calloc, by calling
 * malloc or by modifying it.
 * */
#define NULL 0
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
