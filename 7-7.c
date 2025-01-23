#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

typedef struct {
	unsigned int except : 1;
	unsigned int number : 1;
} Flags;

void grep(FILE *, char *, Flags); /* print each line from open file with pattern */

/* grep print lines that match pattern 1st arg */
/* accepts optional arguments n, x in any order */
int main(int argc, char *argv[]) {
	Flags flags;
	FILE *f;
	char c, *pattern;

	flags.except = flags.number = 0;
	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				flags.except = 1;
				break;
			case 'n':
				flags.number = 1;
				break;
			case 'h':
				fprintf(stdout, "Usage: find -x -n pattern\n");
				exit(EXIT_SUCCESS);
				break;
			default:
				fprintf(stderr, "ERROR: illegal option %c\n", c);
				fprintf(stderr, "Usage: find -x -n pattern\n");
				exit(EXIT_FAILURE);
				break;
			}
	}

	if ((pattern=*argv++) == NULL) {
		fprintf(stderr, "ERROR: pattern not found\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "DEBUG: except=%s,number=%s,pattern=%s\n",
		(flags.except) ? "true" : "false",
		(flags.number) ? "true" : "false",
		pattern);

	if (argc > 1) { /* grep files from argv */
		while (*argv) {
			fprintf(stderr, "DEBUG: grepping file %s\n", *argv);
			f = fopen(*argv, "r");
			if (f == NULL) {
				fprintf(stderr, "ERROR: couldn't open %s\n", *argv);
				exit(EXIT_FAILURE);
			}
			grep(f, pattern, flags);
			fclose(f);
			++argv;
		}
	} else { /* grep stdin */
		fprintf(stderr, "DEBUG: grepping from stdin\n");
		grep(stdin, pattern, flags);
	}

	exit(EXIT_SUCCESS);
}

void grep(FILE *f, char *pattern, Flags flags) {
	char line[MAXLINE], *lp, found;
	long long ln, fc; /* line number */

	ln = 1;
	fc = 0; /* founds */
	while ((lp=fgets(line, MAXLINE, f)) != NULL) {
		found = (strstr(line, pattern) != NULL);
		if (found != flags.except) {
			if (flags.number)
				fprintf(stdout, "%ld: ", ln);
			fprintf(stdout, "%s", line);
			++fc;
		}
		++ln;
	}
	fprintf(stdout, "%ld", fc);
}
