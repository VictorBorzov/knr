#include <stdint.h>

#define SPACECHAR ' '

void entab(int *tabs);
void detab(int *tabs);

/* entab: entabs line */
void entab(int *tabs) {
	char c;
	int pos, *tabstart = tabs;

	for (; (c=getchar()) != EOF; pos = 0) {
		for (pos = 1; c == SPACECHAR; c = getchar(), ++pos);
		/* found pos spaces */
		/* set all tabs that less than pos */
		for (tabs = tabstart; *tabs <= pos; ++tabs) {
			putchar('\t');
		}

		while (c != '\n' && c != EOF) {
			putchar(c);
			c = getchar();
		}
		if (c == '\n')
			putchar(c);
	}
}

void detab(int *tabs) {
	char c;
	int i, pos, *tabstart;

	for (tabstart = tabs, pos = 0; (c=getchar()) != EOF; ++pos) {
		switch (c) {
		case '\n':
			pos = -1; // will make it 1 at the end of the loop
			tabs = tabstart;
			putchar('\n');
			break;
		case '\t':
			while (pos < *tabs) {
				putchar(SPACECHAR);
				pos++;
			}
			++tabs;
			break;
		default:
			putchar(c);
			break;
		}
	}
}
