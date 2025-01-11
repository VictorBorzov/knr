#include <stdlib.h>
#include <stdio.h>

#define SIZE 4

void shellsort(int v[], int n); /* sort v[0]...v[n-1] into increasing order */
void reverse(int v[], int n); /* reverse v[0]...v[n-1] in place */

int main(void) {
	int v[SIZE];
	int i;
	int seed = 69;

	for (i = 0; i < SIZE; ++i) {
		v[i] = rand() % 20;
	}

	for (i = 0; i < SIZE; ++i) {
		printf("%s%d%s", i == 0 ? "[" : ", ", v[i], i == (SIZE - 1) ? "]\n" : "");
	}

	shellsort(v, SIZE);
	for (i = 0; i < SIZE; ++i) {
		printf("%s%d%s", i == 0 ? "[" : ", ", v[i], i == (SIZE - 1) ? "]\n" : "");
	}

	reverse(v, SIZE);
	for (i = 0; i < SIZE; ++i) {
		printf("%s%d%s", i == 0 ? "[" : ", ", v[i], i == (SIZE - 1) ? "]\n" : "");
	}

	exit(EXIT_SUCCESS);
}

void shellsort(int v[], int n) {
	int gap, i, j, tmp;

	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; ++i) {
			for (j = i - gap; j >= 0  && v[j] > v[j + gap]; j -= gap) {
				tmp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = tmp;
			}
		}
	}
}

void reverse(int v[], int n) {
	int c, i, j;

	for (i = 0, j = (n-1); i < j; ++i, --j)
		c = v[i], v[i] = v[j], v[j] = c;
}
