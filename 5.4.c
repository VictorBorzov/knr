#include <stdio.h>
#include <stdlib.h>

char *alloc(int);
void afree(char *);

int main(void) {
	char *s = alloc(5);
	int *x = 0, strlen2(char*);
	printf("%i\n", strlen2("hello"));
	printf("%p\n", x);
	printf("%s\n", (x == NULL) ? "true" : "false");
	exit(EXIT_SUCCESS);
	s = "hehe";
	printf("%s\n", s);
	exit(EXIT_SUCCESS);
}

int strlen2(char *s) {
	char *p = s;
	while (*p != '\0')
		++p;
	return p - s;
}
