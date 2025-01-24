#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filecopy(FILE *, FILE *);

char *mfgets(char *, int, FILE *); /* from the standard library */

int main(int argc, char *argv[]) {
	FILE *f;
	char *prog = *argv, c;

	if (argc == 1) /* no args; copy stdin */
		filecopy(stdin, stdout);
	else {
		while (--argc > 0) {
			if ((f=fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "ERROR: %s can't open %s\n", prog, *argv);
				exit(1);
			} else {
				filecopy(f, stdout);
				fclose(f);
			}
		}
	}
	if (ferror(stdout)) {
		fprintf(stderr, "ERROR: %s writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}

/* fgets: get at most n chars from iop */
char *mfgets(char *s, int n, FILE *iop) {
	register int c;
	register char *cs;

	cs = s;
	while (--n > 0 && (c=getc(iop)) != EOF) {
		if ((*cs++=c) == '\n') {
			break;
		}
	}
	*cs = '\0';

	return (c == EOF && cs == s) ? NULL : s;
}

/* fputs: put string s on file iop */
int mfputs(char *s, FILE *iop) {
	int c;

	while (c = *s++)
		putc(c, iop);
	return ferror(iop) ? EOF : 0;
}

/* getline: read a line, return length */
int mgetline(char *line, int max) {
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

/* filecopy: copy file in to file out */
void filecopy(FILE *in, FILE *out) {
	char buf[BUFSIZ];

	while (fgets(buf, BUFSIZ, in) != NULL)
		fputs(buf, out);
}
