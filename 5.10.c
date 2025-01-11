#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLENGTH 8
#define SPACECHAR '-'
int entab(char *s, char *t); /* copies characters from s to t changing spaces to tabs */
int detab(char *s, char *t); /* copies characters from s to t changing tabs to spaces */

#define INPUTLEN 1000000
int getline2(char *s, int lim);
char *getfilename(char *s);

int main(int argc, char *argv[]) {
	static char buffer[INPUTLEN] = {};
	static char modified[INPUTLEN] = {};

	char detabm = !strcmp(getfilename(*argv++), "detab");
	printf("%i\n", detabm);

	while (getline2(buffer, INPUTLEN) > 0) {
		if (detabm)
			detab(buffer, modified);
		else
			entab(buffer, modified);
		printf("%s", modified);
	}
	exit(EXIT_SUCCESS);
}

char *getfilename(char *s) {
	char *end;
	for (end=s; *end; ++end);
	while (*end != '/' && end != s)
		--end;
	if (*end == '/')
		++end;
	return end;
}

int getline2(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*s = getchar()) != EOF && *s != '\n'; ++s, ++i);
	if (*s == '\n') {
		++s, ++i;
	}
	*s = '\0';
	return i;
}

int entab(char *s, char *t) {
	char newline = 1, tablen = 0, *start = t;
	int i;

	while (*s) {
		for (tablen = 0; *s == SPACECHAR && tablen < TABLENGTH; ++s, ++tablen);
		if (tablen == TABLENGTH) {
			*t++ = '\t';
		} else {
			for (i = 0; i < tablen; ++i) {
				*t++ = SPACECHAR;
			}
		}

		while (*s && *s != SPACECHAR) {
			*t++ = *s++;
		}
	}
	*t = '\0';
	return t - start;
}

int detab(char *s, char *t) {
	char *start = t;
	int i;

	while (*s) {
		switch (*s) {
		case '\t':
			for (i = 0; i < TABLENGTH; ++i)
				*t++ = SPACECHAR;
			break;
		default:
			*t++ = *s;
			break;
		}
		++s;
	}
	*t = '\0';
	return t - start;
}
