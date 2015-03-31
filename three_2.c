#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int BUFFER_SIZE = 128;
char * hexs_lower = "0123456789abcdef";

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

// required by itob ()
char int_to_hex (int i) {
	if (i >= 0 && i < 16)
		return hexs_lower[i];
	return '\0';
}

/** int to base b to string
 * handles -ves naively
 * assumes highest base = 16
 * TODO
 	check if sign bit is required by the problem
 */

void itob (int n, char * s, int b) {
	if (b < 2 || b > 16)
		return;

	int i = 0, sign = n >= 0;

	if (n == 0)
		s[i++] = '0';

	if (n < 0)
		n = -n;

	while (n > 0) {
		int q = n / b;
		int r = int_to_hex (n % b);	// the hex group includes those of lower bases
		s[i++] = r;
		n = q;
	}

	if (! sign) 
		s[i++] = '-';

	for (int j = 0; j < i/2; j++) {
		char tmp = s[j];
		s[j] = s[i-j-1];
		s[i-j-1] = tmp;
	}
	s[i] = '\0';
}

void run_itob_tests () {
	int xs[] = {42, -42, 625, -625, -1024, 1000000, 0, 917};
	int bases[] = {2, 8, 10, 16};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			char * str = malloc (BUFFER_SIZE * sizeof (char));
			itob (xs[j], str, bases[i]);

			printf ("%d in base %d => %s\n", xs[j], bases[i], str);
			free (str);
		}
	}
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
	// run_expand_tests ();
	run_itob_tests ();
}

int main () {
	run_tests ();

	return 0;
}
