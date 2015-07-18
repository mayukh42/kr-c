#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Some random problems
 * and examples
 */

#define MAXSIZE 31

typedef struct Point {
	int x;
	int y;
} Point;


/** 2D Matrix Utility functions
 */
int ** build_mat (int ** xs, int * elems, int r, int c) {
	xs = (int **) malloc (sizeof (int *) * r);
	for (int i = 0; i < r; i++) {
		int * cs = (int *) malloc (sizeof (int) * c);
		for (int j = i*c; j < (i+1)*c; j++)
			cs[j%c] = elems[j];
		xs[i] = cs;
	}
	return xs;
} 

void delete_mat (int ** xs, int r) {
	for (int i = 0; i < r; i++)
		free (xs[i]);
	free (xs);
}

/** 1 - spiral printing of matrix
 * ex. [1 2 3
 		4 5 6
 		7 8 9]
 * should be [1 2 3 6 9 8 7 4 5]
 * Game programming: Moving the turtle
 */
void spiral_print_mat (int ** xs, int r, int c) {
	int n = r * c;	

	int nwx = 0, nwy = 0, nex = 0, ney = c - 1,
		sex = r - 1, sey = c - 1, swx = r - 1, swy = 0;

	printf ("[");
	while (1) {
		for (int j = nwy; j <= ney; j++) {
			printf ("%d ", xs[nwx][j]);
			n--;
		}
		if (n == 0)	break;
		nwx++;
		nex++;

		for (int i = nex; i <= sex; i++) {
			printf ("%d ", xs[i][ney]);
			n--;
		}
		if (n == 0)	break;
		ney--;
		sey--;

		for (int j = sey; j >= swy; j--) {
			printf ("%d ", xs[sex][j]);
			n--;
		}
		if (n == 0)	break;
		sex--;
		swx--;	

		for (int i = swx; i >= nwx; i--) {
			printf ("%d ", xs[i][swy]);
			n--;
		}
		if (n == 0)	break;
		nwy++;
		swy++;
	}
	printf ("]\n");
}

void test_spiral_print_mat () {
	int r = 3, c = 4;
	int elems[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int ** xs = NULL;
	xs = build_mat (xs, elems, r, c);

	spiral_print_mat (xs, r, c);
	delete_mat (xs, r);	
}

/** add_ut ()
 * add elements in the upper triangular part
 * of a square matrix
 */
int add_ut (int ** xs, int r) {
	int sum = 0, dl = 0, dh = 0;
	int n = r * (r + 1) / 2;

	while (n > 0) {
		printf ("[");
		for (int i = dl; i >= 0; i--) {
			printf ("%d ", xs[i][dh - i]);
			sum += xs[i][dh - i];
			n--;
		}
		printf ("]\n");
		dl++;
		dh++;
	}
	return sum;
}

void test_add_ut () {
	int r = 3;
	int elems[] = {1,2,3,4,5,6,7,8,9};
	int ** xs = NULL; 
	xs = build_mat (xs, elems, r, r);

	printf ("sum of upper triangle is %d\n", add_ut (xs, r));
	delete_mat (xs, r);
}

void print_arr (int * xs, int size) {
	printf ("[");
	for (int i = 0; i < size; i++)
		printf ("%d, ", xs[i]);
	printf ("]\n"); 
} 

unsigned long hash_str (char * cs) {
	unsigned long h = 0;
	for (unsigned i = 0; i < strlen (cs); i++)
		h += 31 * h + cs[i];
	return h;
}

void print_str_array (char ** cs, int size) {
	printf ("[");
	for (int i = 0; i < size; i++)
		printf ("%s, ", cs[i]);
	printf ("]\n");
}

/** str_array_diff ()
 * difference between 2 arrays, the 2nd of which contain 
 * one element that is not in 1st
 */
void str_array_diff (char ** first, char ** second, int size) {
	int * xs = (int *) malloc (sizeof (int) * MAXSIZE);
	for (int i = 0; i < size; i++) {
		unsigned long h = hash_str (first[i]);
		xs[h % MAXSIZE]++;
	}
	// print_arr (xs, MAXSIZE);
	printf ("[");
	for (int i = 0; i < size + 1; i++) {
		unsigned long h = hash_str (second[i]);
		if (! xs[h % MAXSIZE])
			printf ("%s, ", second[i]);
	}
	printf ("]\n");
	free (xs);
}

void test_str_array_diff () {
	char * first[] = {"dog", "cat", "monkey"};
	char * second[] = {"dog", "cat", "rat", "monkey"};
	int size = 3;
	// print_str_array (first, size);
	// print_str_array (second, size + 1);

	str_array_diff (first, second, size);
}

/** gcd ()
 * find the gcd of 2 numbers
 */
unsigned gcd (unsigned m, unsigned n) {
	if (m > n)
		return gcd (m-n, n);
	else if (m < n)
		return gcd (m, n-m);
	else
		return m;
}

/** double2rational ()
 * convert a double number to rational fraction
 */
void double2rational (double n) {
	double whole = floor (n);
	double decimal = n - whole;
	if (decimal == 0.0)
		decimal = 1.0;
	double base = 10.0, multiplier = 1.0, tolerance = 0.0001;

	while (decimal - floor (decimal) >= tolerance) {
		decimal *= base;
		multiplier *= base;
	}	

	unsigned factor = gcd ((unsigned) decimal, (unsigned) multiplier);
	decimal /= (double) factor;
	multiplier /= (double) factor;

	printf ("rational fraction of %.8f = %ld %ld/%ld\n", 
		n, (long) whole, (long) decimal, (long) multiplier);
}

void test_gcm_double2rational () {
	int m = 6, n = 9;
	printf ("gcd of %d and %d = %d\n", m, n, gcd (m, n));

	double2rational (1234.5678);
	double2rational (0.5223);
	double2rational (1.125);
	double2rational (6.116);	// not quite the ouput we want
	double2rational (42.0);
}

void run_tests () {
	// test_spiral_print_mat ();
	// test_add_ut ();
	// test_str_array_diff ();
	test_gcm_double2rational ();
}

int main () {
	run_tests ();

	return 0;
}
