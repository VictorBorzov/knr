#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define STACKSIZE 1024
static double pop(void);
static void push(double);
static int empty(void);

enum op { UNKNOWN, VALUE, OPERATION };
static enum op getop(const char *);

extern char **environ;

/* expr: evaluates a reverse Polish notation expression */
int main(int argc, char *argv[]) {
	double val1, val2;

	while (*environ)
		printf("%s\n", *environ++);

	while (*++argv) {
		switch (getop(*argv)) {
		case VALUE:
			push(atof(*argv));
			break;
		case OPERATION:
			errno = 0;
			val1 = pop();
			val2 = pop();
			if (errno)
				exit(EXIT_FAILURE);
			switch (**argv) {
			case '+':
				push(val1+val2);
				break;
			case '*':
				push(val1*val2);
				break;
			case '/':
				push(val2/val1);
				break;
			case '-':
				push(val2-val1);
				break;
			}
			break;
		default:
			printf("ERROR: cannot read %s\n", *argv);
			exit(EXIT_FAILURE);
			break;
		}

	}
	if (!empty())
		printf("%f\n", pop());
	exit(EXIT_SUCCESS);
}

enum op getop(const char *s) {
	if (*s < '0' || *s > '9') {/* first char is nan */
		return *(s+1) ? UNKNOWN : OPERATION; /* if one char this is operation */
	}

	/* if all chars are numbers this is a number */
	while (*s >= '0' && *s <= '9' || *s == '.') {
		++s;
	}
	return *s ? UNKNOWN : VALUE;
}


double stack[STACKSIZE] = {};
int stackp = 0;

double pop(void) {
	if (stackp <= 0) {
		errno = 1;
		printf("ERROR: stack is empty!\n");
		return NAN;
	}
	return stack[--stackp];
}

void push(double value) {
	if (stackp >= STACKSIZE) {
		errno = 1;
		printf("ERROR: stack is full!\n");
		return;
	}
	stack[stackp++] = value;
	return;
}

int empty(void) {
	return (stackp == 0);
}
