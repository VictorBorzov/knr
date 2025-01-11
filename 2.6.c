#include <stdio.h>

int bitcount(unsigned x); // counts ones in x

int main(void) {
	unsigned x;
	while (scanf("%b", &x) == 1) {
		printf("%d\n", bitcount(x));
	}
}

/* counts ones in x */
int bitcount(unsigned x) {
	/*
	  -x == ~x - 1
	  -x + 1 == ~x
	  x == ~(-x + 1)
	  x == -(~x - 1)
	 */

	int b;

	for (b = 0; x != 0; x &= (x - 1)) {
		++b;
	}

	return b;
}
