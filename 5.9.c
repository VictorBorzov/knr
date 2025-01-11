#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

/* echo: prints its arguments separated by blanks */
int echo(int argc, char *argv[]) {
	while (*++argv) {
		printf(*(argv+1) ? "%s " : "%s", *argv);
	}
	putchar('\n');
	exit(EXIT_SUCCESS);
}

int getline2(char *s, int lim);

/* grep print lines that match pattern 1st arg */
int grep1(int argc, char *argv[]) {
	char line[MAXLINE];
	int found = 0;

	if (argc != 2) {
		printf("Usage: find pattern\n");
		exit(EXIT_FAILURE);
	}
	while (getline2(line, MAXLINE) > 0) {
		if (strstr(line, argv[1]) != NULL) {
			printf("%s", line);
			found++;
		}
	}
	printf("%i\n", found);
	exit(EXIT_SUCCESS);
}

/* grep print lines that match pattern 1st arg */
/* accepts optional arguments n, x in any order */
int main(int argc, char *argv[]) {
	char line[MAXLINE];
	long int lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
	}

	if (argc != 1) {
		printf("Usage: find -x -n pattern\n");
		exit(EXIT_FAILURE);
	}

	while (getline2(line, MAXLINE) > 0) {
		++lineno;
		if ((strstr(line, *argv) != NULL) != except) {
			if (number) {
				printf("%ld:", lineno);
			}
			printf("%s", line);
			found++;
		} else {
		}
	}
	printf("%i\n", found);
	exit(EXIT_SUCCESS);
}

int getline2(char *s, int lim) {
	int i;
	for (i = 0; i < lim-1 && (*s=getchar()) != EOF && *s != '\n'; ++i, ++s);
	if (i > 0 && *s == '\n') {
		++s;
	}
	*s = '\0';
	return i;
}
