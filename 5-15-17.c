#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* tolower */
#include <string.h> /* strcpy */
#include <sys/param.h> /* max */

#define MAXLEN 1024
#define MAXLINES 5000 /* max #lines to be sorted */

#define NUM 1 /* numerical */
#define DEC 2 /* decreasing order */
#define FOL 4 /* fold cases */
#define DIR 8 /* directory order */

char *lineptr[MAXLINES]; /* pointers to the text lines */

char *alloc(int);
void freebuf(int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int mystrcmp(char *, char *);

static int option = 0;
static int field = 0; /* use nth field (separated by spaces) */

void print_help(void) {
	printf("\nUsage: sort [options]\n");
	printf("\nOPTIONS:\n");
	printf(" -n\tnumeric\n");
	printf(" -f\tcase-insensitive\n");
	printf(" -r\treverse\n");
	printf(" -d\tdirectory\n");
	printf(" -kn\tn field\n");
}

int main(int argc, char *argv[]) {
	int nlines; /* number of input lines read */
	int i;

	for (i = 1; i < argc; ++i) {
		if (*argv[i] != '-') {
			printf("ERROR: unknown argument %s\n", argv[i]);
			print_help();
			exit(EXIT_FAILURE);
		}
		while (*++argv[i]) {
			switch (*argv[i]) {
			case 'n':
				option |= NUM;
				break;
			case 'r':
				option |= DEC;
				break;
			case 'f':
				option |= FOL;
				break;
			case 'd':
				option |= DIR;
				break;
			case 'k':
				field = atoi(++argv[i]);
				break;
			default:
				printf("ERROR: unknown argument %s\n", argv[i]);
				print_help();
				exit(EXIT_FAILURE);
			}
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort2((void**) lineptr, 0, nlines-1,
			(int (*)(void*,void*))(option & NUM ? numcmp : mystrcmp));
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

int numcmp(char *s1, char *s2) {
	double f1 = atof(s1);
	double f2 = atof(s2);
	return (s1 < s2) ? -1 : (s1 > s2) ? 1 : 0;
}

int isdirectory(char c) {
	return isalnum(c) || isspace(c);
}

int mystrcmp(char *s1, char *s2) {
	int i;
	int fn, fl1, fl2; /* field length */

	/* move s1 and s2 to the (field-1)th space position, and set fl = field - (field-1) len */
	for (fn=0; fn < field-1 && *s1; ++s1) {
		fn += *s1 == ' ';
	}
	/* printf("DEBUG: s1 field starts at %c\n", *s1); */
	for (fl1=0; s1[fl1] && s1[fl1] != ' '; ++fl1);
	/* printf("DEBUG: s1 field ends at %c\n", *(s1+fl1)); */

	for (fn=0; fn < field-1 && *s2; ++s2) {
		fn += *s2 == ' ';
	}
	/* printf("DEBUG: s2 field starts at %c\n", *s2); */
	for (fl2=0; s2[fl2] && s2[fl2] != ' '; ++fl2);

	while (*s1 && *s2 && (field == 0 || fl1 > 0 && fl2 > 0)) {
		if (option & DIR) {
			if (!isdirectory(*s1)) {
				++s1;
				continue;
			}
			if (!isdirectory(*s2)) {
				++s2;
				continue;
			}
		}

		if ((option & FOL) && tolower(*s1) != tolower(*s2))
			break;
		else if (*s1 != *s2)
			break;

		if (!*s1 || fl1 == 0)
			return 0;
		++s1;
		++s2;
		if (field > 0) {
			--fl1;
			--fl2;
		}
	}
	return (option & DIR) ? (tolower(*s1) - tolower(*s2)) : *s1 - *s2;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);
	int reverse = (option & DEC) ? -1 : 1;

	/* printf("DEBUG: sort started from %i to %i\n", left, right); */
	if (left >= right) { /* do nothing if an array contains fewer than 2 elements */
		/* printf("DEBUG: array contains fewer than 2 elements, returning...\n"); */
		return;
	}

	/* printf("DEBUG: swapping %i with %i\n", left, (left+right)/2); */
	swap(v, left, (left+right)/2);
	last = left;
	/* printf("DEBUG: success!\n", left, last); */
	for (i = left + 1; i <= right; ++i) {
		/* printf("DEBUG: comparing %i with %i\n", i, left); */
		/* printf("DEBUG: comparing \"%s\" with \"%s\"\n", (char *)v[i], (char *)v[left]); */
		if (((*comp)(v[i], v[left]) * reverse) < 0) {
			/* printf("DEBUG: swapping %i with %i\n", last+1, i); */
			swap(v, ++last, i);
		}
	}
	/* printf("DEBUG: swapping last time %i with %i\n", left, last); */
	swap(v, left, last);

	/* printf("DEBUG: calling recursively\n"); */
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
