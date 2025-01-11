#define MAXVAL 100 /* maximum depth of the stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	} else {
		printf("ERROR: stack is full, can't push %g\n", f);
	}
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("ERROR: stack is empty\n");
	}
}
