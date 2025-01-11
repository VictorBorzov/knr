#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1024

void itoa(int i, char s[]); /* converts integer to string */
void reverse(char s[], int n);

int main(void) {
	int i;
	char s[MAXLEN];
	while (scanf("%d", &i) == 1) {
		itoa(i, s);
		printf("%d printed as %s\n", i, s);
	}
	exit(EXIT_SUCCESS);
}

void itoa(int n, char s[]) {
	int i, sign;
	if ((sign = n) < 0) {
		n *= -1;
	}

	i = 0;
	do {
		s[i++] = '0' + (n % 10);
	} while ((n /= 10) > 0);

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
