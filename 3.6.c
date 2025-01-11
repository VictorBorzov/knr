#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i = 5;
	do {
		printf("%d\n", i);
		if (i++ == 4) {
			goto clean;
		}
	} while (i < 5);
clean:
	printf("Resources are cleaned\n");
	exit(EXIT_SUCCESS);
}
