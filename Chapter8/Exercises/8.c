#include <stdio.h>
/*
 * Exercise: 8
 * Page:189
 * Write a routine bfree(p,n) that free an arbitrary block p
 * of n characters into the free list maintained by m_alloc and free , By using
 * bfree, a user can add a static or external array to the free list at any
 * time.
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
void bfree(void *p, unsigned int n) {
    Header *header;

    if (n <= sizeof(Header)) {
        fprintf(stderr, "bfree: static block p of %u characters is too small\n",
                n);
        return;
    }
    header         = (Header *)p;
    header->s.size = n / sizeof(Header);
    free((void *)header + 1);
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
