#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static char getch(void); /* get character from input or buffer */
static void ungetch(char); /* puts char back to the input */
static int getfloat(float*); /* reads float from the input */

int main(void) {
	float f;
	while (getfloat(&f)) {
		printf("read %f\n", f);
	}
	exit(EXIT_SUCCESS);
}

static int getfloat(float *f) {
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

	/* read integer part */
	for (*f = 0; isdigit(c); c = getch())
		*f = 10 * *f + (c - '0');

	/* read float part */
	int power = 1;
	if (c == '.') {
		while (isdigit(c = getch())) {
			*f = 10 * *f + (c - '0');
			power *= 10;
		}
		*f /= power;
	}
	*f *= sign;

	if (c != EOF)
		ungetch(c);

	return 1;
}

static char b;
static int ib = 0; /* 0 not saved and 1 saved */
static char getch(void) {
	if (ib) {
		ib = 0;
		return b;
	} else {
		return getchar();
	}
}

static void ungetch(char c) {
	b = c;
	ib = 1;
}

