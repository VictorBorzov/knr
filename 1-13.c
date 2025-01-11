#include <stdio.h>
#include <limits.h>
#include <math.h> /* compile with -lm */

#define MAX_WORD_LENGTH 1024
#define HISTOGRAM_LENGTH MAX_WORD_LENGTH + 1
#define NORMALIZED_MAX 10 /* histogram size */
#define NORMALIZED_MIN 0

main() {
	int i, j, c, cwl, state, min, max;
	cwl = 0; /* current word length */
	max = 0;
	min = INT_MAX;
	int histogram[HISTOGRAM_LENGTH];
	int normalized[HISTOGRAM_LENGTH];

	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		normalized[i] = 0;
		histogram[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (cwl > MAX_WORD_LENGTH) {
				cwl = MAX_WORD_LENGTH;
			}
			if (cwl != 0) {
				++histogram[cwl];
				cwl = 0;
			}
		} else {
			++cwl;
		}
	}

	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		if (histogram[i] > max) {
			max = histogram[i];
		}
		if (histogram[i] < min) {
			min = histogram[i];
		}
	}

	/*
	  Normilize histogram:
	  new_ai = round(ai * (new_max - new_min) / (max - min))
	*/
	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		histogram[i] = (int)round(histogram[i] * (NORMALIZED_MAX - NORMALIZED_MIN) / (max - min));
	}

	printf(" len  number\n");
	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		if (histogram[i] == 0) {
			continue;
		}

		printf("%3d %3d  ", i, histogram[i]);
		for (j = 0; j < histogram[i]; ++j) {
			putchar('=');
		}
		putchar('\n');
	}

	/*
          len 2 3 4
	  num 3 1 5
	  =
	  =
	  =	  =
	  =	  =
	  = = =
	  2 3 4
	*/
	printf("\nVertical:\n");
	for (i = NORMALIZED_MAX; i >= 0; --i) {
		for (j = 0; j < HISTOGRAM_LENGTH; ++j) {
			if (histogram[j] == 0) {
				continue;
			}

			if (histogram[j] >= i) {
				putchar('|');
				putchar('|');
			} else {
				putchar(' ');
				putchar(' ');
			}
		}
		putchar('\n');
	}

}
