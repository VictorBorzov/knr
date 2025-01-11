#include <stdio.h>

int power(); /* expects base and power n */

int main() {
	char test[1] = "h";
	int j;
	int c;
	for (j = 0; j < 10; ++j) {
		printf("%c", test[j]);
		if (test[j] == '\0') {
			printf("YES");
		}
		putchar('\n');
	}
	return;

	j = 0;
	while ((c = test[j]) != '\0') {
		printf("%c\n", c);
		++j;
	}
	return 0;
	int i;

	for (i = 0; i < 10; ++i) {
		printf("%d %d %d\n", i, power(2, i), power(-3, i));
	}
	return 0;
}


/* power: raise base to n-th power; n >= 0 */
/*        (old-style version */
int power(base, n)
int base, n;
{
	int p;
	for (p = 1; n > 0; --n) {
		p *= base;
	}
	return p;
}

