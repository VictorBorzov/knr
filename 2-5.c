#include <stdio.h>
#include <stdlib.h>

int any(char s[], char t[]); /* first location in s where any char from t occurs or -1 */

int main() {
	char c;
	char *line1 = NULL, *line2 = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("Please enter the first string: ");
	if ((nread = getline(&line1, &len, stdin)) != -1) {
		printf("Please enter the second string: ");
		if ((nread = getline(&line2, &len, stdin)) != -1) {
			int i = any(line1, line2);
			printf("found char from second on the position of %i\n", i);
		}
	}

	free(line1);
	free(line2);
	return 0;
}

int any(char s[], char t[]) {
	int i, j;

	for (i = 0; s[i] != '\0'; ++i) {
		j = 0;
		for (j = 0; t[j] != '\0'; ++j) {
			if (s[i] == t[j] && s[i] != '\n') {
				return i;
			}
		}
	}
	return -1;
}
