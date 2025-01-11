#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { OK, ERROR };

static int undcl(int);
static int dcl(void);
static int dirdcl(void);

static int gettoken(int args, const char*); /* args flag allows chars between () */
static int tokentype;             /* type of last token */
static char token[MAXTOKEN];      /* last token string */
static char name[MAXTOKEN];       /* identifier name */
static char datatype[MAXTOKEN];   /* data type = char, int, etc */
static char out[MAXTOKEN*10];

void printd(void) {
	printf("DEBUG: token=\"%s\"\tname=\"%s\"\tdatataype=\"%s\"\n", token, name, datatype);
	printf("DEBUG: out=\"%s\"\n", out);
}

void printtoken(void) {
	printf("DEBUG: read token %s, type is '", token);
	if (tokentype == NAME) {
		puts("NAME'");
	} else if (tokentype == PARENS) {
		puts("PARENS'");
	} else if (tokentype == BRACKETS) {
		puts("BRACKETS'");
	} else if (tokentype == '\n' || tokentype == ' ' || tokentype == '\t' || tokentype == EOF) {
		printf("%s'\n",
			(tokentype == '\n') ? "\\n" :
			(tokentype == '\t') ? "\\t" :
			(tokentype == ' ') ? "' '" :
			"EOF");
	} else {
		printf("%c'\n", tokentype);
	}
}

int main(int argc, char *argv[]) {
	int type;

        if (strstr(argv[0], "undcl")) {
		while (gettoken(0, "main, undcl") != EOF) {
			strcpy(out, token);
			while ((type=gettoken(0, "main, undcl")) != '\n') {
				if (undcl(type) == ERROR) {
					printf("ERROR: invalid input\n");
				}

			}
			puts(out);
		}
	}
	else if (strstr(argv[0], "dcl")) {
		while (gettoken(0, "main, dcl") != EOF) {      /* 1st token on line */
			strcpy(datatype, token); /* is the datatype */
			/* printf("DEBUG: set datatype to %s\n", datatype); */
			out[0] = '\0';
			if (dcl() == ERROR || tokentype != '\n') {
				printf("ERROR: syntax error\n");
				char c;
				void ungetch(char);
				char getch(void);
				while ((c=getch()) != '\n' && c != EOF);
				if (c == EOF)
					exit(EXIT_FAILURE);
			}
			printf("%s: %s %s\n", name, out, datatype);
		}
	}

	exit(EXIT_SUCCESS);
}

/* undcl: parse current token and put it into out */
int undcl(int type) {
	char temp[MAXTOKEN];
	void ungetch(char);
	if (type == PARENS || type == BRACKETS) {
		strcat(out, token);
	} else if (type == '*') {
		if ((type=gettoken(0, "main, undcl")) != BRACKETS && type != PARENS)
			sprintf(temp, "*%s", out);
		else
			sprintf(temp, "(*%s)", out);
		strcpy(out, temp);
		if (type == EOF || type == '\n')
			ungetch(type);
		return undcl(type);

	} else if (type == NAME) {
		sprintf(temp, "%s %s", token, out);
		strcpy(out, temp);
	} else {
		return ERROR;
	}
}

/* gettoken: skips blanks, set parens, brackets with number or single char into token */
int gettoken(int args, const char *title) {
	int gettokenimpl(int), res;
	/* printf("DEBUG: gettoken called from %s\n", title); */
	res = gettokenimpl(args);
	printtoken();
	return res;
}

int gettokenimpl(int args) {
	char c, getch(void);
	void ungetch(char);
	char *p = token;

	while ((c=getch()) == ' ' || c == '\t');

	if (c == '(') {
		if ((c=getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else if (args) {
			*p++ = '(';
			for (*p++ = c; (*p++ = getch()) != ')';);
			*p = '\0';
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}

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
int dcl(void) {
	int ns;

	for (ns = 0; gettoken(0, "dcl: counting pointers") == '*'; ++ns); /* count *'s */
	/* printf("DEBUG: dcl: found %i pointers\n", ns); */
	if (dirdcl() == ERROR)
		return ERROR;
	while (ns-- > 0) {
		/* printf("DEBUG: dcl: found star, setting pointer\n"); */
		strcat(out, " pointer to");
	}
	return OK;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void) {
	int type;

	if (tokentype == '(') {
		/* printf("DEBUG: dirdcl: found '(', reading inner dcl\n"); */
		/* inside may be a dcl or function arguments, and the later should be preserved */
		/* function arguments may contain commas */
		if (dcl() == ERROR)
			return ERROR;
		if (tokentype != ')') {
			printf("ERROR: dirdcl: missing )\n");
			return ERROR;
		}
	} else if (tokentype == NAME) {
		/* printf("DEBUG: dirdcl: setting name to %s\n", token); */
		strcpy(name, token);
	} else {
		printf("ERROR: dirdcl: expected name or (dcl)\n");
		return ERROR;
	}

	while ((type=gettoken(1, "dirdcl, checking parens or brackets")) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			/* printf("DEBUG: dirdcl: found parens setting function\n"); */
			strcat(out, " function");
			strcat(out, token);
			strcat(out, " returning");
		} else {
			/* printf("DEBUG: found brackets setting array %s\n", token); */
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
	return OK;
}

#define EMPTY -10
static char buffer = EMPTY;

/* getch, ungetch */
char getch(void) {
	char c;
	if (buffer == EMPTY) {
		c = getchar();
		/* if (c == '\n' || c == '\t' || c == ' ' || c == EOF) */
			/* printf("DEBUG: reading char %s from input\n", */
				/* (c == '\n') ? "\\n" : */
				/* (c == '\t') ? "\\t" : */
				/* (c == ' ') ? "' '" : */
				/* "EOF"); */
		/* else */
			/* printf("DEBUG: reading char %c from input\n", c); */
		return c;
	} else {
		c = buffer;
		buffer = EMPTY;
		/* if (c == '\n' || c == '\t' || c == ' ' || c == EOF) */
			/* printf("DEBUG: reading char %s from input\n", */
				/* (c == '\n') ? "\\n" : */
				/* (c == '\t') ? "\\t" : */
				/* (c == ' ') ? "' '" : */
				/* "EOF"); */
		/* else */
			/* printf("DEBUG: reading char %c from input\n", c); */
		return c;
	}
}

void ungetch(char c) {
	/* if (c == '\n' || c == '\t' || c == ' ' || c == EOF) */
	/* 	/\* printf("DEBUG: returning char %s to input\n", *\/ */
	/* 		(c == '\n') ? "\\n" : */
	/* 		(c == '\t') ? "\\t" : */
	/* 		(c == ' ') ? "' '" : */
	/* 		"EOF"); */
	/* else */
		/* printf("DEBUG: returning char %c to input\n", c); */
	buffer = c;
}
