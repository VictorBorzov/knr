#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;             /* type of last token */
char token[MAXTOKEN];      /* last token string */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc */
char out[MAXTOKEN*10];

int main(int argc, char *argv[]) {
	/* t is a function returning a pointer to an array[3] */
	/* t () * [3] */
	/* int (*t())[3] */
	/* int (*(*x())[])() */
	/* x is a function returning a pointer to an array of pointer to function returning int  */

	/* int *x[] */
	/* x is an array of pointer to int */

	/* int x()[] */
	/* x is a function returning an array of int */

	/* int x[]() */
	/* x is an array of function returning int */

	/* int (*x)[]() */
	/* x is a pointer to an array of function returning int */

	/* void (*bsd_signal(int, void (*)(int)))(int) */
	/*  bsd_signal is function(int, void(*)(int)) returning a pointer to function(int) returning void   */


	int type;
	char temp[MAXTOKEN];

        if (strstr(argv[0], "undcl")) {
		while (gettoken() != EOF) {
			strcpy(out, token);
			while ((type=gettoken()) != '\n') {
				if (type == PARENS || type == BRACKETS) {
					strcat(out, token);
				} else if (type == '*') {
					sprintf(temp, "(*%s)", out);
					strcpy(out, temp);
				} else if (type == NAME) {
					sprintf(temp, "%s %s", token, out);
					strcpy(out, temp);
				} else {
					printf("ERROR: invalid input at %s\n", token);
				}
			}
			puts(out);
		}
	}
	else if (strstr(argv[0], "dcl")) {
		while (gettoken() != EOF) {      /* 1st token on line */
			strcpy(datatype, token); /* is the datatype */
			out[0] = '\0';
			dcl();                   /* parse rest of line */
			if (tokentype != '\n') {
				printf("ERROR: syntax error\n");
			}
			printf("%s: %s %s\n", name, out, datatype);
		}
	}

	exit(EXIT_SUCCESS);
}

/* gettoken: skips blanks, set parens, brackets with number or single char into token */
int gettoken(void) {
	char c, getch(void);
	void ungetch(char);
	char *p = token;

	while ((c=getch()) == ' ' || c == '\t');

	if (c == '(') {
		if ((c=getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']';);
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c=getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}

/* dcl: parse a declarator */
void dcl(void) {
	int ns;

	for (ns = 0; gettoken() == '*'; ++ns); /* count *'s */
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("ERROR: missing )\n");
		}
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		printf("ERROR: expected name or (dcl)\n");
	}

	while ((type=gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

/* getch, ungetch */
#define BUFSIZE 1024 /* max buffer length */

int pos = 0; /* next free position in buffer */
int buffer[BUFSIZE];

char getch(void) {
	return (pos > 0) ? buffer[--pos] : getchar();
}

void ungetch(char c) {
	if (pos >= BUFSIZE) {
		printf("ERROR: ungetch - too many characters\n");
	}
	buffer[pos++] = c;
}
