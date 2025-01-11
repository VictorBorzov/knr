#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 20 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void printstack(void);
double gettop(void);
void duplicatetop(void);
void swaplastwo(void);
void clear(void);

int strcmp(char[], char[]);

/* polish notation calculator */
int main(void) {
	/*
	  while (next operator or operand is not end-of-file indicator)
	      if (number)
	          push it
	      else if (operator)
	          pop operands
		  do operation
		  push result
	      else if (newline)
	          pop and print top of stack
	      else
	          error
	 */
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		/* if (type == COMMAND) { */
		/* 	printf("DEBUG: command \"%s\" detected!\n", s); */
		/* } else if (type == NUMBER) { */
		/* 	printf("DEBUG: number \"%s\" detected\n", s); */
		/* } else { */
		/* 	printf("DEBUG: operation \"%c\" detected\n", type); */
		/* } */
		switch (type) {
		case NUMBER:
			push(atof(s));
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
			} else {
				printf("ERROR: unknown command %s\n", s);
			}
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

void printstack(void) {
	for (int i = 0; i < sp; ++i) {
		printf("%s%g%s", (i == 0) ? "[" : ", ", val[i], (i == sp-1) ? "]\n" : "");
	}
}

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
		return 0.0;
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
	} else {
		printf("ERROR: stack does not have enough\n");
	}
}

void clear(void) {
	sp = 0;
}

/*************4.3-getop.c*****************/

#include <ctype.h>

char getch(void);
void ungetch(char);

/* getop: get next character of numeric operand */
int getop(char s[]) {
	int i, c, cn;

	while ((s[0] = c = getch()) == ' ' || c == '\t' || c == '\n');
	s[1] = '\0';

	/* read sign */
	i = 0;
	if (c == '-' || c == '+') {
		if (isdigit(cn = getch())) {
			s[i] = c;
			c = cn;
		}
		ungetch(cn);
	}
	/* not a number */
	if (!isdigit(c) && c != '.') {
		if ((cn=getch()) == EOF || cn == '\n' || cn == ' ' || cn == '\t' || isdigit(cn)) {
			ungetch(cn);
			return c;
		} else { // command
			s[i++] = c;
			s[i++] = cn;
			while ((c = getch()) != EOF && c != '\n' && c != ' ' && c != '\t' && !isdigit(c)) {
				s[i++] = c;
			}
			s[i] = '\0';
			return COMMAND;
		}
	}

	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()));

	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
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

