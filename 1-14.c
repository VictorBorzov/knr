#include <stdio.h>
#include <limits.h>
#include <math.h> /* compile with -lm */

#define HISTOGRAM_LENGTH 128
#define NORMALIZED_MAX 10 /* histogram display size */
#define NORMALIZED_MIN 0

/*
  Print histogram of the frequences of different characters in input.
*/

main() {
	int i, j, c, min, max;
	max = min = 0;
	int histogram[HISTOGRAM_LENGTH];
	int normalized[HISTOGRAM_LENGTH];

	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		normalized[i] = 0;
		histogram[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if ((int)c > 127)
			continue;
		++histogram[(int)c];

		if (histogram[(int)c] > max) {
			max = histogram[(int)c];
		}
	}

	/*
	  Normalize histogram:
	  new_ai = round(ai * (new_max - new_min) / (max - min))
	*/
	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		normalized[i] = (int)round(histogram[i] * (NORMALIZED_MAX - NORMALIZED_MIN) / (max - min));
	}
	max = NORMALIZED_MAX;

	printf("char  num\n");
	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		if (normalized[i] == 0) {
			continue;
		}

		c = (char)i;
		if (c == ' ') {
			printf("' ' %3d  ", histogram[i]);
		} else if (c == '\n') {
			printf("\\n %4d  ", histogram[i]);
		} else if (c == '\t') {
			printf("\\t %4d  ", histogram[i]);
		} else {
			printf("%c %5d  ", i, histogram[i]);
		}
		for (j = 0; j < normalized[i]; ++j) {
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
	putchar('\n');
	for (i = max; i > 0; --i) {
		for (j = 0; j < HISTOGRAM_LENGTH; ++j) {
			if (normalized[j] == 0) {
				continue;
			}

			if (normalized[j] >= i) {
				putchar('|');
				putchar('|');
				putchar('|');
			} else {
				putchar(' ');
				putchar(' ');
				putchar(' ');
			}
		}
		putchar('\n');
	}
	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		if (normalized[i] == 0) {
			continue;
		}

		printf("%2i ", normalized[i]);
	}
	putchar('\n');

	for (i = 0; i < HISTOGRAM_LENGTH; ++i) {
		if (normalized[i] == 0) {
			continue;
		}

		c = (char)i;
		if (c == ' ') {
			printf("' ' ");
		} else if (c == '\n') {
			printf("\\n ");
		} else if (c == '\t') {
			printf("\\t ");
		} else {
			printf("%c  ", c);
		}
	}
	putchar('\n');
}
