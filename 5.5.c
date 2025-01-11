#include <stdio.h>
#include <stdlib.h>

void strcpy2(char *s, char *t); /* copies t to s */

int main(void) {
	printf("%s\n", '\0' ? "true" : "false" );
	printf("%i\n", (int)'\0');
	printf("%i\n", (int)EOF);
	exit(EXIT_SUCCESS);
	char *s = "hehe";
	char *p = "ohoho";
	strcpy2(s, p);
	printf("%s\n", p);
	exit(EXIT_SUCCESS);
}

void strcpy2(char *s, char *t) {
	/* while ((*t++ = *s++) != '\0'); */
	while (*s++ = *t++);
}

int strcmp(char *s, char *t) {
	for (; *s == *t; ++s, ++t) {
		if (*s == '\0')
			return 0;
	}
	return s - t;
}
