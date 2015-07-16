#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Some random problems
 * and examples
 */

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

void run_tests () {
	// test_spiral_print_mat ();
	test_add_ut ();
}

int main () {
	run_tests ();

	return 0;
}
