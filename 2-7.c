#include <stdio.h>

unsigned getbits(unsigned x, unsigned p, unsigned n); // get n bits starting from position p
unsigned invert0(unsigned x, unsigned p, unsigned n); // inverts n bits starting from position p
unsigned getmask(unsigned p, unsigned n);
unsigned invert1(unsigned x, unsigned p, unsigned n); // inverts n bits starting from position p

int main(void) {
	unsigned x = 0b1100;
	unsigned p = 2, n = 3;
	printf("x=%b, p=%d, n=%d\n", x, p, n);
	printf("r=%b\n", invert1(x, p, n));
	return 0;
}

/* inverts n bits starting from position p */
unsigned invert0(unsigned x, unsigned p, unsigned n) {
	/*
	  x=111000, p=3, n=2, expect=110100
	  11 [x >> (p+n-1)] ++ 01 [~getbits(x, p, n)] ++ 00 [getbits(x, p-1, p-1)]
	  11 [x >> (p+n-1)] << n | 01 [~getbits(x, p, n)] << (p-1) | 00 [getbits(x, p-1, p-1)]
	  (x >> (p+n-1) << n | ~getbits(x, p, n)) << (p-1) | getbits(x, p-1, p-1)
	*/
	unsigned a = x >> (p+1);
	unsigned b = ~(~0 << n) & ~getbits(x, p, n);
	unsigned c = getbits(x, p-n, p-n+1);
       	printf("%b ++ %b ++ %b\n", a, b, c);
	printf("%b ++ %b =  %b\n", a, b, a << n | b);
	return (a << n | b) << (p-n+1) | c;
}

/* returns n ones starting with position p from the right */
unsigned getmask(unsigned p, unsigned n) {
	return ~(~0 << n) << (p - n + 1);
}

/* inverts n bits starting from position p */
unsigned invert1(unsigned x, unsigned p, unsigned n) {
	unsigned mask = getmask(p, n);
	return x ^ mask;
}


/* get n bits from position p of x starting with right */
unsigned getbits(unsigned x, unsigned p, unsigned n) {
	return (x >> (p-n+1)) & ~(~0 << n);
}
