#include <stdio.h>

#define BUFSIZE 1024 /* max buffer length */

int pos = 0; /* next free position in buffer */
char buffer[BUFSIZE];

char getch(void) {
	return (pos == 0) ? getchar() : buffer[pos--];
}

void ungetch(char c) {
	if (pos >= BUFSIZE) {
		printf("ERROR: ungetch - too many characters\n");
	}
	buffer[pos++] = c;
}





