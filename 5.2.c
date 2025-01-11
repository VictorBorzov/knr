#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 1024

#define parr(arr, lim) \
	putchar('['); \
	for (int i = 0; i < lim; ++i) printf("%d%s", arr[i], (i == lim-1) ? "" : ", "); \
	printf("]\n")

static int getdata(int *n) {
	static int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	static int pos = 0;

	if (pos < 10) {
		*n = data[pos++];
		return 1;
	}
	return 0;
}

int main(void) {
	int arr[20] = {}, i = 5;
	parr(arr, 20);
	for (i = 5; i < 20 && getdata(&arr[i]); ++i);
	parr(arr, 20);
	exit(EXIT_SUCCESS);
}
