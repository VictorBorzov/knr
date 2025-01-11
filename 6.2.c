#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0, /* inner braces like { "auto", 0 }, are optional */
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0,
};

#define NKEYS (sizeof keytab / sizeof keytab[0]) /* or (sizeof keytab / sizeof(struct key)) */

int getword(char *, int);
int binsearch(char *, struct key *, int);
char getch(void);
void ungetch(char);

int main(void) {
	int n;
	char word[MAXWORD];

	int i = 0;
	while (getword(word, MAXWORD) != EOF) {
		printf("%i: \"%s\"\n", ++i, word);
		if (isalpha(word[0])) {
			if ((n=binsearch(word, keytab, NKEYS)) >= 0) {
				keytab[n].count++;
			}
		}
	}
	for (n = 0; n < NKEYS; ++n)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]..tab[n-1] */
int binsearch(char *word, struct key *tab, int n) {
	int cond;
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0) {
			high = mid - 1;
		} else if (cond > 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}

	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	char c, getch(void), *w = word;
	void ungetch(char c);

	while (isspace(c=getch()));

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; ++w) {
		if (!isalnum(*w=getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';

	return word[0];
}

char buffer;
char bset = 0; /* buffer set flag */

char getch(void) {
	if (bset) {
		bset = 0;
		return buffer;
	} else {
		return getchar();
	}
}

void ungetch(char c) {
	if (bset) {
		printf("WARN: ungetch: overriding buffer!\n");
	}
	buffer = c;
	bset = 1;
}
