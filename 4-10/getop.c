#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"

/* parse s[b..end-1] */
void parse(const char s[], int b, int end) {
	int i; /* current position */
	char word[MAXOP]; /* for a number or command */
	word[0] = '+'; /* because in the beginning I parse number */
	int j = 1; /* current position of word */

	/* skip leading spaces */
	for (i = b; i < end && isspace(s[i]); ++i);

	/* override sign when next char is digit */
	if (i < end-1 && (s[i] == '-' || s[i] == '+') && isdigit(s[i+1])) {
		word[0] = s[i++];
	}

	/* collect integer part if exists */
	if (isdigit(s[i]))
		while (i < end && isdigit(word[j++] = s[i++]));
	/* collect fraction part if exists */
	if (s[i] == '.') /* collect fraction part */
		while (i < end && isdigit(word[j++] = s[i++]));
	word[j] = '\0';
	/* number found */
	if (j > 1) {
		/* printf("DEBUG: got number %s\n", word); */
		hnum(atof(word));
		parse(s, i, end);
		return;
	}

	/* parse command/operator or variable if a char [a-z] */
	if (islower(s[i]) && (i == end-1 || isspace(s[i+1]) || isdigit(s[i+1]))) {
		/* printf("DEBUG: got var %c\n", s[i]); */
		hvar(s[i]);
		parse(s, i+1, end);
		return;
	}

	/* parse word from i to j till space as a command/operator */
	for (j=0; i < end && !isspace(s[i]); ++i, ++j) {
		word[j] = s[i];
	}
	word[j] = '\0';
	if (j > 0) {
		/* printf("DEBUG: got command %s\n", word); */
		hcom(word);
		parse(s, i, end);
	}
}

/* compare s1 with s2 */
int strcmp(char s1[], char s2[]) {
	for (int i = 0; i < MAXOP; ++i) {
		if (s1[i] == '\0' && s2[i] == '\0') {
			return 1;
		} else if (s1[i] != s2[i]) {
			return 0;
		}
	}
	return 1;
}

