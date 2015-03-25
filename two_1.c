#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define SIZE(type) (char *)(&type + 1) - (char *)(&type)

int addressing_bits (void * one, void * two) {
	// printf ("one @ %p, two @ %p\n", &one, &two);		// warning: %p is for void *, not void **. but runs, and shows different addresses for one, two
	size_t offset = (size_t) &one - (size_t) &two;
	return offset << 3;		// 1 byte = 2^3 bits
}

int hex_to_int (char hex) {
	char * hexs_lower = "0123456789abcdef";
	char * hexs_upper = "0123456789ABCDEF";
	for (int i = 0; i < 16; i++)
		if (hex == hexs_lower[i] || hex == hexs_upper[i])
			return i;
	return -1;
}

char * reverse_str (char * str, int size) {
	char * res = malloc ((size + 1) * sizeof (char));
	for (int i = size-1; i >= 0; i--) 
		res[i] = str[size-1-i];
	res[size] = '\0';
	return res;
}

long htol (char * hexstr, int size) {
	long n = 0, index = 0;
	char * it = reverse_str (hexstr, size);
	while (it[index] != '\0' && it[index] != 'x' && it[index] != 'X') {
		char c = it[index];
		int i = hex_to_int (c);

		if (i == -1) {
			printf ("%s is not a valid hex string\n", hexstr);
			return -1;
		}

		n += i * (1L << (4 * index));
		index++;
	}
	free (it);
	return n;
}

int str_len (char * s) {
	int i = 0;
	while (s[i++] != '\0')
		;
	return i-1;
}

void test_hex () {	
	int num_hex = 8;
	char * hexstr[] = {"0x2a", "64", "D4", "FFFF", "0Xff", "deadbeef", "CAFEBABE", "0ff1ce"};

	for (int i = 0; i < num_hex; i++)
		printf ("%s to long = %ld\n", hexstr[i], htol (hexstr[i], str_len (hexstr[i])));
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
}

int main () {
	run_tests ();

	return 0;
}
