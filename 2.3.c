#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int atoi2(char s[]); /* reads int from string */
int htoi(char s[]); /* reads hex int from string */
char lower(char c);
char upper(char c);
void to_lower(char buffer[]);
void to_upper(char buffer[]);

unsigned long int next = 1;
int rand(void);
void srand(unsigned int seed);
int random2(int, int);

int main() {
	unsigned int i = -1;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	srand(time(0));
	for (i = 0; i < 10; ++i) {
		printf("%i ", random2(0, 10));
	}
	return 0;
	printf("Set seed = ");
	if ((nread = getline(&line, &len, stdin)) != -1) {
		int s = atoi2(line);
		printf("setting seed to %i...\n", s);
		srand(s);
		for (int i = 0; i < 10; ++i) {
			int r = rand();
			printf("%i\n", r);
		}
	}
	free(line);
	return 0;
}

int atoi2(char s[]) {
	int i, n = 0;
	for (i = 0; s[i] != '\0' && s[i] >= '0' && s[i] <= '9'; ++i) {
		n = 10 * n + (s[i] - '0');
	}
	return n;
}

int htoi(char s[]) {
	int i = 0, n = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
		i = 2;
	}
	while (s[i] != '\0') {
		if (s[i] >= '0' && s[i] <= '9') {
			n = 16 * n + s[i] - '0';
		} else if (s[i] >= 'a' && s[i] <= 'f') {
			n = 16 * n + 10 + s[i] - 'a';
		} else if (s[i] >= 'A' && s[i] <= 'F') {
			n = 16 * n + 10 + s[i] - 'A';
		} else {
			break;
		}
		++i;
	}
	return n;
}

void to_lower(char s[]) {
	for (int i = 0; s[i] != '\0'; ++i) {
		s[i] = lower(s[i]);
	}
}

void to_upper(char s[]) {
	for (int i = 0; s[i] != '\0'; ++i) {
		s[i] = upper(s[i]);
	}
}

char lower(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 'a' + c - 'A';
	}
	return c;
}

char upper(char c) {
	if (c >= 'a' && c <= 'z') {
		return 'A' + c - 'a';
	}
	return c;
}

int random2(int begin, int end) {
	return begin + rand() % (end - begin);
}

/* rand: return pseudo-random integer on 0..32767 */
int rand(void) {
	next = next * 1103515245 + 12345;
	return (unsigned int) (next / 65536) % 32768;
}

/* set seed for rand */
void srand(unsigned int seed) {
	next = seed;
}

