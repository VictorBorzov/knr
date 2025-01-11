#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#define DEFAULTN 10

#define MAXLINES 1024
#define MAXLEN 1000 /* max length of any input line */

static char *alloc(int bn, int size); /* allocate in buffer bn */
static void freelastbuf(int bn); /* free buffer bn */
static int readlines(char *lines[], int lim);
static void writelines(char *lines[], int len, int n); /* writes n last lines */
static int getline2(char s[], int n);
void printdiagnostics(void);

/* tail: prints the last n lines of its input */
int main(int argc, char *argv[]) {
	int lastlen, len, n, i;

	n = DEFAULTN;
	if (*++argv && **argv == '-') {
		n = atoi(*argv+1);
	}

	/* fill sliding window of size n with lines */
	char *lines[n] = {};
	for (lastlen = 0; (len = readlines(lines, n)) > 0; lastlen = len);

	/* last n-lastlen lines are previous tail */
	for (i = lastlen; i < n; ++i) {
		if (*(lines+i))
			printf("%s", *(lines+i));
	}

	/* these are the lines filled at the end */
	for (i = 0; i < lastlen; ++i) {
		printf("%s", *(lines+i));
	}

	printdiagnostics();
	exit(EXIT_SUCCESS);
}

int getline2(char s[], int lim) {
	int i;

	for (i = 0; lim-- > 0 && (s[i] = getchar()) != EOF && s[i] != '\n'; ++i);

	i += (s[i] == '\n');
	s[i] = '\0';

	return i;
}

/* readlines: read n lines to the buffer */
int readlines(char *lines[], int n) {
	static int bn = 1;

	char **d = lines;
	char buffer[MAXLEN];
	int i, len;

	freelastbuf(bn);
	for (i = 0; i < n && (len = getline2(buffer, MAXLEN)) > 0; ++i) {
		if (!(*lines = alloc(bn, len+1))) {
			printf("ERROR: can't read line!\n");
			return 0;
		}
		strcpy(*lines++, buffer);
	}
	bn = (bn == 1) ? 2 : 1;
	return i;
}

static void writelines(char *lines[], int len, int n) {
	char **linesptr;
	for (linesptr = MAX(lines, lines+len-n-1); *linesptr && linesptr >= lines && n > 0; --len, --n)
		printf("%s", *linesptr++);
}

/***************************************************
 *********************ALLOCATOR.h*******************
***************************************************/

#define BUFFERSIZE 1000000
static char buffer1[BUFFERSIZE] = {};
static char buffer2[BUFFERSIZE] = {};
static int bp1 = 0;
static int bp2 = 0;

char *alloc(int bn, int size) {
	if (bn == 1) {
		if (bp1 + size > BUFFERSIZE) {
			printf("ERROR: out of memory!\n");
			return 0;
		}
		bp1 += size;
		return &buffer1[bp1-size];
	} else if (bn == 2) {
		if (bp2 + size > BUFFERSIZE) {
			printf("ERROR: out of memory!\n");
			return 0;
		}
		bp2 += size;
		return &buffer2[bp2-size];
	} else {
		printf("ERROR: wrong buffer number!\n");
		return 0;
	}
}

void freelastbuf(int bn) {
	if (bn == 1)
		bp1 = 0;
	else if (bn == 2)
		bp2 = 0;
	else
		printf("ERROR: wrong buffer number!\n");
}

void printdiagnostics(void) {
	printf("DEBUG: Used %i bytes (%i,%i)\n", bp1+bp2, bp1, bp2);
}
