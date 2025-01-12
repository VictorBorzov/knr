#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

struct tnode {
	int count;
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addnode(struct tnode *, char *);
void printtree(struct tnode *);
char *getword(int);

int node_number = 0;
static int cmpnodes(const void *p1, const void *p2);
struct tnode **make_flat(struct tnode **arr, struct tnode *p, int);

int main(void) {
	char *w;
	int i;
	struct tnode *root = NULL;
	struct tnode **flat;

	while ((w=getword(MAXLEN)) != NULL) {
		root = addnode(root, w);
	}

	flat = (struct tnode **) malloc(node_number*sizeof(struct tnode *));
	make_flat(flat, root, 0);
	qsort(flat, node_number, sizeof(struct tnode **),  cmpnodes);

	for (i = 0; i < node_number; ++i)
		printf("%4d \"%s\"\n", flat[i]->count, flat[i]->word);
}

static int cmpnodes(const void *p1, const void *p2)
{
	struct tnode *n1, *n2;
	n1 = *(struct tnode **)p1;
	n2 = *(struct tnode **)p2;
	return (n1->count < n2->count) ? 1 : (n1->count > n2->count) ? -1 : 0;
}


struct tnode **make_flat(struct tnode **arr, struct tnode *p, int i) {
	if (p != NULL) {
		*arr++ = p;
		arr = make_flat(arr, p->left, i+1);
		make_flat(arr, p->right, i+1);
	}
}


/* printtree: in-order print */
void printtree(struct tnode *p) {
	int i;
	if (p != NULL) {
		printtree(p->right);
		printf("%4d \"%s\"\n", p->count, p->word);
		printtree(p->left);
	}
}

/* addnode: adds word into p node */
struct tnode *addnode(struct tnode *p, char *w) {
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = w;
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
		++node_number;
	} else if ((cond=strcmp(p->word, w)) == 0) {
		p->count++;
	} else if (cond > 0) {
		p->left = addnode(p->left, w);
	} else {
		p->right = addnode(p->right, w);
	}

	return p;
}


/* talloc: creates tnode struct */
struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* getword: reads next word from stdin and sets line number */
char *getword(int lim) {
	char c, buffer[lim], getch(void);
	int i;
	void ungetch(char);

	while (isspace(c=getch()));

	if (c != EOF && !isalnum(c)) {
		buffer[0] = c;
		buffer[1] = '\0';
		return strdup(buffer);
	}
	for (i = 0; i < lim-1 && c != EOF && isalnum(c); c=getch(),++i) {
		buffer[i] = c;
	}

	if (c == '\n') {
		ungetch(c);
	}

	buffer[i] = '\0';

	return (i == 0) ? NULL : strdup(buffer);
}

char buffer = '\0';

char getch(void) {
	char c;
	if (buffer) {
		c = buffer;
		buffer = '\0';
		return c;
	} else {
		return getchar();
	}
}

void ungetch(char c) {
	if (buffer) {
		printf("WARN: overriding buffer %c with %c\n", buffer, c);
	}
	buffer = c;
}
