#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES 145000 /* max #lines to be sorted */
#define LINELEN 1000

char *lineptr[MAXLINES]; /* pointers to text lines */
int readlinesdyn(char *lineptr[], int nlines);

int main(void) {
	int nlines; /* number of input lines read */
	clock_t tic, toc; /* measure seconds doesn't make sense because execution takes <1 sec */

	printf("mode     clocktics     #lines\n");
	printf("----     ---------    -------\n");

	tic = clock();
	nlines = readlinesdyn(lineptr, MAXLINES);
	toc = clock();
	printf("dyn      %9ld   %8d\n", toc-tic, nlines);
}

char *alloc(int);

int getlinedyn(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*(s+i) = getchar()) != EOF && *(s+i) != '\n'; ++i);
	if (*(s+i) == '\n') {
		++i;
	}
	*(s+i) = '\0';
	return i;
}

int readlinesdyn(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[LINELEN];

	nlines = 0;
	while ((len = getlinedyn(line, LINELEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}
