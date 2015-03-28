#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int ARRAYSIZE = 256;
unsigned long next = 1;

unsigned prg_short_range () {
	next = next * 1103515245 + 12345;
	return (next / 65536) % 255;
}

void print_array (int * xs, int size) {
	printf ("[ ");
	for (int i = 0; i < size; i++)
		printf ("%d ", xs[i]);
	printf ("]\n");
}

// Recursive Binary Search
int binary_search (int * xs, int lower, int upper, int element) {
	if (lower > upper)
		return -1;
	else {
		int mid = lower + (upper - lower) / 2;
		if (element == xs[mid])
			return mid;
		else if (element > xs[mid]) 
			return binary_search (xs, mid + 1, upper, element);		// absence of 'return' throws warning: control reaches end of non-void function
		else 
			return binary_search (xs, lower, mid - 1, element);
	}
}

void escape (char * s, char * t) {
	int i = 0, j = 0;
	while (s[i] != '\0') {
		switch (s[i]) {
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;

			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;

			default:
				t[j++] = s[i];
				break; 		// defensive programming
		}
		i++;
	}
	t[j] = '\0';
}

void escape_rev (char * s, char * t) {
	const int OUT = 0, IN = 1;
	int i = 0, j = 0, state = OUT;
	while (s[i] != '\0') {
		switch (s[i]) {
			case '\\':
				state = IN;
				break;

			case 't':
				if (state == IN) {
					t[j++] = '\t';
					state = OUT;
				}
				else 
					t[j++] = 't';
				break;

			case 'n':
				if (state == IN) {
					t[j++] = '\n';
					state = OUT;
				}
				else 
					t[j++] = 'n';
				break;

			default:
				if (state == IN) {
					t[j++] = '\\';
					t[j++] = s[i];
					state = OUT;
				}
				else 
					t[j++] = s[i];
				break;
		}
		i++;
	}
	t[j] = '\0';
}

void run_escape_tests () {
	char cs[] = "Alice in Wonderland\nBy\tLewis Carroll\n\\ is called backslash";
	char ds[ARRAYSIZE];
	char es[ARRAYSIZE];
	printf ("%s\n", cs);

	escape (cs, ds);
	printf ("%s\n", ds);

	escape_rev (ds, es);
	printf ("%s\n", es);
}

void run_binary_search_tests () {
	int common_diff = 0;
	int * xs = malloc (ARRAYSIZE * sizeof (int));

	for (int i = 0; i < ARRAYSIZE; i++) {
		common_diff += prg_short_range ();
		xs[i] = common_diff;
	}

	int size = ARRAYSIZE;
	// print_array (xs, size);
	int element = 1650;

	// measure time (alternate to $ time ./three_1)
	clock_t start, stop;
	start = clock ();
	int found_index = binary_search (xs, 0, size - 1, element);
	stop = clock ();
	printf ("%d found at index = %d. took %5.2f time units\n", 		// keep units abstract for now. For s, divide by CLOCKS_PER_SEC
		element, found_index, (double)(stop - start));

	free (xs);
}

void run_tests () {
	// run_binary_search_tests ();
	run_escape_tests ();
}

int main () {
	run_tests ();

	return 0;
}
