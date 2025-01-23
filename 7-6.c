#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLEN 1024

void print_help(char *name) {
	if (errno) {
		fprintf(stderr, "ERROR");
	}
	printf("Usage: %s <FILE1> <FILE2>\n", name);
}

int main(int argc, char *argv[]) {
	FILE *f1, *f2;
	char l1[MAXLEN], l2[MAXLEN], *lp1, *lp2;
	int n;

	if (argc != 3 || (f1=fopen(argv[1], "r")) == NULL || (f2=fopen(argv[2], "r")) == NULL) {
		print_help(argv[0]);
		exit(EXIT_FAILURE);
	}

	n = 1;
	while ((lp1=fgets(l1, MAXLEN, f1)) != NULL && (lp2=fgets(l2, MAXLEN, f2)) != NULL) {
		if (strcmp(l1, l2) != 0) {
			fprintf(stdout, "line %d:\n%s\n%s\n%s\n%s",
				n, argv[1], l1, argv[2], l2);
			break;
		}
		++n;
	}
	if (lp1 == NULL && (lp2=fgets(l2, MAXLEN, f2)) != NULL) { /* f1 is shorter */
		fprintf(stdout, "line %d:\n%s\n%s\n\n%s\n%s",
			n, argv[1], lp1 ? l1 : "EOF", argv[2], lp2 ? l2 : "EOF");
	} else if (lp1 != NULL && lp2 == NULL) { /* f2 is shorter */
		fprintf(stdout, "line %d:\n%s\n%s\n%s\n%s\n",
			n, argv[1], lp1 ? l1 : "EOF", argv[2], lp2 ? l2 : "EOF");
	}
	fclose(f1);
	fclose(f2);

	exit(EXIT_SUCCESS);
}
