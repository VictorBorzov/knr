#include "stdio.h"
#include "stdlib.h"
#include "4-13-test.h"

#define MAXLEN 1024

void reverse(char[], int, int); /* reverse string in place */

int main(void) {
	printf("%i\n", sum(34, 35));
	exit(EXIT_SUCCESS);
	char s[MAXLEN];
	int i;
	for (i = 0; i < MAXLEN && (s[i] = getchar()) != EOF; ++i);
	s[i] = '\0';
	reverse(s, 0, i-1);
	printf("%s\n", s);
	exit(EXIT_SUCCESS);
}

void swap(char s[], int a, int b) {
	char tmp;
	tmp = s[a];
	s[a] = s[b];
	s[b] = tmp;
}

void reverse(char s[], int b, int e) {
	if (b < e) {
		swap(s, b, e);
		reverse(s, b+1, e-1);
	}
}

