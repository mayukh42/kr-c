#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int MAXSIZE = 1024;


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


/** strindex (s, t) 
 * Returns last index of t in s
 * returns -1 if t does not exist, or if t is longer than s
 * works with t = 1-char string also
 * Stateful
 */

int strindex (char * s, char * t) {
	const int IN = 1, OUT = 0;
	int state = OUT, index = -1;
	unsigned i = 0, j = 0, k = 0;

	if (strlen (t) > strlen (s))
		return index;

	while (s[i] != '\0') {
		if (state == OUT && s[i] == t[j]) {
			state = IN;
			k = i;
			j++;

			// for the special case when t is a single char string
			if (j == strlen (t)) {
				index = k;
				state = OUT;
				j = 0;
			}
		}
		else if (state == IN && s[i] == t[j]) {
			j++;

			if (j == strlen (t)) {
				index = k;
				state = OUT;
				j = 0;
			}
		}
		else if (state == IN) {
			state = OUT;
			j = 0;
		}
		i++;
	}
	return index;
}


// helper type for atof
typedef enum AtoF_State {
	OUT, DECIMAL, EXP, ERROR
} AtoF_State;


/** atof_scientific (s)
 * converts string s to double, including scientific notation (using e or E)
 * stateful
 */

double atof_scientific (char * s) {
	double f = 0.0, place = 0.0;
	AtoF_State state = OUT;
	unsigned sign = 0, i = 0, e_power = 0, e_sign = 0;

	while (s[i] != '\0') {
		switch (state) {
			case OUT:
				if (i == 0 && s[i] == '-')
					sign = 1;
				else if (s[i] >= '0' && s[i] <= '9')
					f = f * 10.0 + (double) (s[i] - 48);
				else if (s[i] == '.') {
					state = DECIMAL;
					place = 0.1;
				}
				else if (s[i] == 'e')
					state = EXP;
				else
					state = ERROR;
				break;

			case DECIMAL:
				if (s[i] >= '0' && s[i] <= '9') {
					f += (double) (s[i] - 48) * place;
					place *= 0.1; 
				}
				else if (s[i] == 'e')
					state = EXP;
				else
					state = ERROR;
				break;

			case EXP:
				if (s[i] == '-')
					e_sign = 1;
				else if (s[i] >= '0' && s[i] <= '9')
					e_power = e_power * 10 + (s[i] - 48);
				else
					state = ERROR;
				break;

			default:
				printf ("%s is invalid\n", s);
				return 0.0;
		}
		i++;
	}

	if (state == EXP) 
		f = f * (e_sign ? pow (0.1, e_power) : pow (10.0, e_power));

	return sign ? -f : f;
}

// all tests
void run_atof_tests () {
	char * decimal_strings[] = {"4.2", "1e4", "-127.93", "10.32e4", "12.25e-4", "1110113115223e-12", "0.0", "12345678.912345e-10"};
	for (int i = 0; i < 8; i++) 
		printf ("%s to double = %f\n", decimal_strings[i], atof_scientific (decimal_strings[i]));
}

void run_index_tests () {
	char * s = "thomas, andrew, anderson, and haviland";
	char * t = "and";

	printf ("%s last occurs in %s at %d\n", t, s, strindex (s, t));
}

void run_grep_tests () {
	char * pattern = "ing";
	simple_grep (pattern);
}

void run_tests () {
	// run_grep_tests ();
	// run_index_tests ();
	run_atof_tests ();
}

int main () {
	run_tests ();

	return 0;
}
