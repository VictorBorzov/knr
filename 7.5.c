#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

int widths[] = { [0 ... 99] = 1 };

long long int next;


/* RAND_MAX assumed to be 32767 */
int myrand(void) {
	next = next * 1103515245 + 12345;
	return((unsigned)(next/65536) % 32768);
}

void mysrand(unsigned int seed) {
	next = seed;
}

void print_hist(FILE *f, int histogram[], int size, int min_norm, int max_norm);

#define SIZE 60
int main(void) {
	char c[2];
	int n, numbers[SIZE], hist[SIZE];

	srand(clock());
	for (n = 0; n < SIZE; ++n) {
		numbers[n] = rand() % SIZE;
		hist[n] = 0;
	}

	for (n = 0; n < SIZE; ++n)
		++hist[numbers[n]];

	print_hist(stdout, hist, SIZE, 0, 10);


	mysrand(clock());
	for (n = 0; n < SIZE; ++n) {
		numbers[n] = myrand() % SIZE;
		hist[n] = 0;
	}

	for (n = 0; n < SIZE; ++n)
		++hist[numbers[n]];

	print_hist(stdout, hist, SIZE, 0, 10);


	return 0;

	c[0] = getc(stdin);
	c[1] = '\0';
	fprintf(stdout, "got '%s', stdin is %s\n",
		(c[0] == '\n') ? "\\n" :
		(c[0] == EOF) ? "EOF" : c,
		feof(stdin) ? "empty" : "not empty");

	ungetc(c[0], stdin);
	ungetc('3', stdin);
	ungetc('3', stdin);


	c[0] = getc(stdin);
	c[1] = '\0';
	fprintf(stdout, "got '%s', stdin is %s\n",
		(c[0] == '\n') ? "\\n" :
		(c[0] == EOF) ? "EOF" : c,
		feof(stdin) ? "empty" : "not empty");

	c[0] = getc(stdin);
	c[1] = '\0';
	fprintf(stdout, "got '%s', stdin is %s\n",
		(c[0] == '\n') ? "\\n" :
		(c[0] == EOF) ? "EOF" : c,
		feof(stdin) ? "empty" : "not empty");

	c[0] = getc(stdin);
	c[1] = '\0';
	fprintf(stdout, "got '%s', stdin is %s\n",
		(c[0] == '\n') ? "\\n" :
		(c[0] == EOF) ? "EOF" : c,
		feof(stdin) ? "empty" : "not empty");

	c[0] = getc(stdin);
	c[1] = '\0';
	fprintf(stdout, "got '%s', stdin is %s\n",
		(c[0] == '\n') ? "\\n" :
		(c[0] == EOF) ? "EOF" : c,
		feof(stdin) ? "empty" : "not empty");
}

void print_hist(FILE *f, int histogram[], int size, int min_norm, int max_norm) {
	int i, j, normalized[size];
	int min, max;

	for (i=0, min=INT_MAX, max=INT_MIN; i < size; ++i) {
		if (histogram[i] > max)
			max = histogram[i];
		if (histogram[i] < min)
			min = histogram[i];
	}

	for (i = 0; i < size; ++i) {
		normalized[i] = (int)round(histogram[i] * (max_norm - min_norm) / (max - min));
	}
	max = max_norm;

	/* for (i = 0; i < size; ++i) { */
	/* 	if (normalized[i] == 0) { */
	/* 		continue; */
	/* 	} */

	/* 	fprintf(f, "%-2d%3d ", i, histogram[i]); */
	/* 	for (j = 0; j < normalized[i]; ++j) { */
	/* 		fputc('=', f); */
	/* 	} */
	/* 	fputc('\n', f); */
	/* } */

	fputc('\n', f);
	for (i = max; i > 0; --i) {
		for (j = 0; j < size; ++j) {
			if (normalized[j] == 0) {
				continue;
			}

			if (normalized[j] >= i) {
				fputc('|', f);
				fputc('|', f);
				fputc('|', f);
			} else {
				fputc(' ', f);
				fputc(' ', f);
				fputc(' ', f);
			}
		}
		fputc('\n', f);
	}
	for (i = 0; i < size; ++i) {
		if (normalized[i] == 0) {
			continue;
		}

		fprintf(f, "%2d ", normalized[i]);
	}
	fputc('\n', f);

	for (i = 0; i < size; ++i) {
		if (normalized[i] == 0) {
			continue;
		}
		fprintf(f, "%2d ", i);
	}
	fputc('\n', f);
}
