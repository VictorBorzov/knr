#include <stdio.h>
#include <stdlib.h>

int main(void) {
	void printd(int);
	void qsort2(int[], int, int);

	int arr[] = { 9, 1, 3 };
	qsort2(arr, 0, 2);
	for (int i = 0; i < 3; ++i) {
		printf("%i ", arr[i]);
	}
	exit(EXIT_SUCCESS);
}

void printd(int n) {
	if (n < 0) {
		putchar('-');
		n *= -1;
	}
	if (n / 10) {
		printd(n / 10);
	}
	putchar(n % 10 + '0');
}

void qsort2(int v[], int l, int r) {
	int i, last;
	void swap(int[], int, int);

	if (l >= r) {
		return;
	}

	/* move middle element to the left */
	swap(v, l, (l + r) / 2);
	last = l;
	for (i = l+1; i <= r; ++i) {
		if (v[i] < v[l]) {
			swap(v, i, last++);
		}
	}
	qsort2(v, l, last-1);
	qsort2(v, last+1, r);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
	int tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}
