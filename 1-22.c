#include <stdio.h>

#define MAXLINE 1024
#define COLUMNLENGTH 4
#define TABLENGTH 2

int getline2(char buffer[], int lim); /* returns length */
int fold(char src[], char result[], int column_length); /* returns length of result */

/* Folds input lines into COLUMNLENGTH column lines */
int main() {
	char line[MAXLINE];
	char folded[MAXLINE];
	int len;

	while ((len = getline2(line, MAXLINE)) > 0) {
		len = fold(line, folded, COLUMNLENGTH);
		printf("%s", folded);
	}
	return 0;
}

int getline2(char buffer[], int lim) {
	char c;
	int len = 0;

	while (len < lim - 1 & (c = getchar()) != EOF & c != '\n') {
		buffer[len++] = c;
	}

	if (c == '\n') {
		buffer[len++] = c;
	}

	buffer[len] = '\0';

	/* printf("getline2: read %s\n", buffer); */
	return len;
}

int fold(char src[], char dest[], int collen) {
	int is, id, line;
	is = id = line = 0;

	while (src[is] != '\0') {
		if (src[is] == '\n') {
			dest[id++] = src[is++];
			line = 0;
		} else if (line > collen - 1 && (src[is] == '\t' || src[is] == ' ')) {
			dest[id++] = '\n';
			++is;
			line = 0;
		} else {
			dest[id++] = src[is++];
			++line;
		}
	}

	dest[id] = '\0';
	return id;
}
