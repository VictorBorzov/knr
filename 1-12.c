#include <stdio.h>

#define IN 1   /* inside a word */
#define OUT 0  /* outside a word */

main() {
		int c, state;
		state = OUT;
		while ((c = getchar()) != EOF) {
				if (c == ' ' || c == '\n' || c == '\t') {
						if (state == IN) {
								state = OUT;
								putchar('\n');
						}
				} else {
						putchar(c);
						if (state == OUT) {
								state = IN;
						}
				}
		}
		putchar('\n');
}






