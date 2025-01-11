#include <stdio.h>

#define MAXINPUT 1024

int getline2(char buffer[], int lim); /* returns length */
void reverse(char s[], int len); /* reverse s in place till the last char */

int main() {
	int len = 0;
	char line[MAXINPUT];

	while ((len = getline2(line, MAXINPUT)) != 0) {
		reverse(line, len);
		printf("%s", line);
	}
	return 0;
}

int getline2(char buffer[], int lim) {
	int i = 0;
	char c;
	while (i < lim - 1 & (c = getchar()) != EOF & c != '\n') {
		buffer[i++] = c;
	}

	if (c == '\n') {
		buffer[i++] = c;
	}

	buffer[i] = '\0';
	return i;
}

void reverse(char line[], int len) {
	int i;
	char c;

	if (len < 2) {
		return;
	}
	if (line[len - 1] == '\n') {
		--len;
	}


	// len=2: li E { 0, 1 }; i E { 0 }; i <-> len - 1 - i
	// len=3: li E { 0, 1, 2 }; i E { 0 }; i <-> len - 1 - i
	// len=4: li E { 0, 1, 2, 3 }; i E { 0, 1 }; i <-> len - 1 -i
	// len=5: li E { 0, 1, 2, 3, 4 }; i E { 0, 1, 2 }; i <-> len - 1 - i
	for (i = 0; i < len / 2; ++i) {
		c = line[i];
		line[i] = line[len - 1 - i];
		line[len - 1 - i] = c;
	}
}
