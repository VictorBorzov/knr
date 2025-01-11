#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 24

char *strncpy2(char *s, const char *ct, int n); /* copy at most n characters of ct to s; return s. Pad with \0's if ct has fewer chars than n */
char *strncat2(char *s, const char *ct, int n); /* concatenate at most n chars of string ct to s, terminate s with \0 and return s */
int strncmp2(char *cs, const char *ct, int n); /* compare at most n chars of string cn to string ct, return -1 when cs < ct, 0 when cs == ct, or >0 when cs > ct) */

int main(void) {
	char s[BUFFERSIZE] = "hello world";
	char *s2 = "world";
	printf("strncmp2(%s,%s)=%i\n", s, s2, strncmp2(s, s2, 5));
	exit(EXIT_SUCCESS);
	putchar('[');
	for (int i = 0; i < BUFFERSIZE; ++i) {
		if (s[i] == '\0') {
			printf("\\0");
		} else {
			putchar(s[i]);
		}
		if (i < BUFFERSIZE - 1) {
			printf(", ");
		} else {
			printf("]\n");
		}
	}
	exit(EXIT_SUCCESS);
}

char *strncpy2(char *s, const char *ct, int n) {
	char *st = s;
	while (n-- > 0 && (*st++ = *ct++));
	while (n-- > 0)
		*st++ = '\0';
	return s;
}

char *strncat2(char *s, const char *ct, int n) {
	char *st = s;

	/* move to the end of st */
	while (*st++);
	--st;
	/* copy n chars from ct to st */
	while (n-- > 0 && (*st++ = *ct++));
	/* pad the rest with \0s */
	while (n-- > 0)
		*st++ = '\0';
	return s;
}

int strncmp2(char *cs, const char *ct, int n) {
	while (n-- > 0 && *cs++ == *ct++);
	return *cs - *ct;
}
