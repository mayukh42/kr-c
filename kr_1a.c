#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

typedef double (* temp_conv) (double t);

double convert_f_to_c (double f) {
	return (f - 32) / 1.8;
}

double convert_c_to_f (double c) {
	return 1.8 * c + 32;
}

void random_escape_chars () {
	printf ("Hello, World! Here are some random escapes: \n");
	printf ("\\c \\s \n \t \b \\w are unknown sequences \n");
}

void print_temperatures (temp_conv fn, int lower, int upper, int step) {
	while (lower < upper) {
		printf("\t %3.1f\t %3.1f\n", lower * 1.0, fn (lower));
		lower += step;
	}
}

void print_temperatures_reverse_order (temp_conv fn, int lower, int upper, int step) {
	for (int t = upper - step; t >= lower; t = t - step)
		printf("\t %3.1f\t %3.1f\n", t * 1.0, fn (t));
}

// Enter (Return) closes (and flushes) the stream. But Enter is not EOF. Hence after typing one line and hitting Enter, we get the prompt back
void copy_input_to_output () {
	int c;
	while ((c = getchar ()) != EOF)
		putchar (c);
}

// Ctrl+D = EOF in Linux
void show_EOF () {
	int c;
	c = getchar ();
	if (c == EOF)
		printf("EOF value is %d\n", c);
}

// Return is a character, hence will be counted
size_t count_input_chars () {
	size_t nc;
	int c;
	for (nc = 0; (c = getchar ()) != EOF; ++nc)
		putchar (c);
	return nc;
}

size_t count_input_lines () {
	size_t nl, nc;
	int c;
	for (nl = nc = 0; (c = getchar ()) != EOF; ++nc) {
		putchar (c);
		if (c == '\n')
			nl++;
	}
	return nl;
}

size_t wc_simple () {
	size_t wc, nc, nl;
	int c;
	for (wc = nc = nl = 0; (c = getchar ()) != EOF; ++nc)
		if (c == ' ' || c == '\t')
			wc++;
		else if (c == '\n') {
			wc++;
			nl++;
		}
	printf ("chars = %lu, lines = %lu, words = %lu\n", nc, nl, wc);
	return wc;
}

size_t wc_stateful () {
	size_t wc, nc, nl;
	const int IN = 1, OUT = 0;
	int state = OUT, c;
	
	for (wc = nc = nl = 0; (c = getchar ()) != EOF; ++nc)
		if (c == ' ' || c == '\t')
			state = OUT;
		else if (c == '\n') 
			nl++;
		else if (state == OUT) {
			state = IN;
			wc++;
		}

	printf ("chars = %lu, lines = %lu, words = %lu\n", nc, nl, wc);
	return wc;
}

void run_tests () {
	// random_escape_chars ();

	// printf("\t F\t C\n");
	// print_temperatures (convert_f_to_c, 0, 300, 20);

	// printf("\t C\t F\n");
	// print_temperatures_reverse_order (convert_c_to_f, 0, 300, 20);

	// copy_input_to_output ();
	// show_EOF ();

	// size_t nc = count_input_chars ();
	// printf ("Number of characters = %lu \n", nc);

	// size_t nl = count_input_lines ();
	// printf("Number of lines = %lu\n", nl);

	// wc_simple ();
	// wc_stateful ();	// identical to wc_simple ()
}

int main () {
	run_tests ();

	return 0;
}
