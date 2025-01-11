#include <stdio.h>
#include <stdlib.h>

int htoi(char s[]); /* reads hex int from string */

int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	while ((nread = getline(&line, &len, stdin)) != -1) {
		int s = htoi(line);
		printf("decimal value is %i\n", s);
	}
	free(line);
	return 0;
}

int htoi(char s[]) {
	int i = 0, n = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
		i = 2;
	}
	while (s[i] != '\0') {
		if (s[i] >= '0' && s[i] <= '9') {
			n = 16 * n + s[i] - '0';
		} else if (s[i] >= 'a' && s[i] <= 'f') {
			n = 16 * n + 10 + s[i] - 'a';
		} else if (s[i] >= 'A' && s[i] <= 'F') {
			n = 16 * n + 10 + s[i] - 'A';
		} else {
			break;
		}
		++i;
	}
	return n;
}
