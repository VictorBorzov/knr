#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXOP 20 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */
#define VAR '2' /* signal that a variable was found */

int getop(char *);
void push(double);
double pop(void);
char popvarname(void);
void printstack(void);
double gettop(void);
void duplicatetop(void);
void swaplastwo(void);
void clear(void);

void initstackflags(void);
void pushvar(char);
void setvar(char name, double value);


int strcmp(char[], char[]);

/* polish notation calculator */
int main(void) {
	int type;
	double op2;
	char s[MAXOP];

	initstackflags();
	while ((type = getop(s)) != EOF) {
		if (type == NUMBER) {
			printf("DEBUG: parsed number %s\n", s);
		} else if (type == COMMAND) {
			printf("DEBUG: parsed command %s\n", s);
		} else if (type == VAR) {
			printf("DEBUG: parsed var %c\n", s[0]);
		} else {
			printf("DEBUG: parsed operator %c\n", type);
		}
		switch (type) {
		case NUMBER:
			push(atof(s));
			printf("DEBUG: pushed %s to the stack\n", s);
			printstack();
			break;
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
			printf("DEBUG: parsed operator \"=\"\n");
			op2 = pop();
			printf("DEBUG: op2=%g\n", op2);
			char var = popvarname();
			printf("DEBUG: var=%c\n", var);
			setvar(var, op2);
			printstack();
			break;
		case COMMAND:
			if (strcmp(s, "print")) {
				printstack();
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
			} else {
				printf("ERROR: unknown command %s\n", s);
			}
			break;
		case VAR:
			printf("DEBUG: pushed %c to the stack\n", s[0]);
			pushvar(s[0]);
			printstack();
			break;
		default:
			printf("ERROR: unknown operator %s\n", s);
			break;
		}
	}
	exit(EXIT_SUCCESS);
}

int strcmp(char s1[], char s2[]) {
	for (int i = 0; i < MAXOP; ++i) {
		if (s1[i] == '\0' && s2[i] == '\0') {
			return 1;
		} else if (s1[i] != s2[i]) {
			return 0;
		}
	}
	return 1;
}

/*************4.3-stack.c*****************/
#define MAXVAL 100 /* maximum depth of the stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
int flags[MAXVAL]; /* is stack value a variable name flags, has to be initialized! */

double vars[26] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0 };

void initstackflags(void) {
	for (int i = 0; i < MAXVAL; ++i) {
		flags[i] = 0;
	}
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
	printf("DEBUG: setting flag %i to 1\n", sp);
	push((double) (name - 'a'));
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL) {
		printf("DEBUG: setting val[%i] to %g\n", sp, f);
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


/*************4.3-getop.c*****************/

#include <ctype.h>

char getch(void);
void ungetch(char);

/* getop: get next character of numeric operand */
int getop(char *s) {
	while (isspace(*s = getch()));

	/* read sign */
	if (*s == '-' || *s == '+') {
		if (isdigit(*++s = getch())) {
			/* in case of number, return it back and read as number */
			ungetch(*s);
			return getop(s);
		}
		/* in case of nan, keep the sign and return char back */
		ungetch(*s--);
	}
	/* s points to first non-whitespace char */

	/* not a number */
	if (!isdigit(*s) && *s != '.') {
		if ((*++s = getch()) == EOF || isspace(*s) || isdigit(*s)) {
			ungetch(*s--);
			if (*s >= 'a' && *s <= 'z') { // variable
				*++s = '\0';
				return VAR;
			}
			return *s; // operator
		} else { // command, s points to the second non whitespace char
			while ((*++s = getch()) != EOF && !isspace(*s));
			*s = '\0';
			return COMMAND;
		}
	}

	/* s points to the first non whitespace */
	if (isdigit(*s)) /* collect integer part */
		while (isdigit(*++s = getch()));

	if (*s == '.') /* collect fraction part */
		while (isdigit(*++s = getch()));

	if (*s != EOF)
		ungetch(*s);

	*s = '\0';
	return NUMBER;
}

#define BUFSIZE 1024 /* max buffer length */

int pos = 0; /* next free position in buffer */
char buffer[BUFSIZE];

char getch(void) {
	return (pos > 0) ? buffer[--pos] : getchar();
}

void ungetch(char c) {
	if (pos >= BUFSIZE) {
		printf("ERROR: ungetch - too many characters\n");
	}
	buffer[pos++] = c;
}

