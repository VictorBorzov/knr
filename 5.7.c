#include <stdio.h>
#include <stdlib.h>

static int daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

void test(int daytabs[][13], int lim);

int main(void) {
	int i, j;
	test(daytab, 13);

	exit(EXIT_SUCCESS);
}

void test(int (*daytabs)[], int len) {
	for (int i = 0; i < len; ++i) {
		printf("%2i ", (*daytabs)[i]);
	}
	putchar('\n');
	for (int i = 0; i < len; ++i) {
		printf("%2i ", (*daytabs)[i]);
	}
}
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	for (i = 1; i < month; ++i) {
		day += daytab[leap][i];
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	for (i = 1; yearday > daytab[leap][i]; ++i) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}
