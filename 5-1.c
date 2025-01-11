#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EMPTY -10
static char buffer = EMPTY;

static char getch(void);
static void ungetch(char c);
static int getint(int *n); /* reads integer from input */

int main(void) {
	int n;
	while (getint(&n))
		printf("read %d\n", n);
	exit(EXIT_SUCCESS);
}

char getch(void) {
	if (buffer == EMPTY) {
		return getchar();
	} else {
		char c = buffer;
		buffer = EMPTY;
		return c;
	}
}

void ungetch(char c) {
	buffer = c;
}

int getint(int *n) {
	char c;
	int sign;

	/* skip whitespaces */
	while (isspace(c = getch()));

	/* not a number */
	if (!isdigit(c) && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	/* skip sign */
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		c = getch();
		/* not a number */
		if (!isdigit(c)) {
			ungetch(c);
			ungetch(sign > 0 ? '+' : '-');
			return 0;
		}
	}

	/* read number */
	for (*n = 0; isdigit(c); c = getch())
		*n = 10 * *n + (c - '0');
	*n *= sign;

	if (c != EOF)
		ungetch(c);

	return 1;
}
