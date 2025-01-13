#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void undef(char *);

int main(void) {
	install("test key", "test value");
	install("test key", "test value 2");
	install("kkk", "vv");
	install("name", "value");
	install("name2", "value2");
	install("john", "mike");
	install("heh", "hah");

	printable(hashtab, HASHSIZE);
	undef("heh");
	printf("==================================================\n");
	printable(hashtab, HASHSIZE);
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
