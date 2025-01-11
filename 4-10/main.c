#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

/* polish notation calculator */
int main(void) {
	int i, n, type;
	double op2;
	char s[MAXOP];

	initstackflags();
	while ((n=getline2(s, MAXOP)) > 0) {
		/* printf("DEBUG: got line with length %i\n", n); */
		parse(s, 0, n);
	}
	exit(EXIT_SUCCESS);
}



void hop(char op) {
	char op2;
	switch(op) {
	case '+':
		push(pop() + pop());
		break;
	case '*':
		push(pop() * pop());
		break;
	case '-':
		op2 = pop();
		push(pop() - op2);
		break;
	case '/':
		op2 = pop();
		if (op2 != 0.0)
			push(pop() / op2);
		else
			printf("ERROR: zero divisor\n");
		break;
	case '%':
		op2 = pop();
		if (op2 != 0.0)
			push((int) pop() % (int) op2);
		else
			printf("ERROR: zero divisor\n");
		break;
	case '\n':
		printf("\t%.6g\n", pop());
		break;
	case '=':
		/* printf("DEBUG: parsed operator \"=\"\n"); */
		op2 = pop();
		/* printf("DEBUG: op2=%g\n", op2); */
		char var = popvarname();
		/* printf("DEBUG: var=%c\n", var); */
		setvar(var, op2);
		printstack();
		break;
	default:
		printf("ERROR: unknown operator %c\n", op);
			break;
	}
}

void hvar(char c) {
	/* printf("DEBUG: pushed %c to the stack\n", c); */
	pushvar(c);
	/* printstack(); */
}

void hnum(double v) {
	push(v);
	/* printf("DEBUG: pushed %f to the stack\n", v); */
	/* printstack(); */
}

void hcom(char s[]) {
	int op2;
	if (strcmp(s, "print")) {
		printstack();
	} else if (strcmp(s, "vars")) {
		printvars();
	} else if (strcmp(s, "top")) {
		printf("\t%g\n", gettop());
	} else if (strcmp(s, "duplicate")) {
		duplicatetop();
	} else if (strcmp(s, "swap")) {
		swaplastwo();
	} else if (strcmp(s, "clear")) {
		clear();
	} else if (strcmp(s, "sin")) {
		push(sin(pop()));
	} else if (strcmp(s, "cos")) {
		push(cos(pop()));
	} else if (strcmp(s, "tan")) {
		push(tan(pop()));
	} else if (strcmp(s, "exp")) {
		push(exp(pop()));
	} else if (strcmp(s, "log")) {
		push(log(pop()));
	} else if (strcmp(s, "log10")) {
		push(log10(pop()));
	} else if (strcmp(s, "pow")) {
		op2 = pop();
		push(pow(pop(), op2));
	} else if (strcmp(s, "sqrt")) {
		push(sqrt(pop()));
	} else if (strcmp(s, "fabs")) {
		push(fabs(pop()));
	} else if (strcmp(s, "+")) {
		push(pop() + pop());
	} else if (strcmp(s, "*")) {
		push(pop() * pop());
	} else if (strcmp(s, "-")) {
		op2 = pop();
		push(pop() - op2);
	} else if (strcmp(s, "/")) {
		op2 = pop();
		if (op2 != 0.0)
			push(pop() / op2);
		else
			printf("ERROR: zero divisor\n");
	} else if (strcmp(s, "%")) {
		op2 = pop();
		if (op2 != 0.0)
			push((int) pop() % (int) op2);
		else
			printf("ERROR: zero divisor\n");
	} else if (strcmp(s, "\\n")) {
		printf("\t%.6g\n", pop());
	} else if (strcmp(s, "=")) {
		/* printf("DEBUG: parsed operator \"=\"\n"); */
		op2 = pop();
		/* printf("DEBUG: op2=%g\n", op2); */
		char var = popvarname();
		/* printf("DEBUG: var=%c\n", var); */
		setvar(var, op2);
		/* printstack(); */

	} else {
		printf("ERROR: unknown command %s\n", s);
	}
}
