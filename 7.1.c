#include <stdio.h>
#include <math.h>

int main(void) {
	int n;
	char m = 3;
	char d = 10;
	short y = 1997;
	int pad = 30;
	int precision = 2;
	n = printf("%*.*f\n", pad, precision, 123.456);
	n = printf("%f\n", 123.456);
	n = printf("%g\n", pow(2, 8*sizeof(short)));
	n = printf("%.2d/%.2d/%ld\n", d, m, y);
	n = printf("%.5s\n", "Hello, World!");
	printf("printed %d chars\n", n);
}
