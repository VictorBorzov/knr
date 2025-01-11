#include <stdio.h>

#define MAXLINE 1024

enum boolean { NO, YES };

int strlen(char s[]); /* returns the length of string */
int getline2(char buffer[], int lim); /* returns the length of the filled buffer */

int main() {
	char buffer[MAXLINE];
	while ((len = getline2(buffer, MAXLINE)) > 0) {
		printf("read \"%s\"\n", buffer);
	}
	return 0;
}

int getline2(char buffer[], int lim) {
	char c;
	int i;
	for (i = 0; i < lim - 1; ++i) {
		c = getchar();
		if (c == '\n') {
			break;
		}
		if (c == EOF) {
			break;
		}
		buffer[i] = c;
	}
	if (c == '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	return i;
}

int strlen(char s[]) {
	int len = 0;
	while (s[len] != '\0') {
		s[len] = '1';
		++len;
	}
	return len;
}

