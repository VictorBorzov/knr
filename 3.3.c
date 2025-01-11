#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 1024

int atoi2(char s[]); /* converts string to integer */

int main(void) {
	int i = 0;
	char s[MAXLEN];
	char c;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	s[i] = '\0';

	i = atoi2(s);
	printf("converted \"%s\" to %i!\n", s, i);
	exit(EXIT_SUCCESS);
}

int atoi2(char s[]) {
	/*
	  skip white space, if any
	  get sign, if any
	  get integer part and convert it
	 */
	int i, res;
	int sign;

	for (i = 0; isspace(s[i]); ++i);

	if (s[i] == '-') {
		sign = -1;
		++i;
	} else {
		sign = 1;
	}

	for (res = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
		res *= 10;
		res += s[i] - '0';
	}

	return res * sign;
}



