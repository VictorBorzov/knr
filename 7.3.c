#include <stdio.h>

int main(void) {
	int n;
	int a, b, c;
	while ((n=scanf("%d %d %d", &a, &b, &c)) == 3) {
		printf("read %d numbers\n", n);
	}
}
