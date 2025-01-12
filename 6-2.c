#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *build_tree(struct tnode *root);

struct tnode *talloc(void);
void treeprint(struct tnode *);

char *strdup(const char *s);
char *read_token(int lim);

char *gettoken(int lim);
void ungettoken(char *token);

/* istype: check if token is a type */
int istype(const char *word) {
	return strcmp(word, "char") == 0 ||
		strcmp(word, "float") == 0 ||
		strcmp(word, "int") == 0 ||
		strcmp(word, "double") == 0 ||
		strcmp(word, "long") == 0 ||
		strcmp(word, "short") == 0;
}

int tokenlen = 6;

/* word frequency count */
int main(int argc, char *argv[]) {
	struct tnode *root = NULL;

	if (argc > 1) {
		tokenlen = atoi(argv[1]);
		tokenlen = tokenlen > 0 ? tokenlen : 1;
	}

	root = build_tree(root);
	treeprint(root);

	return 0;
}

struct tnode *build_tree(struct tnode *root) {
	static char found_type = 0;
	char token_is_type, *token, *next;

	token = gettoken(MAXWORD);
	if (token) {
		token_is_type = istype(token);
		/*
		  variable is a token:
		  1. coming right after type or
		  2. coming after ',' after type or
		  3. coming any token after 'struct'
		 */
		if (found_type) {
			next = gettoken(MAXWORD);
			if (next == NULL) {
				return root;
			} else if (next[0] == '[' || next[0] == '(') {
				found_type = 0;
				return build_tree(root);
			} else if (token[0] == '*' || token[0] == ',') {
				ungettoken(next);
				return build_tree(root);
			} else if (strcmp(token, "struct") == 0) {
				return build_tree(root);
			} else if (token_is_type) {
				ungettoken(next);
				return build_tree(root);
			} else if (isalpha(token[0])) {
				root = addtree(root, token);
				found_type = next[0] == ',';
				return build_tree(root);
			} else {
				found_type = 0;
				return build_tree(root);
			}
		} else if (strcmp(token, "struct") == 0) {
			gettoken(MAXWORD);
			found_type = 1;
			return build_tree(root);
		}else {
			found_type = token_is_type;
			return build_tree(root);
		}

	}
	return root;
}

char *buffertoken = NULL;

char *gettoken(int lim) {
	char *tmp;
	if (buffertoken) {
		tmp = buffertoken;
		buffertoken = NULL;
		return tmp;
	}
	return read_token(lim);
}

void ungettoken(char *token) {
	if (buffertoken) {
		printf("WARN: overriding token %s with %s\n", buffertoken, token);
	}
	buffertoken = token;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	if (strlen(w) > tokenlen)
		w[tokenlen] = '\0';

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

char *read_token(int lim) {
	char token[lim];
	char c, cn, getch(void), *w = token, newline = 1;
	void ungetch(char c);

	while ((c=getch()) == ' ' || c == '\t' || c == '\n') {
		newline = c == '\n';
	}

	if (c == EOF) {
		return NULL;
	}
	if (newline && c == '#') { /* preprocessor directive */
		*w++ = c;
		while ((c=getch()) != '\n' && c != EOF)
			*w++ = c;
		*w = '\0';
		return strdup(token);
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
					return strdup(token);
				}
			}
		}
		if (c == '\'')
			*w++ = c;
		*w = '\0';
		return strdup(token);
	}

	if (c == '"')  {/* strings constants */
		for (cn=getchar(); (c == '\\' || cn != '"') && cn != EOF; c=cn,cn=getch()) {
			*w++ = cn;
		}
		if (cn == '"') {
			*w++ = cn;
		}

		*w = '\0';
		return strdup(token);
	}

	if (c == '/') {
		if ((cn=getch()) == '/') { // single line comment
			for (c=cn; cn != EOF && cn != '\n'; c=cn, cn=getch()) {
				*w++ = cn;
			}
			*w = '\0';
			return strdup(token);
		} else if (cn == '*') { /* multiline comment */
			for (c=cn; cn != EOF && !(c == '*' && cn == '/'); c=cn, cn=getch()) {
				*w++ = cn;
			}
			if (cn == '/') {
				*w++ = cn;
			}
			*w = '\0';
			return strdup(token);
		} else /* not a comment */ {
			ungetch(cn);
		}
	}

	if (!isalpha(c)) { /* not a name */
		if ((cn=getch()) != '_') {
			ungetch(cn);
			*w = '\0';
			return strdup(token);
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

	return strdup(token);
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

