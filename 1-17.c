#include <stdio.h>

#define MAXLINE 16

int getline1(char line[], int lim);
void skipline();

int main() {
	int len;
	char line[MAXLINE];
	while ((len = getline1(line, MAXLINE)) != 0) {
		if (line[len - 1] != '\n') {
			printf("Only strings less than %i are supported! skipping...\n", MAXLINE);
			skipline();
			continue;
		}
		if (len > 8) {
			printf("%s\n", line);
		}
	}
	return 0;
}

int getline1(char line[], int lim) {
	int i = 0, c;
	while (i < lim - 1 & (c = getchar()) != EOF & c != '\n') {
		line[i] = c;
		++i;
	}

	if (c == '\n') {
		line[i] = c;
		++i;
	}

	line[i] = '\0';
	return i;
}

void skipline() {
	int c = getchar();
	while (c != EOF & c != '\n') {
		c = getchar();
	}
}



