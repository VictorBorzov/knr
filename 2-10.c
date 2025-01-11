#include <stdio.h>

char lower(char c); // returns lowercase character

int main(void) {
	char c[3] = { 'a', 'b', 'c' };
	for (int i = 0; i < 3; ++i) {
		printf("%c%s", c[i], i == 2 ? "" : ", ");
	}
	return 0;
}

char lower(char c) {
	return (c >= 'A' && c <= 'Z') ? 'a' + c - 'A' : c;
}
