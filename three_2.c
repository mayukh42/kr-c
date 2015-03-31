#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int BUFFER_SIZE = 128;

typedef enum State {
	OUT, IN, FLUSH
} State;

typedef enum Bool {
	false, true
} Bool;

Bool is_digit (char c) {
	return c >= '0' && c <= '9';
}

Bool is_lower (char c) {
	return c >= 'a' && c <= 'z';
}

Bool is_upper (char c) {
	return c >= 'A' && c <= 'Z';
}

/** expand: a regex problem of expanding patterns
 * a-d: abcd
 * 0-4: 01234
 * X-Z: XYZ
 * This is similar to the balanced parenthesis problem, where lower, upper, and digit types form different parens, with lower paren as the lower char
 * Assume proper sequence 
 * TODO: 
 	Throw errors if sequence is wrong
 	ex. a-9, D-A, etc.
 */

void expand (char * s, char * t) {
	char start = '\0', stop = '\0';
	int i = 0, k = 0;

	while (s[i] != '\0') {
		if (is_digit (s[i]) || is_lower (s[i]) || is_upper (s[i])) {
			stop = s[i];
			if (start == '\0')
				t[k++] = stop;
			else {
				for (char c = start + 1; c <= stop; c++)
					t[k++] = c;
				start = '\0';
			}
		}
		else if (s[i] == '-')
			start = stop;
		else 
			t[k++] = s[i];
		i++;
	}
	t[k] = '\0';
}

void run_expand_tests () {	
	char * s = "-a-b-cA-E";
	char * t = malloc (BUFFER_SIZE * sizeof (char));

	expand (s, t);

	printf ("s = %s\n", s);
	printf ("t = %s\n", t);

	free (t);
}

void run_tests () {
	run_expand_tests ();
}

int main () {
	run_tests ();

	return 0;
}
