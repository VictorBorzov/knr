#include <stdio.h>

int main(void) {
	int arr[8];
	int i = 0;
	while (i < 8) {
		printf("setting arr[%i] = %i\n", i, i);
		arr[i] = i++; /* compare with i += 1 */
	}
	for (int i = 0; i < 8; ++i) {
		printf("%s%i%s", i == 0 ? "[" : ", ", arr[i], i == 7 ? "]\n" : "");
	}
	return 0;
}




