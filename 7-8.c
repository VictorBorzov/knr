#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 28
#define LINELEN 1024

int print_pages(char *, int); /* prints filename content by paged */

int main(int argc, char *argv[]) {
	char c;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILES\n", *argv);
		exit(EXIT_FAILURE);
	}

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0])
			switch (c) {
			case 'h':
				fprintf(stdout, "Usage: find -x -n pattern\n");
				exit(EXIT_SUCCESS);
				break;
			default:
				fprintf(stderr, "Usage: %s FILES\n", *argv);
				exit(EXIT_FAILURE);
				break;
			}
	}

	while (*argv) {
		if (!print_pages(*argv, PAGELEN))
			exit(EXIT_FAILURE);
		++argv;
	}

	exit(EXIT_SUCCESS);
}

int print_pages(char *filename, int pagelen) {
	FILE *f;
	char line[LINELEN], *lp;
	long long ln;
	int pagen;

	if ((f=fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: couldn't open %s\n", filename);
		return 1;
	}

	fprintf(stdout, "\n\t\t\tFile: %s\n\n", filename);
	if (pagelen == 1) {
		fputs("\t\t\tPage 1\n\n", stdout);
		pagen = 2;
	} else
		pagen = 1;


	for (ln = 2; (lp=fgets(line, LINELEN, f)) != NULL; ++ln) {
		if (ln % pagelen == 0) {
			fprintf(stdout, "\n\t\t\tPage %d\n\n", pagen);
			++pagen;
		}
		fputs(line, stdout);
	}
	fprintf(stdout, "\t\t\tPage %d\n\n\n", pagen);
	fclose(f);
}

