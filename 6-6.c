#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 1000
#define TESTEMPTY

/*

  [*] ---> [*] ---> [0]
                    [*] ---> name
		    [*] ---> defn
           [*]
	   [*]
  [0]
  [0]
  [*] ---> [0]
           [*] ---> name
	   [*] ---> defn
  [0]

 */
struct nlist { /* table entry */
	struct nlist *next; /* next entry in chain */
	char *name; /* defined name */
	char *defn; /* replacement text */
};

#define HASHSIZE 5

static struct nlist *hashtab[HASHSIZE] = {}; /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void printable(struct nlist *[], int);

char *read_token(int lim);

char startwith(const char *, const char *);

int ln = 1; /* global line number */
int main(void) {
	char *token, *name, *defn;
	struct nlist *entry;

	while ((token=read_token(MAXWORD)) != NULL) {
		if ((entry=lookup(token)) != NULL) { /* substitute */
			printf("%s", entry->defn);
		} else if (startwith(token, "#define ")) {
			printf("%s", token);
			strtok(token, " "); /* skip define */
			name = strtok(NULL, " ");
			defn = strtok(NULL, " ");
			if (name && defn) {
				install(name, defn);
			}
		} else {
			printf("%s", token);
		}
	}
}

char startwith(const char *haystack, const char *needle) {
	while (*haystack && *needle && *haystack == *needle) {
		++haystack;
		++needle;
	}
	return (*needle == '\0');
}


/* undef: remove name and definition from hashtable */
void undef(char *name) {
	unsigned hashcode = hash(name);
	int cond;
	struct nlist *prev, *target;

	for (prev=NULL, target=hashtab[hashcode];
	     target != NULL && (cond=strcmp(target->name, name)) != 0;
	     prev=target, target=target->next);

	if (cond == 0) { /* found target */
		if (prev != NULL) {
			prev->next = target->next;
		} else {
			hashtab[hashcode] = target->next;
		}
		free((void *) target->defn);
		free((void *) target->name);
		free((void *) target);
	}
}

void printable(struct nlist *table[], int n) {
	int i, j, k;
	struct nlist *p;
	for (i = 0; i < n; ++i) {
		for (p=table[i], j=0; p != NULL; ++j, p=p->next) {
			for (k = 0; k < j; ++k)
				printf("\t------>\t");
			printf("%s -> %s", p->name, p->defn);
			if (p->next == NULL)
				putchar('\n');
		}
	}
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; ++s) {
		hashval += *s + 31 * hashval;
	}

	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np; /* found */
		}
	}

	return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np=lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else { /* already here */
		free((void *) np->defn); /* free previous defn */
	}

	if ((np->defn=strdup(defn)) == NULL) {
		return NULL;
	}
	return np;
}

/* read_token: parses c code and returns a token - word, symbol, constant string or comment */
char *read_token(int lim) {
	char token[lim];
	char c, cn, getch(void), *w = token, newline = 1;
	void ungetch(char c);

	while ((c=getch()) == ' ' || c == '\t' || c == '\n') {
		putchar(c);
		newline = c == '\n';
		ln += newline;
	}

	if (c == EOF) {
		return NULL;
	}
	if (newline && c == '#') { /* preprocessor directive */
		*w++ = c;
		while ((c=getch()) != '\n' && c != EOF) {
			*w++ = c;
		}
		*w = '\0';
		if (c == '\n')
			ungetch(c);
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
		for (cn=getchar(); (c == '\\' || cn != '"') && cn != EOF && cn != '\n'; c=cn,cn=getch()) {
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
			if (cn == '\n') {
				ungetch(cn);
			}
			*w = '\0';
			return strdup(token);
		} else if (cn == '*') { /* multiline comment */
			for (c=cn; cn != EOF && !(c == '*' && cn == '/'); c=cn, cn=getch()) {
				*w++ = cn;
				ln += cn == '\n';
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
