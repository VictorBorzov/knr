#include <unistd.h>

#define BUFSIZE 4096

int getchar(void);
int getchar2(void);

int main(void) {
	char buf[BUFSIZE];
	int n;

	while ((n=read(0, buf, BUFSIZE)) > 0)
		write(1, buf, n);
	return 0;
}

int getchar(void) {
	char c;
	return (read(0, &c, 1) == 1) ? (unsigned char) c : -1; /* EOF is -1 */
}


/* getchar: simple buffered version (does input in big chunks) */
int getchar2(void) {
	static char buf[BUFSIZE];
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) { /* buffer is empty */
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}

	return (--n >= 0) ? (unsigned char) *bufp++ : -1; /* EOF is -1 */
}

