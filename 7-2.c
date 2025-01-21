#include <stdio.h>
#include <ctype.h>

#define LINELEN 80

int main(void) {
	int linelen;
	char c;

	for (linelen = 0; (c=getchar()) != EOF; ++linelen) {
		if (linelen == LINELEN) {
			putchar('\n');
			linelen = 0;
		}

		if (isgraph(c) || isspace(c))
			putchar(c);
		else {
			printf("%.3X", c);
			linelen += 2;
		}

	}
}
