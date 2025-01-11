#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES 145000 /* max #lines to be sorted */
#define LINELEN 1000
/* this can be static char buffer inside main, but not char buffer because of stack overflow */
/* static arrays are stored separately, not on stack */
char buffer[MAXLINES*LINELEN] = {}; /* pointers to text lines */
int readlinesstat(char lines[], int nlines, int linelen);

char buffer2d[MAXLINES][LINELEN] = {}; /* pointers to text lines */
int readlinesstat2d(char lines[][LINELEN], int nlines, int linelen);

int main(void) {
	int nlines; /* number of input lines read */
	clock_t tic, toc; /* measure seconds doesn't make sense because execution takes <1 sec */

	printf("mode     clocktics     #lines\n");
	printf("----     ---------    -------\n");

	tic = clock();
	nlines = readlinesstat2d(buffer2d, MAXLINES, LINELEN);
	toc = clock();
	printf("stat     %9ld   %8d\n", toc-tic, nlines);
}

int getlinestat(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*(s+i) = getchar()) != EOF && *(s+i) != '\n'; ++i);
	if (*(s+i) == '\n') {
		++i;
	}
	*(s+i) = '\0';
	return i;
}

int readlinesstat(char lines[], int maxlines, int linelen) {
	int len, iline;

	for (iline = 0; (len = getlinestat(&lines[iline*linelen], linelen)) > 0; ++iline) {
		if (iline >= maxlines) {
			return -1;
		} else {
			lines[iline*linelen-1] = '\0'; /* delete newline */
		}

	}
	return iline;
}

int readlinesstat2d(char lines[][LINELEN], int maxlines, int linelen) {
	int len, iline;

	for (iline = 0; (len = getlinestat(lines[iline], linelen)) > 0; ++iline) {
		if (iline >= maxlines) {
			return -1;
		} else {
			lines[iline][linelen-1] = '\0'; /* delete newline */
		}

	}
	return iline;
}
