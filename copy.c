#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * Simple copier
 * usage: ./copy < original_file > copy_file
 */

void copy_stream () {
	int c;
	while ((c = getchar ()) != EOF)
		putchar (c);
}

int main () {
	copy_stream ();
	return 0;
}
