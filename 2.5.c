#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BINLEN 1024

int itobi(char buffer[], int lim, int i); /* fill buffer with binary form of integer, returns length */

int bitoi(char buffer[], int len); /* returns decimal form of binary integer */
unsigned getbits(unsigned x, int p, int n); /* get n bits from prosition p */

int main() {

	int mask = 0xf; // 7 * 8^2 + 1 * 8 + 1 = 7 * 64 + 8 + 1 = 448 + 9 = 457
	/*
	  0711 = 0b111001001
	  0177 = 0b001111111
	  0xF  = 0b000001111
	  0xFF = 0b011111111
	 */
	// x = 10110 p = 2, n = 2 => 11
	int n = 0b10110;
        unsigned x = getbits(n, 3, 4);
        printf("n = %b\n", n);
        printf("getbits(n, 3, 4) = %b\n", x);
        return 0;
	printf("mask = %b\n", mask);
	printf("n = %b(%i)\n", n, n);
	printf("~n = %b(%i)\n", ~n, ~n);
	printf("n << 2 = %b(%i)\n", n << 2, n << 2);
	printf("~n << 2 = %b(%i)\n", ~n << 2, ~n << 2);
	printf("n >> 2 = %b(%i)\n", n >> 2, n >> 2);
	printf("~n >> 2 = %b(%i)\n", ~n >> 2, ~n >> 2);
	return 0;

	FILE *stream;
	char *line;
	size_t len = 0;
	ssize_t nread;
	char buffer[BINLEN];

	if ((nread = getline(&line, &len, stdin)) != -1) {
		int i = bitoi(line, nread - 1);
		printf("i=%i\n", i);
		printf("read \"%s\" as %i\n", line, i);
		if ((nread = getline(&line, &len, stdin)) != -1) {
			int j = bitoi(line, nread - 1);
			printf("read \"%s\" as %i\n", line, j);
			char op = getchar();
			int res = 0;
			if (op == '&') {
				res = i & j;
			} else if (op == '|') {
				res = i | j;
			} else if (op == '^') {
				res = i ^ j;
			} else if (op == '<') {
				res = i << j;
			} else if (op == '>') {
				res = i >> j;
			} else if (op == '~') {
				res = ~i;
			}
			itobi(buffer, BINLEN, res);
			printf("%s\n", buffer);
		}
	}
	free(line);
}

int itobi(char buffer[], int lim, int i) {
	int len = 0, remainder = i % 2, tmp;

	/* get binary form */
	while (len < lim - 1 && (i /= 2) > 0) {
		buffer[len++] = '0' + remainder;
		remainder = i % 2;
	}
	buffer[len++] = '0' + remainder;
	buffer[len] = '\0';

	/* reverse buffer */
	for (i = 0; i < (len / 2); ++i) {
		tmp = buffer[i];
		buffer[i] = buffer[len - 1 - i];
		buffer[len - 1 - i] = tmp;
	}
	return len;
}

int bitoi(char buffer[], int len) {
	int res = 0;
	for (int i = len - 1; i >= 0 && (buffer[i] == '0' || buffer[i] == '1'); --i) {
		res += (buffer[i] - '0') * pow(2, len - 1 - i);
	}
	return res;
}

/* get n bits from position p, p = 0 at the right end */
unsigned getbits(unsigned x, int p, int n) {
	/*
	  -> x = 10110 p = 2, n = 2 => 11
	       -----
             right shift to p - n + 1 => 1011
             make everything zero but right n bits => 0011
             (x >> (p - n + 1)) & ~(~0 << n)
	 */
	return (x >> (p-n+1)) & ~(~0 << n);
}

