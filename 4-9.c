#include <stdio.h>

#define MAXLEN 1024
#define DEBUG 0
#define EMPTY -10

char buffer = EMPTY;

char getch(void);
void ungetch(char);
void print(void);

int main(void) {
	char c;
	char buf[MAXLEN];
	int i, n;

	printf("%d\n", -2 == EOF);

	printf("==========getch...==========\n");
	for (n = 0; (c = getch()) != EOF; ++n) {
		putchar(c);
		buf[n] = c;
	}
	buf[n++] = EOF;
	buf[n] = '\0';
	print();

	printf("=========ungetch...=========\n");
	for (i = n-1; i >= 0; --i) {
		ungetch(buf[i]);
		print();
	}

	printf("==========getch...==========\n");
	for (i = 0; (c = getch()) != EOF; ++n) {
		putchar(c);
		buf[n] = c;
	}
	print();
}


void print(void) {
	if (buffer == '\n') {
		printf("BUFFER=\\n\n");
	} else if (buffer == EOF) {
		printf("BUFFER=EOF\n");
	} else if (buffer == EMPTY) {
		printf("BUFFER IS EMPTY\n");
	} else {
		printf("BUFFER=%c\n", buffer);
	}
}

char getch(void) {
	char c;
	if (buffer != EMPTY) {
		c = buffer;
		if (DEBUG) {
			if (c == EOF || c == '\n') {
				printf("DEBUG: getch returning buffered char %s\n",
					(c == EOF) ? "EOF" : (c == '\n') ? "\\n" : "");
			} else {
				printf("DEBUG: getch returning buffered char %c\n", c);
			}
		}
		buffer = EMPTY;
		return c;
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
	}
}

void ungetch(char c) {
	if (DEBUG) {
		if (c == EOF || c == '\n') {
			printf("DEBUG: ungetch buffering %s\n",
				(c == EOF) ? "EOF" : (c == '\n') ? "\\n" : "");
		} else {
			printf("DEBUG: ungetch buffering %c\n", c);
		}
	}
	buffer = c;
}

