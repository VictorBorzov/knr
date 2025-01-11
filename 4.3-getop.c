#include <ctype.h>

int getch(void);
void ungetch(char s[]);

/* getop: get next character of numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	/* not a number */
	if (!isdigit(c) && c != '.') {
		return c;
	}

	/* collect integer part */
	i = 0;
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch()));
	}

	/* collect fraction part */
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()));
	}

	s[i] = '\0';
	if (c != EOF) {
		ungetch(c);
	}
	return NUMBER;
}

