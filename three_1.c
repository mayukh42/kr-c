#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int ARRAYSIZE = 128;
const int NUM_STRINGS = 10;
unsigned long next = 1;

unsigned prg_short_range () {
	next = next * 1103515245 + 12345;
	return (next / 65536) % 16;
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

/** stoi: alternate atoi
 * at most one sign allowed
 * pseudo-stateful
 */

int stoi (char * s) {
	int n = 0, i = 0, num_signs = 0, negative = 0, error = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i] != '\0') {
		switch (s[i]) {
			case '+':
				num_signs++;
				if (num_signs > 1)
					error++;
				break;

			case '-':
				num_signs++;
				if (num_signs > 1)
					error++;
				negative = 1;
				break;

			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				n = n * 10 + (s[i] - 48);	// ASCII ('0') = 48
				break;

			default:
				error++;	// fail it
				break;
		}
		if (error > 0)
			break;
		i++;
	}
	if (error > 0)
		return -999999;
	else if (negative)
		return -n;
	else 
		return n;
}

// subtly stateful
void itos (int n, char * s) {
	int i = 0, sign = n >= 0, extreme = 0;

	if (n == -n) {
		n = -(n + 1);
		extreme = 1;
	}
	else if (n < 0)
		n = -n;

	while (n > 0) {
		int q = n / 10;
		int r = n % 10;
		s[i++] = extreme ? r+1 + '0' : r + '0';
		extreme = 0;
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

void run_stoi_tests () {
	char * numbers[] = {"233", "fox", "-2147483648", "-576", "+1025", "--102", "++144", "+-233", "  -273", "-27 3"};
	int * xs = malloc (NUM_STRINGS * sizeof (int));
	for (int i = 0; i < NUM_STRINGS; i++) {
		xs[i] = stoi (numbers[i]);
		char * str = malloc (ARRAYSIZE * sizeof (int));
		itos (xs[i], str);

		printf ("%s => %d => %s\n", numbers[i], xs[i], str);
		free (str);
	}
	free (xs);
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
	/* 
	[ 6 20 21 32 43 54 56 67 71 77 90 105 117 129 130 137 138 153 154 168 174 176 191 198 205 211 218 227 237 245 257 266 276 282 285 296 298 303 304 312 324 328 333 348 355 369 374 385 395 397 406 414 426 429 439 445 459 474 483 492 507 522 537 543 557 560 568 581 594 604 618 624 634 638 644 658 670 679 692 706 721 727 728 728 728 739 754 755 763 768 768 773 782 794 797 810 820 831 839 848 850 853 855 868 874 889 899 904 906 912 915 923 932 934 935 949 961 963 971 972 984 986 992 997 998 1004 1019 1026 ]
	*/
	int element = 174;

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
	// run_escape_tests ();
	run_stoi_tests ();
}

int main () {
	run_tests ();

	return 0;
}
