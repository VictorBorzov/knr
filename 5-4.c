#include <stdio.h>
#include <stdlib.h>

int strend(char *s, char *t); /* returns 1 if t occurs at the end of s and 0 otherwise */

int main(void) {
	char *s = "test hehe";
	printf("%i\n", strend(s, "hehe"));
	printf("%i\n", strend(s, "test"));
	printf("%i\n", strend(s, "\0"));
	exit(EXIT_SUCCESS);
}

int strend(char *s, char *t) {
	char *ss = s, *ts = t;

	/* move s and t to the end */
	while (*s++);
	while (*t++);

	/* move back until the start or unequality */
	while (*--s == *--t && s > ss && t > ts);

	return s == ss || t == ts; /* moved back to the start of s or t */
}
