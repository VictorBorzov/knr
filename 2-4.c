#include <stdio.h>
#include <stdlib.h>

void squeeze(char s[], char c); /* delete all c from s */
void squeeze2(char s[], char t[]); /* delete all t chars from s */
void strcat2(char s[], char t[]); /* assumes that s has enough space for s + t */

enum boolean { TRUE, FALSE };

int main() {
	char c;
	char *line1 = NULL, *line2 = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("Please enter the first string: ");
	if ((nread = getline(&line1, &len, stdin)) != -1) {
		printf("Please enter the second string: ");
		if ((nread = getline(&line2, &len, stdin)) != -1) {
			squeeze2(line1, line2);
			printf("removed all second's chars from the first one:\n%s", line1);
		}
	}

	free(line1);
	free(line2);
	return 0;
}

void squeeze(char s[], char c) {
	int i, j;

	for (i = j = 0; s[i] != '\0'; ++i) {
		if (s[i] != c) {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

void squeeze2(char s[], char t[]) {
	int i, j, k;
	enum boolean found = FALSE;

	for (i = j = 0; s[i] != '\0'; ++i) {
		found = FALSE;
		k = 0;
		while (t[k] != '\0') {
			if (s[i] == t[k++]) {
				found = TRUE;
				break;
			}
		}

		if (found == FALSE) {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

void strcat2(char s[], char t[]) {
	int i, j;
	i = j = 0;
	/* find end of s */
	while (s[i] != '\0') {
		++i;
	}
	while ((s[i++] = t[j++]) != '\0') {}
}
