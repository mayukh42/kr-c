#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int STRSIZE = 128;
const int ARRAYSIZE = 8;

void squeeze (char * s, char c) {
	int j = 0;
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

// without pointers
void concat_naive (char s[], char t[]) {
	int i = 0, j = 0;
	while (s[i++] != '\0')
		;
	i--;	// i is incremented after getting the null char's index
	while ((s[i++] = t[j++]) != '\0')	// s[i] is compared to '\0', hence '\0' is already assigned to s[i] when the loop exits
		;
}

int find_char (char * s, char c) {
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return i;
	return -1;
}

void squeeze_alternate (char * s1, char * s2) {
	int i = 0, j = 0;
	while (s1[i] != '\0') {
		if (find_char (s2, s1[i]) == -1)
			s1[j++] = s1[i];
		i++;
	}
	s1[j] = '\0';
}

int any (char * s1, char * s2) {
	int j = -1;
	for (int i = 0; s1[i] != '\0'; i++) {
		j = find_char (s2, s1[i]);
		if (j != -1)
			return i;
	}
	return j;
}

char * reverse_str (char * str, int size) {
	char * res = malloc ((size + 1) * sizeof (char));
	for (int i = size-1; i >= 0; i--) 
		res[i] = str[size-1-i];
	res[size] = '\0';
	return res;
}

char * to_bit_string (int n) {
	char * bits = malloc (33 * sizeof (char));
	int i = 0;
	if (! n)
		bits[i++] = '0';

	while (n > 0) {
		int q = n >> 1;
		int r = n & 1;
		bits[i++] = r ? '1' : '0';
		n = q;
	}
	bits[i] = '\0';
	char * bit_str = reverse_str (bits, i);
	free (bits);
	return bit_str;
}

/** return n bits of x starting from p, where 0 is the right-most index
 * assume p >= n
 */

unsigned getbits (unsigned x, unsigned p, unsigned n) {
	if (! n)			// nothing to do
		return x;
	x = x >> (p+1 - n);	// right-align n bits starting from original index p in x
	x = x & ~(~0 << n);	// ~0 << n = all 1's except last n bits = 0. complimenting that gives all 0's except last n bits = 1
	return x;
}

unsigned setbits (unsigned x, unsigned p, unsigned n, unsigned y) {
	if (! n)
		return x;
	y = y & ~(~0 << n);	// ~0 << n: 1...10..0 (last n bits = 0). So, and-ing its compliment with y gives last n bits of y, and everything else = 0
	y = y << (p+1 - n);	// move the last n bits of y into position
	return x | y;
}

unsigned invertbits (unsigned x, unsigned p, unsigned n) {
	if (! n)
		return x;
	unsigned mask = ~(~0 << (p+1));		// 0..01..1
	mask = mask & (~0 << (p+1 - n));	// 1..10..0
	return x ^ mask;					// x ^ 0..01..10..0, such that there are n 1's in the middle. 0 is the identity for XOR, and 1 inverts the bits
}

/** Right & Left rotation of bits
 * For any length of bit string (of unsigned type). 
 * to_bit_string () ignores the leftmost '0' bits
 */

unsigned rightrot (unsigned x, unsigned n) {
	char * bits = to_bit_string (x);	
	unsigned p = strlen (bits);
	
	unsigned xr = x & ~(~0 << n);
	xr = xr << (p - n);
	x = x >> n;
	
	free (bits);
	return xr | x;
}

unsigned leftrot (unsigned x, unsigned n) {
	char * bits = to_bit_string (x);	
	unsigned p = strlen (bits);
	
	unsigned xl = x >> (p - n);
	x = x & ~(~0 << (p - n));
	x = x << n;
	
	free (bits);
	return x | xl;
}

<<<<<<< HEAD
/** Right Rotation of string
 * ("cisco", 2) = "cocis"
 * For left rotation, pass a negative shift
 * ("cisco", -2) = "scoci"
 */

void rightrot_str (char * s, int shift) {
	int i = 0, p = strlen (s);
	if (shift < 0)			// handle left rotation
		shift += p;			// note that shift is negative, so added to p instead of subtraction
	char * buf = malloc (p * sizeof (char));

	while (s[i] != '\0' && i != p) {
		buf[(i+shift) % p] = s[i];
		i++;
	}
	i = 0;
	while (i != p) {
		s[i] = buf[i];
		i++;
	}

	free (buf);
}

=======
>>>>>>> c1208391dcf84f781e365fdf100d32f4f0ae2feb
void run_bit_tests () {
	int xs[] = {42, 28, 10, 16, 356, 255, 31, 1000};

	for (int i = 0; i < ARRAYSIZE; i++) {
		char * bits1 = to_bit_string (xs[i]);

		// leftrot		
		char * bits2 = to_bit_string (leftrot (xs[i], 3));

		// rightrot
		// char * bits2 = to_bit_string (rightrot (xs[i], 3));

		// invertbits
		// char * bits2 = to_bit_string (invertbits (xs[i], 3, 3));

		// setbits
		// char * bits2 = to_bit_string (setbits (xs[i], 3, 3, 15));

		// getbits
		// char * bits2 = to_bit_string (getbits (xs[i], 3, 3));
		
		printf ("%d in bits = %s, after modification = %s\n", xs[i], bits1, bits2);
		
		free (bits1);
		free (bits2);
	}
}

void run_char_tests () {
	char ds[] = "cisco";
	// char * vowels = "aeiou";

	// char cs[STRSIZE]; 
	// int i;
	// for (i = 0; ds[i] != '\0'; i++)
	// 	cs[i] = ds[i];
	// cs[i] = '\0';

	// printf ("before: %s, %s\n", cs, ds);
	// concat_naive (cs, ds);
	// printf ("after: %s, %s\n", cs, ds);

	// squeeze (ds, 'h');	// char * cs would give SIGSEGV, since rhs is a string literal which wont be copied over in that case, resulting in read-only array
	// printf ("squeezed %s\n", ds);

	// squeeze_alternate (ds, vowels);
	// printf ("squeezed %s\n", ds);

	// int first_occurrence = any (ds, vowels);
	// printf ("a char from %s was found in %s at %d\n", vowels, ds, first_occurrence);

	rightrot_str (ds, -2);
	printf ("%s\n", ds);
}

void run_tests () {
<<<<<<< HEAD
	run_char_tests ();
	// run_bit_tests ();
=======
	// run_char_tests ();
	run_bit_tests ();
>>>>>>> c1208391dcf84f781e365fdf100d32f4f0ae2feb
}

int main () {
	run_tests ();

	return 0;
}
