#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

typedef long Align;          	                         /* for alingment to long boundary */

typedef union header {                                                     /* block header */
	struct {
		union header *ptr;                           /* next block if on free list */
		size_t size;	                                     /* size of this block */
	} s;
	Align x;		                              /* force alignment of blocks */
} Header;

static Header base;            	                              /* empty list to get started */
static Header *freep = NULL;	                                     /* start of free list */

static Header *morecore(size_t);
static void dprint(FILE *);

void *mmalloc(size_t);
void mfree(void *);
void *mcalloc(size_t, size_t);

void dprint(FILE *f)
{
	return;
	Header *p = freep;
	int j;

	if (freep == NULL) {
		fprintf(f, "DEBUG: freep = NULL\n");
		return;
	}

	fprintf(f, "DEBUG: freep = %p[%d]", p, p->s.size);
	for (p = freep; p != freep; p = p->s.ptr) {
		fprintf(f, " -> %p[%d]", p, p->s.size);
	}
	fprintf(f, " \n");
}

/* malloc: general-purpose storage allocator */
void *mmalloc(size_t nbytes) {
	Header *p, *prevp;
	size_t nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	if ((prevp=freep) == NULL) {                                   /* no free list yet */
		fprintf(stderr, "DEBUG: mmalloc: there is no free list yet, setting it to base\n");
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	fprintf(stderr, "DEBUG: mmalloc: memory looks like:\n");
	dprint(stderr);
	for (p = prevp->s.ptr; ; prevp=p, p=p->s.ptr) {
		fprintf(stderr,
			"DEBUG: mmalloc: checking if block %p[%d] is bigger than %d\n",
			p,
			p->s.size,
			nunits);
		if (p->s.size >= nunits) {                                   /* big enough */
			if (p->s.size == nunits) {                              /* exactly */
				fprintf(stderr, "DEBUG: mmalloc: matched exatcly\n");
				prevp->s.ptr = p->s.ptr;
			} else {                                      /* allocate tail end */
				fprintf(stderr, "DEBUG: mmalloc: block is bigger (%d)\n",
					p->s.size);
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			fprintf(stderr, "DEBUG: mmalloc: now memory looks like:\n");
			dprint(stderr);
			p->s.ptr = NULL;
			return p+1;
		}

		if (p == freep) {                              /* wrapped around free list */
			fprintf(stderr, "DEBUG: mmalloc: all list checked, asking for more\n");
			if ((p=morecore(nunits)) == NULL) {
				fprintf(stderr, "ERROR: mmalloc: seems like none left\n");
				return NULL;                                  /* none left */
			}
			fprintf(stderr, "DEBUG: mmalloc: now memory looks like:\n");
			dprint(stderr);
		}
		fprintf(stderr, "DEBUG: mmalloc: block is smaller, checking next\n");
	}
}

void *mcalloc(size_t nmemb, size_t size) {
	void *result;
	/* overflow */
	if (INT_MAX % nmemb < size) {
		return NULL;
	}

	result = mmalloc(nmemb * size);
	if (result != NULL)
		memset(result, 0, nmemb * size);

	return result;
}

#define NALLOC 1                                           /* minimum #units to request */

/* morecore: ask system for more memory */
Header *morecore(size_t nu) {
	char *cp;
	void *sbrk(intptr_t);
	Header *up;

	fprintf(stderr, "DEBUG: morecore: asking system for %d units\n", nu);
	if (nu < NALLOC) {
		fprintf(stderr, "DEBUG: morecore: %d < %d, so asking for ", nu, NALLOC);
		nu = NALLOC;
		fprintf(stderr, "%d\n", nu);
	}

	fprintf(stderr, "DEBUG: morecore: sbrk %d bytes\n", nu * sizeof(Header));
	errno = 0;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1) {                                        /* no space at all */
		fprintf(stderr, "ERROR: morecore: no space at all\n");
		perror("ERROR: morecore: sbrk");
		return NULL;
	}

	fprintf(stderr, "DEBUG: morecore: success!\n");
	up = (Header *) cp;
	up->s.size = nu;
	fprintf(stderr, "DEBUG: morecore: setting header at %p size %d\n", up, up->s.size);
	fprintf(stderr, "DEBUG: morecore: block starting at %p\n", up+1);
	mfree((void *) (up + 1));

	return freep;
}

/* free: put block a in free list */
void mfree(void *a) {
	Header *bp, *p;		                /* header of a block and where to place it */

	fprintf(stderr, "DEBUG: mfree: adding memory %p to the free list\n", a);
	bp = (Header *) a - 1;                                    /* point to block header */
	fprintf(stderr, "DEBUG: mfree: this is a block %p[%d]\n", bp, bp->s.size);

	/* find block p where b belongs, check for the right/left-most inside */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
			if (bp > p)
				fprintf(stderr, "DEBUG: mfree: this is the rightmost block\n");
			else
				fprintf(stderr, "DEBUG: mfree this is the leftmost block\n");
			break;                	   /* freed block at start or end of arena */
		}
	}

	fprintf(stderr, "DEBUG: mfree: closest block is %p[%d]\n", p, p->s.size);
	if (bp + bp->s.size == p->s.ptr) {                              /* join to upper nbr */
		fprintf(stderr, "DEBUG: mfree: joining %p to upper %p[%d]\n", bp, p, p->s.size);
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		fprintf(stderr, "DEBUG: mfree: setting next of %p[%d] to the next of %p\n", p, p->s.size, bp);
		bp->s.ptr = p->s.ptr;
		fprintf(stderr, "DEBUG: mfree: success\n");
	}


	if (p + p->s.size == bp) {                                     /* join to lower nbr */
		fprintf(stderr, "DEBUG: mfree: joining %p to lower %p[%d]\n", bp, p, p->s.size);
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		fprintf(stderr, "DEBUG: mfree: setting %p to the next of %p[%d]\n", bp, p, p->s.size);
		p->s.ptr = bp;
	}
	freep = p;
	fprintf(stderr, "DEBUG: mfree: new freep header is %p\n", freep);
}

int main(void) {
	char *s1, *s2, *s3;
	int n = 5;
	s1 = mcalloc(n, sizeof(char));
	s2 = mcalloc(n, sizeof(char));
	s3 = mcalloc(n, sizeof(char));
	s1 = strcpy(s1, "hello");
	s2 = strcpy(s2, "world");
	s3 = strcpy(s3, "test");
	fprintf(stdout, "s1=%s,s2=%s,s3=%s\n", s1, s2, s3);
	mfree(s1);
	fprintf(stdout, "s1 has been freed\n");
	fprintf(stdout, "s2=%s,s3=%s\n", s2, s3);
	mfree(s3);
	fprintf(stdout, "s3 has been freed\n");
	fprintf(stdout, "s2=%s\n", s2);
	mfree(s2);
}
