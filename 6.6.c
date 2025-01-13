#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *);
int getword(char *, int);
char *strdup(const char *s);

/* word frequency count */
int main(void) {
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
	treeprint(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

	if (p == NULL) { /* a new word arrived, make a new node */
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond=strcmp(w, p->word)) == 0) {
		p->count++; /* repeated word */
	} else if (cond < 0) { /* less than into left subtree */
		p->left = addtree(p->left, w);
	} else { /* greater than into right subtree */
		p->right = addtree(p->right, w);
	}

	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdup(const char *s) {
	char *p;

	p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL) {
		strcpy(p, s);
	}

	return p;
}

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

