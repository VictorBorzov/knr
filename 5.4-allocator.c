#include <stdio.h>

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

/* returns pointer to n characters */
char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		printf("ERROR: No space available\n");
		return 0;
	}
}

/* free storage pointed to p */
void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
		allocp = p;
	} else {
		printf("ERROR: %p is out of buffer\n", p);
	}
}
