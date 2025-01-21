#include <stdio.h>
#include <stdarg.h>

#define MAXLEN 1024

typedef union arg {
	int i;
	unsigned u;
	double d;
	char *s;
	void *p;
} Arg;

void minprintf(char *fmt, ...);

int main(void) {
	minprintf(":%-15.10s:\n%.7f\n", "hello, world", 123.123456789);
}

void minprintf(char *fmt, ...) {
	va_list ap; /* points to each unnamed arg in turn */
	Arg arg;
	char *p, *pbak, *f, format[MAXLEN];

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (f=format,p=fmt; *p; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		f = format;
		*f++ = *p;
		pbak = p++; /* if format parsing fails, simply print everything */
		/* left adjustment */
		if (*p == '-') {
			*f++ = *p++;
		}

		/* width */
		while (*p >= '0' && *p <= '9') {
			*f++ = *p++;
		}

		/* skip the point delimeter */
		if (*p == '.') {
			*f++ = *p++;
		}

		/* read precision, default is 6 */
		while (*p >= '0' && *p <= '9') {
			*f++ = *p++;
		}
		*f++ = *p;
		*f = '\0';
		switch (*p) {
		case 'd':
		case 'o':
		case 'x':
		case 'X':
		case 'i':
			arg.i = va_arg(ap, int);
			printf(format, arg.i);
			break;
		case 'u':
			arg.u = va_arg(ap, unsigned);
			printf(format, arg.u);
			break;
		case 'e':
		case 'f':
		case 'g':
		case 'G':
			arg.d = va_arg(ap, double);
			printf(format, arg.d);
			break;
		case 'p':
			arg.p = va_arg(ap, void *);
			printf(format, arg.p);
			break;
		case 's':
			arg.s = va_arg(ap, char *);
			printf(format, arg.s);
			break;
		default:
			putchar(*pbak);
			break;
		}
	}
	va_end(ap); /* clean up when done */
}
