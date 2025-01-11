#include <stdio.h>

#define BUFSIZE 1024 /* max buffer length */

int getline2(char buffer[], int lim) {
	int i;
	char c;
	for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
		buffer[i] = c;
	}
	if (c == '\n') {
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return i;
}
