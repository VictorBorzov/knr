#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1024

int main(void) {
	int i, getline2(char[], int);
	double sum, atof2(char[]);
	char s[MAXLEN];

	while ((i = getline2(s, MAXLEN)) > 0) {
		printf("\t%g\n", sum += atof2(s));
	}

	exit(EXIT_SUCCESS);
}

int getline2(char s[], int lim) {
	char c;
	int i;

	for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

int atoi2(char s[]) {
	double atof2(char s[]);
	return (int) atof(s);
}

/* supports exponential notation like 1.3e-10 (signed) */
double atof3(char s[]) {
	double atof2(char s[]), res;
	int i, sign, exp, power;
	res = atof2(s);

	for (i = 0; s[i] != '\0' && s[i] != 'e' && s[i] != 'E'; ++i);
	if (s[i] == '\0') {
		return res;
	}
	++i;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+') {
		++i;
	}

	for (exp = 0; isdigit(s[i]); ++i) {
		exp *= 10;
		exp += s[i] - '0';
	}
	for (power = 1; exp > 0; --exp) {
		power *= 10;
	}
	return (sign > 0) ? res * power : res / power;
}

double atof2(char s[]) {
	int i, sign, exp, power;
	double res;

	// skip leading spaces
	for (i = 0; isspace(s[i]); ++i);

	// handle sign
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+') {
		++i;
	}

	for (res = 0; isdigit(s[i]); ++i) {
		res *= 10;
		res += s[i] - '0';
	}

	// floating part
	if (s[i] == '.') {
		++i;
		for (power = 1; isdigit(s[i]); ++i, power *= 10) {
			res *= 10;
			res += (s[i] - '0');
		}
	} else {
		power = 1;
	}

	res = sign * res / power;
	if (s[i] != 'e' && s[i] != 'E') {
		return res;
	}

	// exponent part
	++i;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+') {
		++i;
	}

	for (exp = 0; isdigit(s[i]); ++i) {
		exp *= 10;
		exp += s[i] - '0';
	}
	for (power = 1; exp > 0; --exp) {
		power *= 10;
	}

	return (sign > 0) ? res * power : res / power;
}

