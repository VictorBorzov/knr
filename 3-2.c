#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 10240

void escape(char s[], char p[]); /* converts escape chars like \n and \t to escape sequences */
void unescape(char s[], char p[]); /* converts escape sequences into real chars */

int main(void) {
	char s[BUFFERSIZE], p[BUFFERSIZE];
	char c;
	int i;

	for (i = 0; (c = getchar()) != EOF; ++i) {
		s[i] = c;
	}

	unescape(s, p);

	for (i = 0; (c = p[i]) != '\0'; ++i) {
		putchar(p[i]);
	}

	exit(EXIT_SUCCESS);
}

void escape(char s[], char p[]) {
	int is, ip;
	is = ip = 0;
	char c;

	while (is < BUFFERSIZE && ip < BUFFERSIZE && (c = s[is++]) != '\0') {
		switch (c) {
		case '\n':
			p[ip++] = '\\';
			p[ip++] = 'n';
			break;
		case '\t':
			p[ip++] = '\\';
			p[ip++] = 't';
			break;
		default:
			p[ip++] = c;
			break;
		}
	}

	p[ip] = '\0';
	return;
}

void unescape(char s[], char p[]) {
	int is = 0, ip = 0;;
	char c, n;

	if ((c = s[is++]) == '\0') {
		p[ip] = '\0';
		return;
	}

	while ((n = s[is++]) != '\0') {
		if (c == '\\') {
			switch (n) {
			case 'n':
				p[ip++] = '\n';
				break;
			case 't':
				p[ip++] = '\t';
				break;
			default:
				p[ip++] = '\\';
				p[ip++] = n;
				break;
			}
			c = s[is++];
		} else {
			p[ip++] = c;
			c = n;
		}
	}

	p[ip] = '\0';
	return;
}
