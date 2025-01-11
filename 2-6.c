#include <stdio.h>

/* returns x with n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged */
unsigned setbits0(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned getbits(unsigned x, unsigned p, unsigned n);

unsigned setbits1(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned getmask(unsigned p, unsigned n);

int main() {
	unsigned p = 3, n = 2;
	unsigned x = 0b1011101;
	unsigned y = 0b1000001; // 6 101110 46
	printf("p=%d,n=%d\nx=%b\ny=%b\nr=%b\n", p, n, x, y, setbits1(x, p, n, y));
}

unsigned setbits0(unsigned x, unsigned p, unsigned n, unsigned y) {
	/*
	  x=1011101, p=3, n=2, y=100001 => 1000101

          idea: 10 ++ 00 ++ 101
          0..2 from x + 3..4 from y + 4..from x
          x[p+1..]       get(y, p, n)     x[0..p-n]

	  x >> (p + 1) ++ getbits(y, p, n) ++ getbits(x, p-n, p-n+1)
	       0       ++        10        ++       11111
	  (000000 | 10) == 10 << 5 == 1011111 |
	  (() << (p + 1) | ()) << p-n+1 | ()


          ~(~0 << p) & x        p-n+1 from x's right part
	  +
	  get(y, p, n)          n from y
	  +
	  x >> (p + n)          all - p from x's left

	*/
	return (x >> (p + 1) << n | getbits(y, p, n)) << (p-n+1) | getbits(x, p-n, p-n+1);
}

/* get n bits from position p, p = 0 at the right end */
unsigned getbits(unsigned x, unsigned p, unsigned n) {
	return (x >> (p-n+1)) & ~(~0 << n);
}

/* returns n ones starting with position p from the right */
unsigned getmask(unsigned p, unsigned n) {
	return ~(~0 << n) << (p - n + 1);
}

unsigned setbits1(unsigned x, unsigned p, unsigned n, unsigned y) {
	const unsigned mask = getmask(p, n);
	/*
	  (1) ~0b010 ~> 0b101 // ~mask
	  (2) 0b101 & 0b111 ~> 0b101 // (1) & x
	  (3) 0b101 | 0b101 // (2) | y
	 */
	return (~mask & x) | y;
}
