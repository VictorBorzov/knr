#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define OPLEN 16
#define FMTLEN 1024
#define MAXLEN 1024

void push(double);
double pop(void);
void init_stack(void);
void free_stack(void);
void print_stack(void);

char *getoken(void);

int main(void) {
	int res;
	double n1, n2;
	char c, *token;

	init_stack();
	res = 0;
	while ((token=getoken()) != NULL) {
		if (sscanf(token, "%lf", &n1)) {
			push(n1);
		} else if (sscanf(token, "%c", &c)) {
			n2 = pop();
			n1 = pop();
			switch (c) {
			case '+':
				n1 += n2;
				break;
			case '-':
				n1 -= n2;
				break;
			case '*':
				n1 *= n2;
				break;
			case '/':
				n1 /= n2;
				break;
			default:
				printf("ERROR: unknown operation '%c'\n", c);
				n1 = 0;
				return 1;
			}
			printf("%g\n", n1);
			push(n1);
		} else {
			printf("ERROR: this error should never happen\n");
		}
		free(token);
	}
	free(token);

	free_stack();
	return 0;
}

#define TOKENLEN 1024
/* getoken: returns next non-whitespace seq of chars or NULL */
char *getoken(void) {
	char c, token[TOKENLEN];
	unsigned n;

        while (isspace(c=getchar())); /* skip whitespaces */
	if (c == EOF)
		return NULL;

	for (n = 0; n < TOKENLEN-1 && c != EOF && !isspace(c); ++n,c=getchar()) {
		token[n] = c;
	}
	token[n] = '\0';
	if (n == TOKENLEN-1)
		printf("WARN: token is too long!\n");

	return strdup(token);
}

double *stack;
int stacksize = 16;
int pos = 0; /* next free position in stack */

double pop(void) {
	if (pos > 0) {
		return stack[--pos];
	} else {
		printf("ERROR: stack is empty!\n");
		return NAN;
	}
}

void push(double d) {
	if (pos == stacksize) {
		stacksize *= 2;
		stack = (double *) reallocarray((void *)stack, pos, stacksize);
	}
	stack[pos++] = d;
}

void print_stack(void) {
	int i;
	printf("stack=[");
	for (i = 0; i < pos; ++i)
		printf("%s%lg", (i > 0) ? ", " : "", stack[i]);
	printf("]\n");
}

void init_stack(void) {
	stack = (double *) malloc(sizeof(double) * stacksize);
}
void free_stack(void) {
	free(stack);
}
