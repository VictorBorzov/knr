#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strcpy */
#include <sys/param.h> /* max */

#define MAXLEN 1024
#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to the text lines */

char *alloc(int);
void freebuf(int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);

int main(int argc, char *argv[]) {
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 0;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort2((void**) lineptr, 0, nlines-1,
			(int (*)(void*,void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
	exit(EXIT_SUCCESS);
}

int getline2(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*(s+i) = getchar()) != EOF && *(s+i) != '\n'; ++i);
	if (*(s+i) == '\n') {
		++i;
	}
	*(s+i) = '\0';
	return i;
}

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline2(line, MAXLEN)) > 0) {
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

int numcmp(const char *s1, const char *s2) {
	double f1 = atof(s1);
	double f2 = atof(s2);
	return (s1 < s2) ? -1 : (s1 > s2) ? 1 : 0;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);

	if (left >= right) { /* do nothing if an array contains fewer than 2 elements */
		return;
	}
	swap(v, left, (left+right)/2);
	last = left;
	for (i = left + 1; i <= right; ++i) {
		if ((*comp)(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort2(v, left, last-1, comp);
	qsort2(v, last+1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j) {
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


/***************************************************
 *********************ALLOCATOR.h*******************
***************************************************/

#define BUFFERSIZE 1000000
static char buffer[BUFFERSIZE] = {};
static int bp = 0;

char *alloc(int size) {
	if (bp + size > BUFFERSIZE) {
		printf("ERROR: out of memory!\n");
		return 0;
	}
	bp += size;
	return &buffer[bp-size];
}

void freebuf(int size) {
	bp = MAX(0, bp-size);
}
