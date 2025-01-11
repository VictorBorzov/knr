#include <stdio.h>

#define MAXLINE 1024

int getlinetrim(char buffer[], int lim); /* returns length and -1 if EOF */

int trimline(char source[], int len, char result_buffer[]); /* returns length of trimmed line */
int getline2(char buffer[], int lim); /* returns length */

int main() {
	int len;
	char line[MAXLINE];
	char trimmed[MAXLINE];
	while ((len = getlinetrim(line, MAXLINE)) != -1) {
		if (len > 0) {
			printf("%s\n", line);
		}
	}
	return 0;
}

int getline2(char buffer[], int lim) {
	int i = 0, c;
	while (i < lim - 1 & (c = getchar()) != EOF & c != '\n') {
		buffer[i] = c;
		++i;
	}

	if (c == '\n') {
		buffer[i] = c;
		++i;
	}

	buffer[i] = '\0';
	return 0;
}

int trimline(char from[], int len, char to[]) {
	int i, start;
	/* trim end */
	while (len > 0 && (from[len - 1] == ' ' || from[len - 1] == '\t' || from[len - 1] == '\n')) {
		--len;
	}

	/* trim start */
	start = 0;
	while (start < len && (from[start] == ' ' || from [start] == '\t')) {
		++start;
	}

	for (i = start; i < len; ++i) {
		to[i] = from[i];
	}

	return len - start;
}


int getlinetrim(char buffer[], int lim) {
	int i = 0, c = getchar();
	if (c == EOF) {
		return -1;
	}
	while (c == '\t' || c == ' ') {
		c = getchar();
	}

	while (i < lim - 1 & c != EOF & c != '\n') {
		buffer[i] = c;
		c = getchar();
		++i;
	}

	while (buffer[i] == ' ' || buffer[i] == '\t') {
		--i;
	}

	buffer[i] = '\0';
	return i;
}
