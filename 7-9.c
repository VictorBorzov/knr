#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isupper(int c);
int isupper2(int c);

#define SAMPLE 1000
int main(void) {
	static int s[SAMPLE];
	int n, tmp;
	long long int l;
	clock_t tic, tok;

	/* generate sample */
	for (n = 0; n < SAMPLE; ++n)
		s[n] = rand() % 255;

	/* measure isupper */
	for (l=0, n=0; n < SAMPLE; ++n) {
		tic = clock();
		tmp = isupper(s[n]);
		tok = clock();
		l += (tok - tic);
	}
	fprintf(stdout, "avg1: %5.3ld\n", l);

	/* measure isupper */
	for (l=0, n=0; n < SAMPLE; ++n) {
		tic = clock();
		tmp = isupper2(s[n]);
		tok = clock();
		l += (tok - tic);
	}
	fprintf(stdout, "avg2: %5.3ld\n", l);
}

/* isupper: memory minimized */
int isupper(int c) {
	return (c >= 'A' && c <= 'Z');
}

enum CTYPE_MASK {
	DIGIT_MASK = 1 << 0,
	XDIGT_MASK = 1 << 1,
	LOWER_MASK = 1 << 2,
	UPPER_MASK = 1 << 3,
	ALPHA_MASK = 1 << 4,
	PUNCT_MASK = 1 << 5,
	SPACE_MASK = 1 << 6,
	PRINT_MASK = 1 << 7,
	CNTRL_MASK = 1 << 8,
	BLANK_MASK = 1 << 9,
	ALNUM_MASK = ALPHA_MASK | DIGIT_MASK,
	GRAPH_MASK = ALNUM_MASK | PUNCT_MASK
};

/* isupper2: time efficient */
int isupper2(int c) {
	static unsigned short ctype_bits[] =
		{
			[EOF   +1] = 0,
			['\0'  +1] = CNTRL_MASK,
			['\1'  +1] = CNTRL_MASK,
			['\2'  +1] = CNTRL_MASK,
			['\3'  +1] = CNTRL_MASK,
			['\4'  +1] = CNTRL_MASK,
			['\5'  +1] = CNTRL_MASK,
			['\6'  +1] = CNTRL_MASK,
			['\a'  +1] = CNTRL_MASK,
			['\b'  +1] = CNTRL_MASK,
			['\t'  +1] = CNTRL_MASK|SPACE_MASK|BLANK_MASK,
			['\n'  +1] = CNTRL_MASK|SPACE_MASK,
			['\v'  +1] = CNTRL_MASK|SPACE_MASK,
			['\f'  +1] = CNTRL_MASK|SPACE_MASK,
			['\r'  +1] = CNTRL_MASK|SPACE_MASK,
			['\x0E'+1] = CNTRL_MASK,
			['\x0F'+1] = CNTRL_MASK,
			['\x10'+1] = CNTRL_MASK,
			['\x11'+1] = CNTRL_MASK,
			['\x12'+1] = CNTRL_MASK,
			['\x13'+1] = CNTRL_MASK,
			['\x14'+1] = CNTRL_MASK,
			['\x15'+1] = CNTRL_MASK,
			['\x16'+1] = CNTRL_MASK,
			['\x17'+1] = CNTRL_MASK,
			['\x18'+1] = CNTRL_MASK,
			['\x19'+1] = CNTRL_MASK,
			['\x1A'+1] = CNTRL_MASK,
			['\x1B'+1] = CNTRL_MASK,
			['\x1C'+1] = CNTRL_MASK,
			['\x1D'+1] = CNTRL_MASK,
			['\x1E'+1] = CNTRL_MASK,
			['\x1F'+1] = CNTRL_MASK,

			[' '   +1] = SPACE_MASK|PRINT_MASK|BLANK_MASK,

			['!'   +1] = PUNCT_MASK|PRINT_MASK,
			['"'   +1] = PUNCT_MASK|PRINT_MASK,
			['#'   +1] = PUNCT_MASK|PRINT_MASK,
			['$'   +1] = PUNCT_MASK|PRINT_MASK,
			['%'   +1] = PUNCT_MASK|PRINT_MASK,
			['&'   +1] = PUNCT_MASK|PRINT_MASK,
			['\''  +1] = PUNCT_MASK|PRINT_MASK,
			['('   +1] = PUNCT_MASK|PRINT_MASK,
			[')'   +1] = PUNCT_MASK|PRINT_MASK,
			['*'   +1] = PUNCT_MASK|PRINT_MASK,
			['+'   +1] = PUNCT_MASK|PRINT_MASK,
			[','   +1] = PUNCT_MASK|PRINT_MASK,
			['-'   +1] = PUNCT_MASK|PRINT_MASK,
			['.'   +1] = PUNCT_MASK|PRINT_MASK,
			['/'   +1] = PUNCT_MASK|PRINT_MASK,

			['0'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['1'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['2'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['3'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['4'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['5'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['6'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['7'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['8'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,
			['9'   +1] = DIGIT_MASK|PRINT_MASK|XDIGT_MASK,

			[':'   +1] = PUNCT_MASK|PRINT_MASK,
			[';'   +1] = PUNCT_MASK|PRINT_MASK,
			['<'   +1] = PUNCT_MASK|PRINT_MASK,
			['='   +1] = PUNCT_MASK|PRINT_MASK,
			['>'   +1] = PUNCT_MASK|PRINT_MASK,
			['?'   +1] = PUNCT_MASK|PRINT_MASK,
			['@'   +1] = PUNCT_MASK|PRINT_MASK,

			['A'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['B'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['C'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['D'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['E'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['F'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK|XDIGT_MASK,
			['G'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['H'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['I'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['J'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['K'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['L'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['M'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['N'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['O'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['P'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['Q'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['R'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['S'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['T'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['U'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['V'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['W'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['X'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['Y'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,
			['Z'   +1] = ALPHA_MASK|UPPER_MASK|PRINT_MASK,

			['['   +1] = PUNCT_MASK|PRINT_MASK,
			['\\'  +1] = PUNCT_MASK|PRINT_MASK,
			[']'   +1] = PUNCT_MASK|PRINT_MASK,
			['^'   +1] = PUNCT_MASK|PRINT_MASK,
			['_'   +1] = PUNCT_MASK|PRINT_MASK,
			['`'   +1] = PUNCT_MASK|PRINT_MASK,

			['a'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['b'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['c'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['d'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['e'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['f'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK|XDIGT_MASK,
			['g'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['h'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['i'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['j'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['k'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['l'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['m'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['n'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['o'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['p'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['q'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['r'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['s'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['t'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['u'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['v'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['w'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['x'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['y'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,
			['z'   +1] = ALPHA_MASK|LOWER_MASK|PRINT_MASK,

			['{'   +1] = PUNCT_MASK|PRINT_MASK,
			['|'   +1] = PUNCT_MASK|PRINT_MASK,
			['}'   +1] = PUNCT_MASK|PRINT_MASK,
			['~'   +1] = PUNCT_MASK|PRINT_MASK,
			['\x7F'+1] = CNTRL_MASK
		};

	return (ctype_bits+1)[c] & UPPER_MASK;
}
