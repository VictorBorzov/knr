#include <stdio.h>

int main(void) {
	int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int i;
	for (i = 0; i < 9; ++i) {
		printf("%d%c", i, i % 3 == 2 ? '\n' : ' ');
	}

	i = 1;
	printf("You have %d item%s.\n", i, i == 1 ? "" : "s");
	return 0;
}




