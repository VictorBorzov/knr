#include <stdio.h>
#include <stdlib.h>

char *month_name(int n);

int main(void) {
	int x;
	scanf("%i", &x);
	printf("%s\n", month_name(x));
	exit(EXIT_SUCCESS);
}

char *month_name(int n) {
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May",	"June",
		"July", "August", "September",
		"October", "Novermber", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name [n];
}
