#include <stdio.h>
#include <math.h>
#include "calc.h"

#define MAXVAL 100 /* maximum depth of the stack */

static int sp = 0; /* next free stack position */
static double val[MAXVAL]; /* value stack */
static int flags[MAXVAL]; /* is stack value a variable name flags, has to be initialized! */

static double vars[26] = {
	NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
	NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
	NAN, NAN, NAN, NAN, NAN, NAN };

void initstackflags(void) {
	for (int i = 0; i < MAXVAL; ++i) {
		flags[i] = 0;
	}
}

void printvars(void) {
	for (int i = 0; i < sp; ++i) {
		if (flags[i]) {
			int c = (int) val[i];
			if (vars[c] != NAN)
				printf("%c=%f;", 'a' + c, vars[c]);
		}
	}
	putchar('\n');
}

void printstack(void) {
	putchar('[');
	for (int i = 0; i < sp; ++i) {
		if (flags[i]) { // print variable
			int c = (int) val[i];
			printf("%c=%f", 'a' + c, vars[c]);
		} else { // print value
			printf("%g", val[i]);
		}
		if (i != sp-1) {
			printf(", ");
		}
	}
	printf("]\n");
}

void pushvar(char name) {
	flags[sp] = 1;
	/* printf("DEBUG: setting flag %i to 1\n", sp); */
	push((double) (name - 'a'));
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL) {
		/* printf("DEBUG: setting val[%i] to %g\n", sp, f); */
		val[sp++] = f;
	} else {
		printf("ERROR: stack is full, can't push %g\n", f);
	}
}

char popvarname(void) {
	if (sp <= 0) {
		printf("ERROR: stack is empty\n");
		return 0;
	}
	if (!flags[sp-1]) {
		printf("ERROR: not a variable!\n");
		return 0;
	}
	flags[sp-1] = 0;
	return 'a' + (int) val[--sp];
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp <= 0) {
		printf("ERROR: stack is empty\n");
		return 0.0;
	}
	if (flags[--sp]) {
		flags[sp] = 0;
		return vars[(int)val[sp]];
	} else {
		return val[sp];
	}
}

double gettop(void) {
	if (sp > 0) {
		return val[sp-1];
	} else {
		printf("ERROR: stack is empty\n");
		return 0.0;
	}
}

void duplicatetop(void) {
	if (sp > 0) {
		push(val[sp-1]);
		flags[sp-1] = flags[sp-2];
	} else {
		printf("ERROR: stack is empty\n");
	}
}

void swaplastwo(void) {
	double tmp;
	if (sp > 1) {
		tmp = val[sp-2];
		val[sp-2] = val[sp-1];
		val[sp-1] = tmp;

		tmp = flags[sp-2];
		flags[sp-2] = flags[sp-1];
		flags[sp-1] = tmp;
	} else {
		printf("ERROR: stack does not have enough\n");
	}
}

void clear(void) {
	sp = 0;
	initstackflags();
}

void setvar(char name, double value) {
	if (name < 'a' || name > 'z') {
		printf("ERROR: name %c not supported!\n", name);
	}
	vars[name - 'a'] = value;
}
