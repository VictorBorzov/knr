#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(void) {
	minprintf("%d -> %f\n", 10, 1.1);
}

void minprintf(char *fmt, ...) {
	va_list ap; /* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	unsigned uval;
	double dval;
	void *pval;

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		case 'x':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		case 'X':
			ival = va_arg(ap, int);
			printf("%X", ival);
			break;
		case 'i':
			ival = va_arg(ap, int);
			printf("%i", ival);
			break;
		case 'u':
			uval = va_arg(ap, unsigned);
			printf("%u", ival);
			break;
		case 'e':
			dval = va_arg(ap, double);
			printf("%e", dval);
			break;
		case 'E':
			dval = va_arg(ap, double);
			printf("%E", dval);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 'g':
			dval = va_arg(ap, double);
			printf("%g", dval);
			break;
		case 'G':
			dval = va_arg(ap, double);
			printf("%g", dval);
			break;
		case 'p':
			pval = va_arg(ap, void *);
			printf("%p", pval);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; ++sval)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap); /* clean up when done */
}
