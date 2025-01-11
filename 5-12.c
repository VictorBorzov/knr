#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5-11-tabs.c"

#define INPUTLEN 1000000
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

	int m, n;
	char detabm = !strcmp(getfilename(*argv++), "detab");

	m = n = DEFAULTTABSTOPLEN;
	if (*argv && (**argv == '+' || **argv == '-')) { // read -m +n format
		if (**argv == '-') {
			m = atoi(*argv + 1);
		} else {
			n = atoi(*argv+1);
		}

		if (*++argv && **argv == '-') {
			m = atoi(*argv+1);
		} else if (*argv && **argv == '+') {
			n = atoi(*argv+1);
		}

		tabstops[0] = m;
		for (i = 1; i < MAXTABSTOPS; ++i) {
			tabstops[i] = tabstops[i-1] + n;
		}
	} else {  // read tabstops directly
		for (i = 0; i < argc-1; ++i) {
			tabstops[i] = atoi(*argv++);
		}
		for (i = i ? i : 1; i < MAXTABSTOPS; ++i) { // if no tabstops provided set i to 1
			tabstops[i] = tabstops[i-1] + DEFAULTTABSTOPLEN;
		}
	}

	if (detabm)
		detab(tabstops);
	else
		entab(tabstops);

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
