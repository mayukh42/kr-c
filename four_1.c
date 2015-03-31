#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int MAXSIZE = 1024;

// helper functions
int find_char (char * s, char c) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == c)
			return i;
	}
	return -1;
}

/** Simple grep: find a string in line, print if found
 * can be coupled with expand () in three_2.c to implement simple regex patterns
 * usage: ./four_1 < textfile
 */

void simple_grep (char * pat) {
	const int IN = 1, OUT = 0;
	int c, state = OUT, found = 0;
	unsigned i = 0, j = 0;
	char * buf = malloc (MAXSIZE * sizeof (char));

	while ((c = getchar ()) != EOF) {
		buf[i++] = c;
		if (state == OUT && c == pat[0]) {
			state = IN;
			j++;
		}
		else if (state == IN && c == pat[j]) {
			j++;
		}
		else if (state == IN && j == strlen (pat)) {
			found = 1;
			state = OUT;
		}
		else if (state == IN) {
			state = OUT;
			j = 0;
		}
		if (c == '\n') {
			if (found) {
				buf[i] = '\0';
				printf ("%s", buf);
				found = 0;
			}
			i = 0;
		}
	}

	free (buf);
}

void run_grep_tests () {
	char * pattern = "ing";
	simple_grep (pattern);
}

void run_tests () {
	run_grep_tests ();
}

int main () {
	run_tests ();

	return 0;
}
