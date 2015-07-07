#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

// sizeof is a unary operator, not a function; it requires parens only when the arg is a type instead of a variable
void test_sizeof_parens () {
	int x = 42;
	printf("sizeof without parens: %lu\n", sizeof x);
} 

void output_one_word_per_line () {
	const int IN = 1, OUT = 0;
	int state = OUT, c;

	while ((c = getchar ()) != EOF) 
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state != OUT)
				putchar ('\n');
			state = OUT;
		} 
		else if (state == OUT) {
			state = IN;
			putchar (c);
		} 
		else if (state == IN)
			putchar (c);
}

void count_digits_whitespace_others () {
	int nw, nc, c;
	nw = nc = 0;
	int digits[] = {0,0,0,0,0,0,0,0,0,0};

	while ((c = getchar ()) != EOF) {
		if (c >= '0' && c <= '9')
			digits[c-'0']++;
		else if (c == ' ' || c == '\t' || c == '\n')
			nw++;
		else 
			nc++;
	}

	for (int i = 0; i < 10; i++)
		printf ("%d:%d ", i, digits[i]);
	printf ("\nwhitespaces = %d, other characters = %d\n", nw, nc);
}

char * get_asterisks (int n) {
	char * asterisks = malloc ((n + 1) * sizeof (char));
	int i = n;

	while (--i >= 0)
		asterisks[i] = '*';
	
	asterisks[n] = '\0';
	return asterisks;
}

void histogram_wordlengths () {
	int n = 20;
	int norm = 50; 	// a large text will have several words, so divide histogram lengths by this factor. set to 1 if text is small. log may be used as well
	int * wlens = malloc (n * sizeof (int));
	const int IN = 1, OUT = 0;
	int state = OUT, c, wlen = 0;

	while ((c = getchar ()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN && wlen > 0 && wlen <= n) {
				wlens[wlen-1]++;
				wlen = 0;
			}
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			wlen = 1;
		} 
		else if (state == IN) 
			wlen++;
	}
	if (wlen > 0)
		wlens[wlen-1]++;

	for (int i = 0; i < n; i++) {
		if (wlens[i] > 0) {
			char * s = get_asterisks (wlens[i] / norm);
			printf("%3d: %s\n", i+1, s);
			free (s);
		}
	}
	free (wlens);
}

void histogram_chars () {
	int n = 26, c;
	int norm = 1; 	// a large text will have several chars, so divide histogram lengths by this factor. set to 1 if text is small. 
	int * characters = malloc (n * sizeof (int));

	while ((c = getchar ()) != EOF) {
		if (c >= 'a' && c <= 'z')
			characters[c-'a']++;
		else if (c >= 'A' && c <= 'Z')
			characters[c-'A']++;
	}

	for (int i = 0; i < n; i++) {
		char * s = get_asterisks (characters[i] / norm);
		printf("%3c: %s\n", 'a' + i, s);
		free (s);
	}
	free (characters);	
}

// O(lg n) + O(n/2) power function for x ^ n; better constants than trivial O(n)
int power (int base, int exponent) {
	if (base <= 1)
		return base;

	int product = base;
	int i = 1;
	while ((i<<=1) <= exponent)
		product *= product;

	i >>= 1;
	i = exponent - i;
	while (i-- > 0) 
		product *= base;

	return product;
}

void power_test (int base, int lower, int upper) {
	if (lower > upper)
		return;

	for (int i = lower; i < upper; i++)
		printf("%d ^ %d = %d \n", base, i, power (base, i));
}

/** 
 * generic tests: ./scratch < infile > outfile
 */
void run_tests () {
	// test_sizeof_parens ();
	output_one_word_per_line ();
	// count_digits_whitespace_others ();
	// histogram_wordlengths ();
	// histogram_chars ();
	// power_test (3, 2, 20);
}

int main () {
	run_tests ();

	return 0;
}
