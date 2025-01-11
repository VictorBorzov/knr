#include <stdio.h>
#include <limits.h>
#include <float.h>

#define COMPUTE_MAX(s1, s2) while (s2 > s1) { ++s1; ++s2; } /* computes max (s2) via overfloat */
#define COMPUTE_MIN(s1, s2) while (s2 > s1) { --s1; --s2; } /* computes min (s1) via overfloat */

void print_defined_lims(void); /* prints limits from limits.h */
void compute_limits(void); /* computes limits */
void compute_limits_short(void);
void compute_limits_int(void);
void compute_limits_long(void);
float compute_min_step();
double compute_min_step_double();
void compute_limits_float(void);
void compute_limits_double(void);

int main(void) {
	char c = '\0';
	printf("%c\n", c);
	printf("%c\n", 0);
	printf("%i\n", '\0' == 0);
	char *s = "Hello" "\n"
		  "World";
	printf("%s\n", s);
	return 0;
}

/* print limits of char, short, int, long, both signed and unsigned */
void print_defined_lims(void) {
	printf("LIMITS.H (signed)\n");
	printf("\tchar: from %i to %i\n", CHAR_MIN, CHAR_MAX);
	printf("\tint: from %i to %i\n", INT_MIN, INT_MAX);
	printf("\tshort: from %hi to %hi\n", SHRT_MIN, SHRT_MAX);
	printf("\tlong: from %li to %li\n", LONG_MIN, LONG_MAX);
	printf("\tfloat: from %f to %f\n", FLT_MIN, FLT_MAX);
	printf("\tdouble: from %lf to %lf\n", DBL_MIN, DBL_MAX);

	printf("LIMITS.H (unsigned)\n");
	printf("\tchar: from %i to %i\n", 0, UCHAR_MAX);
	printf("\tint: from %u to %u\n", 0, UINT_MAX);
	printf("\tshort: from %hhi to %hu\n", 0, USHRT_MAX);
	printf("\tlong: from %lli to %lu\n", 0, ULONG_MAX);
}

void compute_limits_short(void) {
	short s1 = 0, s2 = 1;
	COMPUTE_MAX(s1, s2);
	short max_s = s1;
	s1 = 0; s2 = 1;
	COMPUTE_MIN(s1, s2);
	short min_s = s2;
	printf("short: from %hi to %hi\n", min_s, max_s);

	unsigned char i1 = 1, i2 = 2;
	COMPUTE_MAX(i1, i2);
	unsigned char max_i = i1;
	i1 = 0; i2 = 1;
	COMPUTE_MIN(i1, i2);
	unsigned char min_i = i2;
	printf("unsigned char: from %i to %i\n", min_i, max_i);
}

/* compute minimal positive float number */
float compute_min_step(void) {
	/*
	  multiply by 0.1 until it's greater than 0 and different from previous number.
	 */
	float fp = 0, f = 1;
	int i = 1;
	while (f != 0) {
		printf("step %i, fp = %e, f = %e\n", i++, fp, f);
		fp = f;
		f *= 0.1;
	}
	return fp;
}

double compute_min_step_double(void) {
	/*
	  multiply by 0.1 until it's greater than 0 and different from previous number.
	 */
	double fp = 0, f = 1;
	int i = 1;
	while (f != 0) {
		printf("step %i, fp = %e, f = %e\n", i++, fp, f);
		fp = f;
		f *= 0.1;
	}
	return fp;
}

/* computes and prints double min and double max */
void compute_limits_double(void) {
	double min, max, fpp, fp, f, step;
	fpp = 0; fp = 0; f = -1; step = 1e308;
	int i = 1;
	while (step != 0) {
		printf("step = %e, fpp = %e, fp = %e, f = %e\n", step, fpp, fp, f);
		while (f != fp) {
			fpp = fp;
			fp = f;
			f -= step;
			/* printf("step = %e, fpp = %e, fp = %e, f = %e\n", step, fpp, fp, f); */
			/* if (i++ > 1e3) { */
			/* 	return; */
			/* } */
		}
		printf("min found! step = %e, fpp = %e, fp = %e, f = %e\n", step, fpp, fp, f);
		step *= 0.1;
		f = fpp;
	}
	min = fp;

	fpp = 0; fp = 0; f = 1; step = 1e36;
	while (step != 0) {
		while (f != fp) {
			fpp = fp;
			fp = f;
			f += step;
		}
		step *= 0.1;
		f = fpp;
	}
	max = fp;


	printf("double: from %e to %e\n", min, max);
}
/* computes and prints float min and float max */
void compute_limits_float(void) {
	/*
	  decrease by step until it's not bigger than 0;
	  when it is - multiply step by 0.1 and repeat from prelast value (which is less than 0)
	 */

	float min, max, fpp, fp, f, step;
	fpp = 0; fp = 0; f = -1; step = 1e36;
	while (step != 0) {
		while (f != fp) {
			fpp = fp;
			fp = f;
			f -= step;
		}
		step *= 0.1;
		f = fpp;
	}
	min = fp;

	fpp = 0; fp = 0; f = 1; step = 1e36;
	while (step != 0) {
		while (f != fp) {
			fpp = fp;
			fp = f;
			f += step;
		}
		step *= 0.1;
		f = fpp;
	}
	max = fp;


	printf("float: from %e to %e\n", min, max);
}
