#include <stdio.h>
#include <stdlib.h>

#define forever for(;;) /* infinite loop */
#define max(A, B) A > B ? A : B
#define square(x) x * x /* WRONG */
/* # sign expand expr with quotes, space between strings concatenates them */
#define dprint(expr) printf(#expr " = %g\n", expr)
#define paste(front, back) front ## back /* makes paste(front, back) frontback */

// #undef max

int main(void) {
	int i, j;
	i = j = 0;
	printf("i=%d,j=%d\n", i, j);
	printf("%d\n", max(i++, j++)); /* WRONG */
	printf("i=%d,j=%d\n", i, j);
	printf("%d\n", square(5+1)); /* WRONG */
	float xy = 3/2.;
	dprint(paste(x,y));
	exit(EXIT_SUCCESS);
	forever {
		printf("Hello! Please press enter to continue\n");
		char c = getchar();
	}
}


