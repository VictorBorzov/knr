#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort2(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
	int nlines; /* number of input lines read */

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort2(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("ERROR: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000 /* max length of any input line */

int getline2(char *, int);
char *alloc(int);

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

int getline2(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*(s+i) = getchar()) != EOF && *(s+i) != '\n'; ++i);
	if (*(s+i) == '\n') {
		++i;
	}
	*(s+i) = '\0';
	return i;
}

void qsort2(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right) { /* do nothing if an array contains fewer than 2 elements */
		return;
	}
	swap(v, left, (left+right)/2);
	last = left;
	for (i = left + 1; i <= right; ++i) {
		if (strcmp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort2(v, left, last-1);
	qsort2(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

