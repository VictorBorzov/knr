#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024 /* maximum input line length */

int strindex(char source[], char searchfor[]);
int dummy();

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
int main(void) {
	char line[MAXLINE];

	while (getline2(line, MAXLINE) > 0) {
		if (strindex(line, pattern) > 0) {
			printf("%s", line);
		}
	}
	exit(EXIT_SUCCESS);
}

int dummy() {
	return(10);
	return 0;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
	int is, it, i;

	for (is = 0; s[is] != '\0'; ++is) {
		for (it = 0, i = is; t[it] != '\0' && s[i] == t[it]; ++it, ++i);
		if (i > 0 && t[it] == '\0') {
			return is;
		}
	}
	return -1;
}


