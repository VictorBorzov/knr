#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void filecopy(int fin, int fout);

int main(int argc, char *argv[]) {
	const char *help = "Usage: cat FILES\n";
	int f1, n;

	if (argc < 2) {
		write(2, help, strlen(help));
		exit(EXIT_FAILURE);
	}


	while (*++argv) {
		if ((f1=open(*argv, O_RDONLY, 0)) == -1) {
			fprintf(stderr, "ERROR: couldn't read %s\n", *argv);
			exit(EXIT_FAILURE);
		}
		filecopy(f1, 1);
		close(f1);
	}


	exit(EXIT_SUCCESS);
}

/* filecopy: copy file in to file out */
void filecopy(int fin, int fout) {
	static char buf[BUFSIZ];
	int n;

	while ((n=read(fin, buf, BUFSIZ)) > 0)
		write(fout, buf, n);
}
