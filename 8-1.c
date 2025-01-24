#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	const char *help = "Usage: cat FILES\n";
	char buf[BUFSIZ];
	int f1, n;

	if (argc < 2) {
		write(2, help, strlen(help));
		exit(EXIT_FAILURE);
	}


	while (*++argv) {
		if ((f1=open(*argv, O_RDONLY, 0)) == -1) {
			n = sprintf(buf, "ERROR: couldn't read %s\n", *argv);
			write(2, buf, n);
			exit(EXIT_FAILURE);
		}

		while ((n=read(f1, buf, BUFSIZ)) > 0) {
			write(1, buf, n);
		}
		if (n == -1) {
			n = sprintf(buf, "ERROR: couldn't read %s\n", *argv);
			write(2, buf, n);
			exit(EXIT_FAILURE);
		}

		if (close(f1) != 0) {
			n = sprintf(buf, "ERROR: couldn't close %s\n", *argv);
			write(2, buf, n);
			exit(EXIT_FAILURE);
		}
	}


	exit(EXIT_SUCCESS);
}
