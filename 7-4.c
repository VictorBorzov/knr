#include <stdio.h>
#include <stdarg.h>

#define MAXLEN 1024

typedef union arg {
	int *i;
	unsigned *u;
	float *f;
	char *s;
} Arg;

int minscanf(char *fmt, ...);

int main(void) {
	int i, n;
	unsigned u;
	float f;
	char s[5];

	n = minscanf("%i %5s %u and %f", &i, s, &u, &f);
	printf("n=%d,i=%d,s=%s,u=%u,f=%f\n", n, i, s, u, f);
	return 0;
}

int minscanf(char *fmt, ...) {
	va_list ap;
	Arg arg;
	int n, res;
	char format[MAXLEN], *f;

	va_start(ap, fmt);
	for (res=n=0,f=format; *fmt; ++fmt) {
		if (*fmt != '%') {
			*f++ = *fmt;
			continue;
		}
		*f++ = *fmt++;
		while (*fmt >= '0' && *fmt <= '9') {
			*f++ = *fmt++;
		}
		*f++ = *fmt;
		*f = '\0';
		res = 0;
		switch(*(f-1)) {
		case 'd': case 'i': case 'b': case 'x': case 'X':
			arg.i = (int *) va_arg(ap, int *);
			res = scanf(format, arg.i);
			f = format;
			break;
		case 'u':
			arg.u = (unsigned *) va_arg(ap, unsigned *);
			res = scanf(format, arg.u);
			f = format;
			break;
		case 'f': case 'g': case 'G':
			arg.f = (float *) va_arg(ap, float *);
			res = scanf(format, arg.f);
			f = format;
			break;
		case 's':
			arg.s = (char *) va_arg(ap, char *);
			res = scanf(format, arg.s);
			f = format;
			break;
		default:
			break;
		}
		if (res == EOF)
			return n;
		else
			n += res;

	}
	va_end(ap);
	return n;
}
