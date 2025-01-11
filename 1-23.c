#include <stdio.h>

int main() {
	int is, id;
	char c, prev;
	is = id = 0;

	prev = getchar();
	if (prev == EOF)
		return 0;
	c = getchar();
	if (c == EOF)
		return 0;

	while (prev != EOF) {
		if (prev == '"') {
			putchar(prev);
			prev = c;
			c = getchar();
			while (prev != '"') {
				if (prev == '\\') {
					putchar(prev);
					putchar(c);
					prev = getchar();
					c = getchar();
				} else {
					putchar(prev);
					prev = c;
					c = getchar();
				}
			}
		}
		if (prev == '/' && c == '/')
		{
			while (prev != '\n') {
				prev = c;
				c = getchar();
			}
		} else if (prev == '/' && c == '*') {
			while (!(prev == '*' && c == '/') && prev != EOF) {
				prev = c;
				c = getchar();
			}
			if (prev != EOF) {
				prev = getchar();
				c = getchar();
			}
		} else {
			putchar(prev);
			prev = c;
			c = getchar();
		}
	}
}
