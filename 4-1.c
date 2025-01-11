#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024 /* maximum input line length */

int getline2(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
int main(void) {
	char line[MAXLINE];
	int i;

	while (getline2(line, MAXLINE) > 0) {
		if ((i=strindex(line, pattern)) > 0) {
			printf("%s:%d", line, i);
		}
	}
	exit(EXIT_SUCCESS);
}

int getline2(char line[], int max) {
	int c, i;

	i = 0;
	while (--max > 0 && (c=getchar()) != EOF && c != '\n') {
		line[i++] = c;
	}

	if (c == '\n') {
		line[i++] = c;
	}

	line[i] = '\0';

	return i;
}

/* strindex: return index of t in s from the end, -1 if none */
int strindex(char s[], char t[]) {
	int it, i;
	size_t is;

	for (is = strlen(s) - 1; s[is] != '\0'; --is) {
		for (it = 0, i = is; t[it] != '\0' && s[i] == t[it]; ++it, ++i);
		if (i > 0 && t[it] == '\0') {
			return is;
		}
	}
	return -1;
}
