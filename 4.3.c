#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 20 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

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
			push(pop() / op2);
			break;
		case '\n':
			printf("\t%.6g\n", pop());
			break;
		default:
			printf("ERROR: unknown command %s\n", s);
			break;
		}
	}
	exit(EXIT_SUCCESS);
}

/*************4.3-stack.c*****************/
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
		return 0.0;
	}
}

/*************4.3-getop.c*****************/

#include <ctype.h>

char getch(void);
void ungetch(char);

/* getop: get next character of numeric operand */
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */

	i = 0;
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

