#include <stdio.h>

#define MAXLINE 4 /* maximum line input length */

int getline1(char line[], int maxline);
void copy(char to[], char from[]);
void skipline();

int main() {
	int c;
	int len; /* current line length */
	int max; /* maximum length seen so far */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE]; /* longest line saved here */

	max = 0;
	while ((len = getline1(line, MAXLINE)) != 0) {
		if (line[len - 1] != '\n') {
			printf("Only lines less than %i are accepted (with '\\n')\n", MAXLINE);
			skipline();
			continue;
		}

		if (len > max) {
			copy(longest, line);
			max = len;
		}
	}

	if (max > 0) {
		printf("%s\n", longest);
	}

	return 0;
}

/* skipline: read a line untill \n from input */
void skipline() {
	int c = getchar();
	while (c != EOF && c != '\n') {
		c = getchar();
	}
}

/* getline1: read a line into s, return length */
int getline1(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 & (c = getchar()) != EOF & c != '\n'; ++i) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}
