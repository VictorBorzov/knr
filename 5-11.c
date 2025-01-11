#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5-11-tabs.c"

#define INPUTLEN 1000000
int getline2(char *s, int lim);
char *getfilename(char *s);

#define MAXTABSTOPS 8
#define DEFAULTTABSTOPLEN 8

void printarr(int arr[], int len) {
	int i;
	putchar('[');
	for (i = 0; i < len; ++i)
		printf("%s%i", i ? ", " : "", arr[i]);
	printf("]\n");
}

int main(int argc, char *argv[]) {
	static char buffer[INPUTLEN] = {};
	static char modified[INPUTLEN] = {};
	static int i, tabstops[MAXTABSTOPS] = { DEFAULTTABSTOPLEN };

	char detabm = !strcmp(getfilename(*argv++), "detab");

	for (i = 0; i < argc-1; ++i) {
		tabstops[i] = atoi(*argv++);
	}
	for (i = i ? i : 1; i < MAXTABSTOPS; ++i) { // if no tabstops provided set i to 1
		tabstops[i] = tabstops[i-1] + DEFAULTTABSTOPLEN;
	}

	while (getline2(buffer, INPUTLEN) > 0) {
		if (detabm)
			detab(buffer, modified, tabstops, MAXTABSTOPS);
		else
			entab(buffer, modified, tabstops, MAXTABSTOPS);
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
