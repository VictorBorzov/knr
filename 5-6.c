#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define BUFFERLEN 1024

void dprint(char *s);

int getline2(char *s, int lim);
int atoi2(char *s);
void itoa2(int n, char *s, int width); /* convert n to characters in s */
void itoa3(int n, char *s); /* recursive version */
void reverse(char *s);
int strindex(char *s, char *ss); /* returns the index of ss in s, -1 if none */

int main(void) {
	char buffer[BUFFERLEN];
	char buffer2[BUFFERLEN];
	int i;
	while ((i = getline2(buffer, BUFFERLEN)) > 0) {
		buffer[i-1] = '\0'; /* remove \n */
		printf("beg: %s\n", buffer);
		reverse(buffer);
		printf("rev: %s\n", buffer);
		continue;
		if ((i = getline2(buffer2, BUFFERLEN)) > 0) {
			buffer2[i-1] = '\0'; /* remove \n */
			printf("1: %s", buffer);
			printf("2: %s\n", buffer2);
			printf("2 in 1 starts at %i\n", strindex(buffer, buffer2));
		}
	}
	exit(EXIT_SUCCESS);
}

int getline2(char *s, int lim) {
	int i;
	for (i = 0; lim-1 > 0 && (*s = getchar()) != EOF && *s != '\n'; ++i, ++s);
	if (*s == '\n') {
		++i, ++s;
	}
	*s = '\0';
	return i;
}

void dprint(char *s) {
	putchar('{');
	while (*s != '\0') {
		switch (*s) {
		case '\n':
			printf("\\n");
			break;
		case '\t':
			printf("\\t");
			break;
		case EOF:
			printf("EOF");
			break;
		default:
			printf("%c", *s);
			break;
		}
		printf(", ");
		++s;
	}
	printf("\\0}\n");
}

int atoi2(char *s) {
	int result, sign;

	/* skip whitespaces */
	while (isspace(*s)) {
		++s;
	}

	/* read sign */
	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+') {
		++s;
	}

	for (result = 0; isdigit(*s); ++s) {
		result *= 10;
		result += *s - '0';
	}

	return sign * result;
}

void itoa2(int n, char *s, int width) {
	int sign;
	char *tmp = s;
	unsigned abs = (sign = n) < 0 ? -n : n;

	do { /* write digits in reverse order */
		*s++ = abs % 10 + '0'; /* get the next digit */
		--width;
	} while ((abs /= 10) > 0); /* remove it from number */

	if (sign < 0) {
		*s++ = '-';
		--width;
	}
	while (width-- > 0) {
		*s++ = ' ';
	}
	*s = '\0';
	reverse(tmp);
}

void reverse(char *s) {
	char *pend = s, tmp;

	while (*pend)
		++pend;
	--pend; /* pend points to the last character now */

	while (pend > s) {
		tmp = *pend;
		*pend-- = *s;
		*s++ = tmp;
	}
}

int itoarec(unsigned n, char *s) {
	unsigned tail = n / 10;
	int res = 0;
	if (tail > 0)
		res = itoarec(tail, s);
	*(s+res) = n % 10 + '0';
	return res + 1;
}

void itoa3(int n, char *s) {
	int offset;
	if (n < 0)
		*s++ = '-';
	offset = itoarec((n < 0) ? -n : n, s);
	*(s+offset) = '\0';
}

int strindex(char *s, char *ss) {
	int i;
	char *st, *sst;
	for (i = 0; *s; ++i, ++s) {
		/* traverse equal part of ss and s */
		for (st=s,sst=ss; *sst && *sst == *st; ++sst, ++st);
		if (!*sst) { /* if ss traversed to the end */
			return i;
		}
	}
	return -1;
}
