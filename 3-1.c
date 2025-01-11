#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYLEN 10
#define SAMPLESIZE 10000

int binsearch1(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void) {
	clock_t tic, toc;
	int a[ARRAYLEN], targets[SAMPLESIZE], i, j, pos;
	long int measures[SAMPLESIZE];
	long double avg1, avg2;
	avg1 = avg2 = 0;

	// set up data array 0..ARRAYLEN
	for (i = 0; i < ARRAYLEN; ++i) {
		a[i] = i;
	}

	// generate random targets from 0 to ARRAYLEN-1
	for (i = 0; i < SAMPLESIZE; ++i) {
		targets[i] = rand() % ARRAYLEN;
	}

	// measure binsearch1
	for (i = 0; i < SAMPLESIZE; ++i) {
		tic = clock();
		for (j = 0; j < SAMPLESIZE; ++j) {
			pos = binsearch1(targets[i], a, ARRAYLEN);
		}
		toc = clock();
		measures[i] = toc - tic;
	}

	// compute avg1 for binsearch1
	for (i = 0; i < SAMPLESIZE; ++i) {
		avg1 += (double)measures[i];
	}
	avg1 /= SAMPLESIZE;
	printf("binsearch1 in average takes %6llf clock ticks\n", avg1);

	// measure binsearch2
	for (i = 0; i < SAMPLESIZE; ++i) {
		tic = clock();
		for (j = 0; j < SAMPLESIZE; ++j) {
			pos = binsearch2(targets[i], a, ARRAYLEN);
		}
		toc = clock();
		measures[i] = toc - tic;
	}

	// compute avg1 for binsearch1
	for (i = 0; i < SAMPLESIZE; ++i) {
		avg2 += measures[i];
	}
	avg2 /= SAMPLESIZE;
	printf("binsearch2 in average takes %6llf clock ticks\n", avg2);
	printf("avg2 is %6llf times faster\n", avg1 / avg2);
}

int binsearch1(int x, int v[], int n) {
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

int binsearch2(int x, int v[], int n) {
	int l = 0, i = 0, res = -1;
	while (n > (l + 1)) {
		i = (n + l) / 2;
		/* printf("l=%d,t=%d,i=%d\n", l, n, i); */
		res = v[i];
		if (res > x) {
			n = i;
		} else {
			l = i;
		}
	}

	if (v[l] == x) {
		return l;
	} else if (v[n] == x) {
		return n;
	} else {
		return -1;
	}
}

