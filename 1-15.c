#include <stdio.h>

#define LOWER 0    /* lower limit of table */
#define UPPER 300  /* upper limit */
#define STEP  20   /* step size */

float fahrtocel(float fahr); /* convert fahrenheit to celcius */
float celtofahr(float cel); /* convert celcius to fahrenheit */

/* print Farhenheit-Celsius table */
int main() {
	float lower = 0, upper = 300, step = 20;
	float fahr = lower, celsius;
	printf("============================================================================\n");
	printf("Farhenheit-Celsius table for fahr = 0, 20, ..., 300; floating-point version\n");
	printf("============================================================================\n");
	for (fahr = UPPER; fahr >= LOWER; fahr -= STEP) {
		celsius = fahrtocel(fahr);
		printf("\t%3.0f %6.1f\n", fahr, celsius);
	}

	printf("============================================================================\n");

	printf("Celsius-Farhenheit table for fahr = -30, -25, ..., 30; floating-point version\n");
	printf("============================================================================\n");
	lower = -60; upper = 60; step = 5;
	celsius = lower;
	while (celsius <= upper) {
		fahr = celtofahr(celsius);
		printf("\t%3.0f %6.1f\n", celsius, fahr);
		celsius += step;
	}
	printf("============================================================================\n");

	return 0;
}

float fahrtocel(float fahr) {
	return 5.0 / 9.0 * (fahr - 32.0);
}
float celtofahr(float cel) {
	return cel * 9.0 / 5.0 + 32.0;
}


