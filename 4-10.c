#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXOP 20 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */
#define VAR '2' /* signal that a variable was found */


void parse(const char[], int, int);
int getline2(char buffer[], int lim);
void push(double);
double pop(void);
char popvarname(void);
void printstack(void);
void printvars(void);
double gettop(void);
void duplicatetop(void);
void swaplastwo(void);
void clear(void);

void initstackflags(void);
void pushvar(char);
void setvar(char name, double value);

void hvar(char); /* handle variable */
void hnum(double); /* handle number */
void hcom(char[]); /* handle command */
void hunknown(void); /* handle unknown */

int strcmp(char[], char[]);

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

/* compare s1 with s2 */
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


/*************4.3-getop.c*****************/

#include <ctype.h>

int getline2(char[], int);

/* parse s[b..end-1] */
void parse(const char s[], int b, int end) {
	/* printf("DEBUG: s=%s,b=%i,end=%i\n", s, b, end); */
	/* printf("DEBUG: parsing \""); */
	/* for (int k = b; k < end; ++k) { */
	/* 	if (s[k] == '\n') { */
	/* 		printf("\\n"); */
	/* 	} else if (s[k] == EOF) { */
	/* 		printf("EOF"); */
	/* 	} else { */
	/* 		putchar(s[k]); */
	/* 	} */
	/* } */
	/* printf("\"\n"); */
	/* s = "10 -20 +", b = 0, end = 8 */
	int i; /* current position */
	char word[MAXOP]; /* for a number or command */
	word[0] = '+'; /* because in the beginning I parse number */
	int j = 1; /* current position of word */

	/* skip leading spaces */
	for (i = b; i < end && isspace(s[i]); ++i);

	/* override sign when next char is digit */
	if (i < end-1 && (s[i] == '-' || s[i] == '+') && isdigit(s[i+1])) {
		word[0] = s[i++];
	}

	/* collect integer part if exists */
	if (isdigit(s[i]))
		while (i < end && isdigit(word[j++] = s[i++]));
	/* collect fraction part if exists */
	if (s[i] == '.') /* collect fraction part */
		while (i < end && isdigit(word[j++] = s[i++]));
	word[j] = '\0';
	/* number found */
	if (j > 1) {
		/* printf("DEBUG: got number %s\n", word); */
		hnum(atof(word));
		parse(s, i, end);
		return;
	}

	/* parse command/operator or variable if a char [a-z] */
	if (islower(s[i]) && (i == end-1 || isspace(s[i+1]) || isdigit(s[i+1]))) {
		/* printf("DEBUG: got var %c\n", s[i]); */
		hvar(s[i]);
		parse(s, i+1, end);
		return;
	}

	/* parse word from i to j till space as a command/operator */
	for (j=0; i < end && !isspace(s[i]); ++i, ++j) {
		word[j] = s[i];
	}
	word[j] = '\0';
	if (j > 0) {
		/* printf("DEBUG: got command %s\n", word); */
		hcom(word);
		parse(s, i, end);
	}
}

#define BUFSIZE 1024 /* max buffer length */

int getline2(char buffer[], int lim) {
	int i;
	char c;
	for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
		buffer[i] = c;
	}
	if (c == '\n') {
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return i;
}
