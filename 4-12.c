#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 20

int itoa(int, char[]); /* convert an integer into as string, returns length */

int main(void) {
	char buffer[BUFFERSIZE];
	int i = -251;
	int size = itoa(i, buffer);
	printf("i=%i,size=%i,buffer=%s\n", i, size, buffer);
	exit(EXIT_SUCCESS);
}

int itoa(int n, char s[]) {
	/*
	  convert the n - n % 10 into string, get the length
	  write n % 10 to s[length]

	 */
	int i;
	i = 0;
	if (n / 10 > 0) {
		i = itoa(n / 10, s);
	} else if (n < 0) {
		printf("DEBUG: writing %c to s[%i]\n", '-', i);
		s[i++] = '-';
		n *= -1;
	}
	printf("DEBUG: writing %c to s[%i]\n", '0' + n % 10, i);
	s[i++] = '0' + n % 10;
	s[i] = '\0';
	return i;
}


