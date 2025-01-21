#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define OPLEN 16
#define FMTLEN 1024
#define MAXLEN 1024

void push(double);
double pop(void);
void init_stack(void);
void free_stack(void);

int calc(double n1, double n2, double *res, char c);

int main(void) {
	double n1, n2, res;
	char op, line[MAXLEN];

	n = scanf("%5s%c%5s", s1, &c, s2);
	if (c == '\n')
		printf("n=%d, read %s and \\n, the rest is %s(%d)\n", n, s1, s2, strlen(s2));
	else
		printf("n=%d, read %s and %c, the rest is %s(%d)\n", n, s1, c, s2, strlen(s2));
	return 0;


	sprintf(fmt, "%%lf %%lf %%%ds", OPLEN);
	puts(fmt);

	init_stack();
	while (fgets(line, MAXLEN, stdin) != NULL) {
		if (sscanf(line, "%lf %lf %c", &n1, &n2, &op) == 3) {
			/* calc, print/push result to stack */
		} else if (sscanf(line, "%lf %c", &n2, &op) == 2) {
			if (isnan(n1 = pop())) {
				printf("ERROR: invalid stack operation\n");
				continue;
			}
			/* pop n1 from the stack, calc and print/push res */
		} else if (sscanf(line, "%c", &op) == 1) {
			/* pop n1, n2 from the stack and calc */
			if (isnan(n1 = pop())) {
				printf("ERROR: invalid stack operation\n");
				continue;
			}
			if (isnan(n2 = pop())) {
				printf("ERROR: invalid stack operation\n");
				continue;
			}
		} else {
			/* error line */
			printf("ERROR: wrong format\n");
			continue;
		}
		/* */
	}

	free_stack();
	return 0;
}

int calc(double n1, double n2, double *res, char c) {
	switch (c) {
	case '+':
		*res = n1 + n2;
		break;
	case '-':
		*res = n1 - n2;
		break;
	case '*':
		*res = n1 * n2;
		break;
	case '/':
		*res = n1 / n2;
		break;
	default:
		printf("ERROR: unknown operation '%c'\n", c);
		return 1;
	}
	return 0;
}

double *stack;
int stacksize = 1024;
int pos = 0; /* next free position in stack */

double pop(void) {
	if (pos > 0) {
		return stack[pos--];
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

