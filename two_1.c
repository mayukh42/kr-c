#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define SIZE(type) (char *)(&type + 1) - (char *)(&type)

const int HEXSIZE = 16;
char * hexs_lower = "0123456789abcdef";

int addressing_bits (void * one, void * two) {
	// printf ("one @ %p, two @ %p\n", &one, &two);		// warning: %p is for void *, not void **. but runs, and shows different addresses for one, two
	size_t offset = (size_t) &one - (size_t) &two;
	return offset << 3;		// 1 byte = 2^3 bits
}

int hex_to_int (char hex) {
	for (int i = 0; i < 16; i++)
		if (hex == hexs_lower[i])
			return i;
		else if (i > 9 && hex - 'A' + 'a' == hexs_lower[i])
			return i;
	return -1;
}

char int_to_hex (int i) {
	if (i >= 0 && i < 16)
		return hexs_lower[i];
	return '\0';
}

char * reverse_str (char * str, int size) {
	char * res = malloc ((size + 1) * sizeof (char));
	for (int i = size-1; i >= 0; i--) 
		res[i] = str[size-1-i];
	res[size] = '\0';
	return res;
}

int str_len (char * s) {
	int i = 0;
	while (s[i++] != '\0')
		;
	return i-1;
}

long htol (char * hexstr) {
	long n = 0, index = 0;

	while (hexstr[index] != '\0') {
		int hexsym = (hexstr[index] == '0' && index == 0) || ((hexstr[index] == 'x' || hexstr[index] == 'X') && index == 1);
		if (hexsym)
			;
		else {
			int i = hex_to_int (hexstr[index]);

			if (i == -1) {
				printf ("%s is not a valid hex string\n", hexstr);
				return -1;
			}

			n = n * 16 + i;
		}
		index++;
	}
	return n;
}

char * ltoh (long n) {
	char * buf = malloc (HEXSIZE * sizeof (char));
	int index = 0;

	if (n < 0) {
		buf[0] = '\0';
		return buf;
	}

	while (n > 0) {
		int q = n / 16;
		int r = n % 16;
		buf[index++] = int_to_hex (r);
		n = q;
	}
	buf[index++] = 'x';
	buf[index++] = '0';
	char * hexstr = reverse_str (buf, index);

	free (buf);
	return hexstr;
}

int char_to_int (char c) {
	if (c >= '0' && c <= '9')
		return c - 48;
	else 
		printf ("'%c' is not a valid integer\n", c);
	return -1;
}

char int_to_char (int i) {
	if (i >= 0 && i <= 9)
		return '0' + i;
	else 
		printf ("%d is not a valid integer\n", i);
	return '\0';
}

void test_conversions () {
	char * str = "012345";
	for (int i = 0; str[i] != '\0'; i++) {
		int j = char_to_int (str[i]);
		char c = int_to_char (j);
		if (j != -1 && c != '\0')
			printf("'%c' to int = %d; back to char = '%c'\n", str[i], j, c);
	}
}

void test_hex () {	
	int num_hex = 8;
	char * hexinp[] = {"0x2a", "64", "D4", "oxtal", "0Xff", "deadbeef", "CAFEBABE", "0ff1ce"};
	char ** hexout = malloc (num_hex * sizeof (char *));
	long xs[] = {0,0,0,0,0,0,0,0};

	for (int i = 0; i < num_hex; i++) {
		xs[i] = htol (hexinp[i]);
		hexout[i] = ltoh (xs[i]);
		printf ("%s to long = %ld; back to hex = %s\n", hexinp[i], xs[i], hexout[i]);
	}

	for (int i = 0; i < num_hex; i++)
		free (hexout[i]);
	free (hexout);
}

void test_sizes () {	
	printf ("The CPU uses %d-bit addressing\n", addressing_bits (NULL, NULL));

	int x = 42;
	int xs[] = {0,1,1,2,3};
	int * pxs = xs;
	printf ("Sizeof int = %lu\n", SIZE(x));
	printf ("Sizeof int array = %lu\n", SIZE(xs));	// prints 20. note how the macro is translated: this is why int[] requires a fixed size at compile time
	printf ("Sizeof int * = %lu\n", SIZE(pxs));
	printf ("%s\n", reverse_str ("hello", 5));
	printf ("%s length = %d\n", "hello", str_len ("hello"));
}

void run_tests () {
	// test_sizes ();
	test_hex ();
	// test_conversions ();
}

int main () {
	run_tests ();

	return 0;
}
