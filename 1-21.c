#include <stdio.h>

#define MAXLINE 1024
#define TABLENGTH 4 /* tab length in spaces */

int getline2(char buffer[], int buffer_limit); /* returns length of filled buffer */
int entab(char source[],  int len, char result[]); /* returns length of result with spaces */

int main(void) {
	int len;
	char line[MAXLINE];
	char detabbed[MAXLINE];

	while ((len = getline2(line, MAXLINE)) > 0) {
		entab(line, len, detabbed);
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

	/* printf("DEBUG: getline2: read %s\n", buffer); */
	return i;
}

int entab(char src[],  int len, char dest[]) {
	/* index destination/source */
	int is, id, ns, i;
	is = id = 0;

	while (is < len) {
		ns = 0;
		while (is < len & src[is] == '-' & ns < TABLENGTH) {
			++ns;
			++is;
		}

		if (ns == TABLENGTH) {
			dest[id++] = '\t';
		} else {
			for (i = 0; i < ns; ++i) {
				dest[id++] = '-';
			}
		}

		while (is < len & src[is] != '-') {
			dest[id++] = src[is++];
		}

	}

	dest[id] = '\0';
	/* printf("DEBUG: detabbed to %s\n", dest); */

	return id;
}
