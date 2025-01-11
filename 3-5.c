#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1024

void itob(int n, char s[], int b); /* converts integer to string as b-based */
void reverse(char s[], int n);

int main(void) {
	int i;
	char s[MAXLEN];
	while (scanf("%d", &i) == 1) {
		itob(i, s, 2);
		printf("%d printed as %s\n", i, s);
	}
	exit(EXIT_SUCCESS);
}

void itob(int n, char s[], int b) {
	int i = 0, sign = n, offset;

	// converter expects negative number
	if (sign > 0) {
		n *= -1;
	}


	do {
		offset = n % b;
		if (b > 10 && offset < -9) {
			offset -= 7;
		}
		s[i++] = '0' - offset;
	} while ((n /= b) < 0);

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
