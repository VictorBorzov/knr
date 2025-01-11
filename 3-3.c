#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1024

void expand(char s[], char t[]); /* expand range like a-z, leading/trailing '-' works like open range */

int main(void) {
	char c;
	char s[MAXLEN], t[MAXLEN];
	int i = 0;
	for (i = 0; (c = getchar()) != EOF && c != '\n' && i < MAXLEN; ++i) {
		s[i] = c;
	}
	s[i] = '\0';

	expand(s, t);

	for (i = 0; t[i] != '\0'; ++i) {
		putchar(t[i]);
	}

	exit(EXIT_SUCCESS);
}

void expand(char s[], char t[]) {
	int is, it;
	char b, e, c;
	it = is = 0;

	while ((c = s[is]) != '\0') {
		if (c == '-') { // example: -b ~> a-b
			printf("0\n");
			e = s[is+1];
			b = islower(e) ? 'a' : isupper(e) ? 'A' : isdigit(e) ? '0' : '\0';
			is += 2;
		} else if (s[is+2] == '\0') { // example: a- ~> a-z
			printf("1\n");
			b = c;
			e = islower(b) ? 'z': isupper(b) ? 'Z' : isdigit(b) ? '9' : '\0';
			is += 2;
		} else { // example: a-d
			printf("2\n");
			b = c;
			e = s[is+2];
			is += 3;
		}
		printf("b=%c, e=%c\n", b, e);
		for (c = b; c <= e; ++c, ++it) {
			t[it] = c;
		}
	}
	t[it] = '\0';
}
