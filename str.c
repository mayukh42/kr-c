#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define MAXSIZE 32

typedef enum Bool {
	false,
	true
} Bool;

char * remove_at (char * cs, unsigned idx) {
	unsigned len = strlen (cs);
	if (idx >= len)
		return cs;

	char * ds = (char *) malloc (sizeof (char) * len);
	for (unsigned i = 0; i < len - 1; i++) {
		if (i >= idx) 
			ds[i] = cs[i+1];
		else
			ds[i] = cs[i];
	}
	ds[len - 1] = '\0';
	return ds;
}

void test_remove_at () {
	char cs[] = "germany";
	unsigned i = 6;
	char * ds = remove_at (cs, i);
	printf ("%s, after removal at %u = %s\n", cs, i, ds);
	free (ds);
}

/** permute ()
 * print all permutations of a given string
 */
void permute (char * cs, char * buf, int last) {
	if (strlen (cs) == 0) {
		buf[last] = '\0';
		printf ("%s\n", buf);
	} else {
		for (unsigned i = 0; i < strlen (cs); i++) {
			buf[last] = cs[i];
			char * rest = remove_at (cs, i);
			permute (rest, buf, last + 1);
			free (rest);
		}
	}
}

/** subsets ()
 * print all subsets of the given string, including the empty string
 */
void subsets (char * cs, char * buf, int last) {
	if (strlen (cs) == 0) {
		buf[last] = '\0';
		printf ("%s\n", buf);
	} else {
		char c = cs[0];
		char * rest = remove_at (cs, 0);
		subsets (rest, buf, last);
		buf[last] = c;
		subsets (rest, buf, last + 1);
		free (rest);
	}
}

void test_combinatorics () {
	char * buf = (char *) malloc (sizeof (char) * MAXSIZE);
	char cs[] = "abc";

	printf ("\npermutations of %s:\n", cs);
	permute (cs, buf, 0);
	
	printf ("\nsubsets of %s:\n", cs);
	subsets (cs, buf, 0);

	free (buf);
}

/** is_equal ()
 * returns true iff 2 strings are equal
 */
Bool is_equal (char * first, char * second) {
	if (first[0] == '\0' && second[0] == '\0')
		return true;
	else 
		return (first[0] == second[0]) &&
			is_equal (first + 1, second + 1);
}

/** is_equal_upto ()
 * returns true if same chars up to the given index
 */
Bool is_equal_upto (char * first, char * second, int n) {
	if (n == 0)
		return first[0] == second[0];
	else 
		return (first[0] == second[0]) &&
			is_equal_upto (first + 1, second + 1, n - 1);
}

void test_basic_utilities () {
	char cs[] = "hello";
	char ds[] = "hello";
	Bool eq = is_equal (cs, ds);
	int idx = 3;
	Bool eq_upto = is_equal_upto (cs, ds, idx);

	printf ("the strings are %sequal\n", eq ? "" : "not ");
	printf ("the strings are %sequal upto index %d\n", eq_upto ? "" : "not ", idx);
}


/** String matching algorithms
 */

/** naive_matcher ()
 * O(n-m+1 . m)
 */
void naive_matcher (char * text, char * pat) {
	unsigned t = strlen (text), p = strlen (pat);
	if (p > t)
		return;

	for (unsigned i = 0; i < t-p+1; i++) {
		if (is_equal_upto (pat, text + i, p - 1))
			printf ("strings match at shift %d\n", i);
	}
}

void test_matchers () {
	char cs[] = "naive string matcher algorithm for strings";
	char ds[] = "string";
	naive_matcher (cs, ds);
}

void run_tests () {
	// test_remove_at ();
	// test_combinatorics ();
	// test_basic_utilities ();
	test_matchers ();
}

int main () {
	run_tests ();

	return 0;
}
