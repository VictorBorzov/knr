#include <stdio.h>
#include <stdlib.h>

int day_of_year(int y, int m, int d);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {
	int year, month, day, yearday, choice;
	printf("Would you like to compute day of the year(1) or day of the month(2)?\n");
	if (scanf("%i", &choice) != 1) {
		printf("Wrong format, sorry\n");
		exit(EXIT_SUCCESS);
	}

	switch (choice) {
	case 1:
		printf("Please enter year, month, and day: ");
		if (scanf("%i %i %i", &year, &month, &day) != 3) {
			printf("Wrong format, sorry\n");
			exit(EXIT_SUCCESS);
		}
		yearday = day_of_year(year, month, day);
		printf("%i\n", yearday);
		break;
	case 2:
		printf("Please enter year and year day: ");
		if (scanf("%i %i", &year, &yearday) != 2) {
			printf("Wrong format, sorry\n");
			exit(EXIT_SUCCESS);
		}
		month_day(year, yearday, &month, &day);
		printf("%i month %i day\n", month, day);
		break;
	default:
		printf("Wrong format, sorry\n");
	}

	exit(EXIT_SUCCESS);
}

static int leapyear[] =	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static int nonleapyear[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static int *daytab[] = { leapyear, nonleapyear };

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (month < 1 || month > 12 || day > *(*(daytab+leap)+month)) {
		printf("ERROR: month should be from 1 to 12\n");
		return -1;
	}
	for (i = 1; i < month; ++i) {
		day += *(*(daytab+leap)+i);
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	for (i = 1; yearday > *(*(daytab+leap)+i); ++i) {
		yearday -= *(*(daytab+leap)+i);
	}
	if (yearday < 0) {
		printf("ERROR: yearday is too big\n");
		return;
	}
	*pmonth = i;
	*pday = yearday;
}
