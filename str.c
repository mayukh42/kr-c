#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define MAXSIZE 32

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
	}
	else {
		for (unsigned i = 0; i < strlen (cs); i++) {
			buf[last] = cs[i];
			char * rest = remove_at (cs, i);
			permute (rest, buf, last + 1);
			free (rest);
		}
	}
}

void test_permute () {
	char * buf = (char *) malloc (sizeof (char) * MAXSIZE);
	char cs[] = "abc";
	permute (cs, buf, 0);
	free (buf);
}

void run_tests () {
	// test_remove_at ();
	test_permute ();
}

int main () {
	run_tests ();

	return 0;
}
