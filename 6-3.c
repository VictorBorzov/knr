#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULTLN 64
#define MAXLEN 1024

struct tnode {
	int count;
	int pos; /* position of last number in line numbers array */
	int len; /* length of line numbers array */
	char *word; /* word */
	int *ln; /* line numbers array */
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addnode(struct tnode *, char *, int);
void printtree(struct tnode *, double);

char *getword(int);

int line_number = 1; /* global line number */
long long node_number = 0; /* global node number for avg */
long long total_words = 0; /* global number of words */

int main(void) {
	char *w;
	double avg;
	struct tnode *root = NULL;

	while ((w=getword(MAXLEN)) != NULL) {
		root = addnode(root, w, line_number);
		++total_words;
	}

	avg = (double) total_words / node_number;
	printf("AVG: %.3f\n", avg);
	printtree(root, 3*avg);
}

/* printtree: in-order print with threshold */
void printtree(struct tnode *p, double threshold) {
	int i;
	if (p != NULL) {
		printtree(p->right, threshold);
		if (p->count < threshold) {
			printf("%4d \"%s\": ", p->count, p->word);
			for (i = 0; i < p->pos; ++i) {
				printf("%d%s", p->ln[i], (i == p->pos-1) ? "\n" : ", ");
			}
		}
		printtree(p->left, threshold);
	}
}

/* addnode: adds word from ln line number into p node */
struct tnode *addnode(struct tnode *p, char *w, int ln) {
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = w;
		p->count = 1;
		p->ln = (int *) malloc(sizeof(int) * DEFAULTLN);
		p->len = DEFAULTLN;
		p->pos = 0;
		p->left = NULL;
		p->right = NULL;
		p->ln[p->pos++] = ln;
		++node_number;
	} else if ((cond=strcmp(p->word, w)) == 0) {
		p->count++;
		if (p->pos == p->len) {
			p->ln = (int *) realloc(p->ln, sizeof(int) * p->len * 2);
			p->len *= 2;
		}
		p->ln[p->pos++] = ln;
	} else if (cond < 0) {
		p->left = addnode(p->left, w, ln);
	} else {
		p->right = addnode(p->right, w, ln);
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

	while (isspace(c=getch())) {
		line_number += c == '\n';
	}

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
