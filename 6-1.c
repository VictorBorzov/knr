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
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
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
		printf("%i: '%s'\n", ++i, word);
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
/* handles underscores as one word for example my_test_name */
/* handles string constants as one word for example "my_test_name" */
/* handles comments // and /* */
/* as well as preprocessor control lines starting with # */
int getword(char *word, int lim) {
	char c, cn, getch(void), *w = word, newline = 1;
	void ungetch(char c);

	while ((c=getch()) == ' ' || c == '\t' || c == '\n') {
		newline = c == '\n';
	}

	if (newline && c == '#') { /* preprocessor directive */
		*w++ = c;
		while ((c=getch()) != '\n' && c != EOF)
			*w++ = c;
		*w = '\0';
		return word[0];
	}

	if (c != EOF)
		*w++ = c;

	if (c == '\'') { /* char constant */
		while ((c=getch()) != '\'' && c != EOF) {
			*w++ = c;
			if (c == '\\') {
				*w++ = (c=getch());
				if (c == EOF) {
					*w = '\0';
					return word[0];
				}
			}
		}
		if (c == '\'')
			*w++ = c;
		*w = '\0';
		return word[0];
	}

	if (c == '"')  {/* strings constants */
		for (cn=getchar(); (c == '\\' || cn != '"') && cn != EOF; c=cn,cn=getch()) {
			*w++ = cn;
		}
		if (cn == '"') {
			*w++ = cn;
		}

		*w = '\0';
		return word[0];
	}

	if (c == '/') {
		if ((cn=getch()) == '/') { // single line comment
			printf("DEBUG: single line comment\n");
			for (c=cn; cn != EOF && cn != '\n'; c=cn, cn=getch()) {
				*w++ = cn;
			}
			*w = '\0';
			return word[0];
		} else if (cn == '*') { /* multiline comment */
			for (c=cn; cn != EOF && !(c == '*' && cn == '/'); c=cn, cn=getch()) {
				*w++ = cn;
			}
			if (cn == '/') {
				*w++ = cn;
			}
			*w = '\0';
			return word[0];
		} else /* not a comment */
			ungetch(cn);
	}

	if (!isalpha(c)) { /* not a name */
		if ((cn=getch()) != '_') {
			ungetch(cn);
			*w = '\0';
			return c;
		}
		ungetch(cn);
	}


	for (; --lim > 0; ++w) {
		if (!isalnum(*w=getch()) && *w != '_') {
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
