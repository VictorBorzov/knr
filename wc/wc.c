#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

main() {
		int state, c, nl, nw, nc;
		nl = nw = nc = 0;

		state = OUT;
		while ((c = getchar()) != EOF) {
				++nc;
				if (c == '\n')
						++nl;
				if (c == '\n' || c == ' ' || c == '\t')
						state = OUT;
				else if (state == OUT) {
						++nw;
						state = IN;
				}
		}
		printf("lines\twords\tchars\n");
		printf("%d\t%d\t%d\n", nl, nw, nc);
}
