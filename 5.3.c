#include <stdio.h>
#include <stdlib.h>

#define PP(x) printf(#x "=%p *" #x "=%i\n", x, *x);

void add2(int *a);

int strlen2(char*);

int main(void) {
	char *s = "hello!";
	printf("%s has the length %i\n", s, strlen2(s));
	exit(EXIT_SUCCESS);

	int a[] = { 1, 2, 3 }, b[] = { }, *x;
	// b = a; WRONG
	x = a;
	add2(a);
	exit(EXIT_SUCCESS);
	PP(b);
	PP(x);
	PP(a);
	x++;
	PP(x);
	PP(a);
	// a++; WRONG
	PP(a);
	// a = x; WRONG
	exit(EXIT_SUCCESS);
}

void add2(int *a) {
	int x = 3, *y = &x;
	PP(a);
	PP(y);
	printf("==================================================\n");
	a = y;
	PP(y);
	PP(y);
}

int strlen2(char *s) {
	int n;
	for (n = 0; *s != '\0'; ++s, ++n);
	return n;
}
