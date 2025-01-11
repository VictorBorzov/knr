#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void) {
	int a[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int x, pos;
	for (int i = 0; i < 8; ++i) {
		printf("%s%d%s", i == 0 ? "[" : ", ", a[i], i == 7 ? "]\n" : "");
	}
	while (scanf("%i", &x) == 1) {
		pos = binsearch(x, a, 8);
		printf("found on position %d\n", pos);
	}
}

int binsearch(int x, int v[], int n) {
	/*
	  v is sorted increasingly for example 0..10
	  t = n, l = 0
	  i = (t + l) / 2
	  if (v[i] > x) t = i; else if (v[i] < x) l = i; else return i;
	  while t > l
	 */
	int l = 0, i = 0;
	while (n > l) {
		i = (n + l) / 2;
		/* printf("l=%d,t=%d,i=%d\n", l, n, i); */
		if (v[i] > x) {
			n = i;
		} else if (v[i] < x) {
			l = i + 1;
		} else {
			return i;
		}
	}
	return -1;
}

