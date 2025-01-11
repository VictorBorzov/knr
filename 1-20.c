#include <stdio.h>

#define MAXLINE 1024
#define TABLENGTH 2 /* tab length in spaces */

int getline2(char buffer[], int buffer_limit); /* returns length of filled buffer */
int detab(char source[],  int len, char result[]); /* returns length of result with spaces */

int main(void) {
	int len;
	char line[MAXLINE];
	char detabbed[MAXLINE];

	while ((len = getline2(line, MAXLINE)) > 0) {
		detab(line, len, detabbed);
		printf("%s", detabbed);
	}

	return 0;
}

int getline2(char buffer[], int lim) {
	char c;
	int i;

	i = 0;
	while (i < lim - 1 & (c = getchar()) != EOF & c != '\n') {
		buffer[i++] = c;
	}

	if (c == '\n') {
		buffer[i++] = c;
	}

	buffer[i] = '\0';

	return i;
}

int detab(char src[],  int len, char dest[]) {
	/* index destination/source */
	int is, id, i;
	is = id = i = 0;
	while (is < len) {
		if (src[is] == '\t') {
			for (i = 0; i < TABLENGTH; ++i) {
				dest[id++] = ' ';
			}
		} else {
			dest[id++] = src[is];
		}
		++is;
	}

	dest[id] = '\0';

	return id;
}
