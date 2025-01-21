#include <stdio.h>

typedef struct tnode Treenode;

struct tnode {
	enum { INT, STRING, FLOAT } type;
	union {
		int i;
		char *s;
		float f;
	} value;

	Treenode *left;
	Treenode *right;
};

typedef struct flags {
	unsigned int a : 4;
	unsigned int b : 8;
} Flags;

int main(void) {
	Treenode node = { 10, 1, NULL, NULL }; /* value may be initialized only as first member int */

	Flags flags;
	printf("%i\n", sizeof(flags));
}
