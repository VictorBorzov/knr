#include <stdio.h>

unsigned rightrot(unsigned x, unsigned n);

int main(void) {
	unsigned x, n;

	while (scanf("%x %u", &x, &n) == 2) {
	    printf("0x%0*X\n", (int) sizeof(unsigned) * 2, rightrot(x, n));
	}
	return 0;

	x = 0b101;
	printf("%b\n", ~0);
	for (unsigned n = 0; n < 4; ++n) {
		printf("%b\n", rightrot(x, n));
	}
}

/* rotates x to the right n times */
unsigned rightrot(unsigned x, unsigned n) {

	/*
	  rightrot(101, 0) -> 10000000000000000000000000000101
	  rightrot(101, 1) -> 10000000000000000000000000000010
	  rightrot(101, 2) -> 01000000000000000000000000000001
	  rightrot(101, 3) -> 10100000000000000000000000000000
	 */
	/* printf("n=%d\nx=%b\n", n, x); */
	/* printf("x >> n ~> %b\n", x >> n); */
	/* printf("x << (32 - n) ~> %b\n", x << (32 - n)); */
	n = n % 32;
	return (x >> n) | (x << (32 - n));

}
