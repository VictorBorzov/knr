#include <stdio.h>
#include <stdlib.h>

#define swap(t, x, y) t _tmp=x;x=y;y=_tmp
#define dprint(expr) printf(#expr "=%c\n", expr);
#define d3print(a, b, c) dprint(a); dprint(b); dprint(c)

int main(void) {
	char t = 't', x = 'x', y = 'y';
	d3print(t, x, y);
	swap(char, x, y);
	d3print(t, x, y);
	exit(EXIT_SUCCESS);
}
