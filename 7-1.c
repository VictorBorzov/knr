#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int (*changecase)(int);

int main(int argc, char *argv[]) {
	char c;
	changecase f;

	f = strstr(argv[0], "lower") ? tolower : toupper;
	while ((c=getchar()) != EOF) {
		putchar(f(c));
	}

	return 0;
}
