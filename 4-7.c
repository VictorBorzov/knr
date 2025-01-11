#include <stdio.h>

#define BUFSIZE 1024 /* max buffer length */
#define DEBUG 0

char buffer[BUFSIZE];
int bufp = 0; /* next free position in buffer */

char getch(void);
void ungetch(char);

void ungets(char[]); /* ungetch an entire string */

void print(void);

int main(void) {
	char c;
	char buf[BUFSIZE];
	int i, n;
	for (n = 0; (c = getch()) != EOF; ++n) {
		putchar(c);
		buf[n] = c;
	}
	buf[n] = '\0';
	print();

	/* for (i = 0; i < n; ++i) { */
	/* 	ungetch(buf[i]); */
	/* } */
	ungets(buf);
	print();

	for (i = 0; (c = getch()) != EOF; ++n) {
		putchar(c);
		buf[n] = c;
	}
	print();
}


void print(void) {
	putchar('[');
	for (int i = 0; i < bufp; ++i) {
		printf("%c%s", buffer[i], (i < bufp-1) ? ", " : "");
	}
	putchar(']');
	putchar('\n');
}

char getch(void) {
	char c;
	if (bufp > 0) {
		c = buffer[bufp-1];
		if (DEBUG) {
			if (c == EOF || c == '\n') {
				printf("DEBUG: getch returning buffered char %s\n",
					(c == EOF) ? "EOF" : (c == '\n') ? "\\n" : "");
			} else {
				printf("DEBUG: getch returning buffered char %c\n", c);
			}
		}
		return buffer[--bufp];
	} else {
		c = getchar();
		if (DEBUG) {
			if (c == EOF || c == '\n') {
				printf("DEBUG: getch returning input char %s\n",
					(c == EOF) ? "EOF" : (c == '\n') ? "\\n" : "");
			} else {
				printf("DEBUG: getch returning input char %c\n", c);
			}
		}
		return c;
		// return getchar();
	}
}

void ungetch(char c) {
	if (DEBUG) {
		if (bufp >= BUFSIZE) {
			printf("ERROR: ungetch - too many characters\n");
		}
		if (c == EOF || c == '\n') {
			printf("DEBUG: ungetch buffering %s\n",
				(c == EOF) ? "EOF" : (c == '\n') ? "\\n" : "");
		} else {
			printf("DEBUG: ungetch buffering %c\n", c);
		}
	}
	buffer[bufp++] = c;
}

void ungets(char s[]) {
	for (int i = 0; s[i] != '\0'; ++i) {
		ungetch(s[i]);
	}
}
