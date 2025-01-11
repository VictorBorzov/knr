#include <stdio.h>
#include <stdlib.h>

#define dprint(expr) printf("DEBUG: " #expr "=%i\n", expr);
int main(void) {
	int x = 1, y = 2, z[10] = {}, *p;
	double *dp, atof(const char*);
	p = &x;
	dprint(*p);

	y = *p;
	dprint(y);

	*p = z[0];
	dprint(*p);
	dprint(x);

	exit(EXIT_SUCCESS);
}
