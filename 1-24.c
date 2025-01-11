#include <stdio.h>

/*
  Check unmatched braces, brackets, parentheses, single/double quotes.
  Take into account comments and escape sequences.
*/

int skip_until(char target); /* returns line with error, if ok returns 0 */
char getcharlog(); /* reads a character and track line/col number */

int line = 1;
int col = 1;

int main() {
	return skip_until(EOF);
}

int skip_until(char target) {
	int start = line;
	char prev, c;

	while ((c = getcharlog()) != EOF) {
		if (c == '"') {
			// skip everything including '\"' until '"', error if '\n' or eof
			do {
				prev = c;
				c = getcharlog();
				if (prev == '\\' && c == '"') {
					prev = getcharlog();
					c = getcharlog();
				} else if (c == EOF || c == '\n') {
					return 1;
				}
			} while (c != '"');
		} else if (c == '\'') {
			// if c is ''' when next is '\\' skip two, else skip one
			// if the next is not ''' return error
			if ((c = getcharlog()) == '\\') {
				getcharlog();
			}
			if ((c = getcharlog()) != '\'') {
				printf("%i:%i: error: unmatched \"'\"\n", line, col);
				return 1;
			}
		} else if (c == '/') {
			// possible comment
			if ((c = getcharlog()) == '/') { // single line comment
				// skip everything until '\n'
				do {
					c = getcharlog();
				} while (c != '\n');
			} else if (c == '*') { // multiline comment
				// skip everything until eof or */
				do {
					if ((prev = c) == EOF || (c = getcharlog()) == EOF)
					{
						printf("%i:%i: error: unexpected EOF\n", line, col);
						return 1;
					}
				} while (prev != '*' || c != '/');
				prev = getcharlog();
				c = getcharlog();
			}
		} else if (c != target && (c == ')' || c == ']' || c == '}')) {
			printf("%i:%i: error: unmatched %c\n", line, col, target);
			return 1;
		} else if (c == target) {
			return 0;
		} else if (c == '(') {
			// call skip until matching brace
			int l = line, c = col;
			if (skip_until(')') != 0) {
				printf("%i:%i: error: unmatched %c\n", l, c, '(');
				return 1;
			}
		} else if (c == '[') {
			// call skip until matching brace
			int l = line, c = col;
			if (skip_until(']') != 0) {
				printf("%i:%i: error: unmatched %c\n", l, c, '[');
				return 1;
			}
		} else if (c == '{') {
			// call skip until matching brace
			int l = line, c = col;
			if (skip_until('}') != 0) {
				printf("%i:%i: error: unmatched %c\n", l, c, '{');
				return 1;
			}
		}
	}
	if (target == EOF) {
		return 0;
	} else {
		printf("not found %c\n", target);
		return 1;
	}
}

char getcharlog() {
	extern int line;
	extern int col;

	char c = getchar();
	if (c == '\n') {
		++line;
		col = 1;
	} else {
		++col;
	}
	return c;
}
