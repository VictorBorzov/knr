#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLEN 20 /* 2**63 has 20 digits including - */

void itoa(int i, char s[]); /* converts integer to string */
void reverse(char s[], int n);

int main(void) {
	int i;
	printf("%d\n", INT_MIN);
	printf("%d\n", INT_MAX);

	char s[MAXLEN];
	i = INT_MIN;
	itoa(i, s);
	printf("%d printed as %s\n", i, s);

	i = INT_MAX;
	itoa(i, s);
	printf("%d printed as %s\n", i, s);

	i = -INT_MAX;
	itoa(i, s);
	printf("%d printed as %s\n", i, s);

	while (scanf("%d", &i) == 1) {
		itoa(i, s);
		printf("%d printed as %s\n", i, s);
	}
	exit(EXIT_SUCCESS);
}

void itoa(int n, char s[]) {
	int i = 0, sign = n;

	// converter expects negative number
	if (sign > 0) {
		n *= -1;
	}

	do {
		s[i++] = '0' - (n % 10);
	} while ((n /= 10) < 0);

	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s, i);
}

void reverse(char s[], int n) {
	int i, tmp;
	for (i = 0; i < n/2; ++i) {
		tmp = s[i];
		s[i] = s[n - i - 1];
		s[n - i - 1] = tmp;
	}
}
