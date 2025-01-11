#include <stdio.h>
#include <stdlib.h>

void strcat2(char *s, char *t); /* copies t to the end of s */

int main(void) {
	char s[32] = "hello";
	char *t = " world";
	strcat2(s, " hehe world");
	printf("%s\n", s);
	exit(EXIT_SUCCESS);
}

void strcat2(char *s, char *t) {
	while (*s++); /* find the next after '\0' char in s */
	--s; /* '\0' has to be overriden */
	while (*s++ = *t++); /* copy until find '\0' inclusively */
}
