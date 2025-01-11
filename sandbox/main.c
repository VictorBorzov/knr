#include <stdio.h>

#define LOWER 0    /* lower limit of table */
#define UPPER 300  /* upper limit */
#define STEP  20   /* step size */

/* print Farhenheit-Celsius table */
main0() {
		float lower = 0, upper = 300, step = 20;
		float fahr = lower, celsius;
		printf("Farhenheit-Celsius table for fahr = 0, 20, ..., 300; floating-point version\n");
		printf("============================================================================\n");
		for (fahr = UPPER; fahr >= LOWER; fahr -= STEP) {
				celsius = 5.0 / 9.0 * (fahr - 32.0);
				printf("\t%3.0f %6.1f\n", fahr, celsius);
		}

		printf("============================================================================\n");

		printf("Celsius-Farhenheit table for fahr = -30, -25, ..., 30; floating-point version\n");
		printf("============================================================================\n");
		lower = -60; upper = 60; step = 5;
		celsius = lower;
		while (celsius <= upper) {
				fahr = celsius * 9.0 / 5.0 + 32.0;
				printf("\t%3.0f %6.1f\n", celsius, fahr);
				celsius += step;
		}
		printf("============================================================================\n");

}

main1() {
		int c;
		printf("Please enter the character:\n");
		int expression = c != getchar();
		printf("expression 'c = getchar() != EOF' is equal to %d\n", expression);
		printf("EOF = %i\n", EOF);
}

main2() {
		/* int nc; */
		/* while (getchar() != EOF) { */
		/* 		++nc; */
		/* } */
		double nc;
		for (nc = 0; getchar() != EOF; ++nc);
		printf("input contains %.0f characters!\n", nc);
}

main3() {
		long long int n = 0, s = 0, t = 0;
		int c;
	    while ((c = getchar()) != EOF) {
				if (c == '\n') {
						++n;
				} else if (c == ' ') {
						++s;
				} else if (c == '\t') {
						++t;
				}
		}
		printf("Found %lli newlines, %lli spaces, and %lli tabs!\n", n, s, t);
}

main4() {
		int prev, c;
		if ((prev = getchar()) == EOF) {
				return;
		}

		putchar(prev);
		while ((c = getchar()) != EOF) {
				if (c != ' ' || prev != ' ') {
						putchar(c);
				}
				prev = c;
		}
}

main() {
		int c, d;
		c = d = 0;
		/* true and false or true -> true */
		/* false and false or true -> true */
		/* (true or false) and false -> true */
		if (d == 0 || c == 2 && c == 1) {
				printf("Yes\n");
		} else
				printf("No\n");
}

