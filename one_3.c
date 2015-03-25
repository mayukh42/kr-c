#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int MAXCHARS = 100;

char * get_longest_line () {
	const int IN = 1, OUT = 0;
	int c, i = 0, last = 0, state = OUT;

	char * line_buffer = malloc (MAXCHARS * sizeof (char));
	char * longest_line = malloc (MAXCHARS * sizeof (char));

	while ((c = getchar ()) != EOF) {
		if (c == '\n') {
			state = OUT;			
			if (i > last) {
				last = i;
				memcpy (longest_line, line_buffer, last);
			}
		}
		else if (state == OUT && c != '\n') {
			i = 0;
			state = IN;
			line_buffer[i++] = c;
		}
		else if (state == IN)
			line_buffer[i++] = c;
	}
	if (last < MAXCHARS)
		longest_line[last] = '\0';
	else
		longest_line[MAXCHARS-1] = '\0';

	free (line_buffer);
	return longest_line;
}

void line_longer_than_n_chars (int n) {
	if (n > MAXCHARS-1)
		return;

	const int IN = 1, OUT = 0;
	int c, i = 0, state = OUT;

	char * line_buffer = malloc (MAXCHARS * sizeof (char));
	char * line_longer = malloc (MAXCHARS * sizeof (char));

	while ((c = getchar ()) != EOF) {
		if (c == '\n') {
			state = OUT;
			if (i > n) {
				memcpy (line_longer, line_buffer, i);
				line_longer[i] = '\0';
				printf("%3d: %s\n", i, line_longer);
			}
		}
		else if (state == OUT && c != '\n') {
			state = IN;
			i = 0;
			line_buffer[i++] = c;
		}
		else if (state == IN) 
			line_buffer[i++] = c;
	}
	free (line_buffer);
	free (line_longer);
}

void remove_trailing_whitespaces () {
	int c, i = 0, j = 0;
	char * line_buffer = malloc (MAXCHARS * sizeof (char));

	while ((c = getchar ()) != EOF) {
		if (c == '\n') {
			for (j = i-1; j >= 0; j--) {
				if (line_buffer[j] != ' ' && line_buffer[j] != '\t')
					break;
			}
			char * line_trimmed = malloc ((j+2) * sizeof (char));
			memcpy (line_trimmed, line_buffer, j+1);
			line_trimmed[j+1] = '\0';
			i = 0;

			printf("%s\n", line_trimmed);
			free (line_trimmed);
		}
		else 
			line_buffer[i++] = c;
	}

	free (line_buffer);
}

char * reverse_string (char * s, int i) {
	char * rev_s = malloc ((i+1) * sizeof (char));	
	for (int j = 0; j < i; j++)
		rev_s[j] = s[i-1-j];
	rev_s[i] = '\0';

	return rev_s;
}

void reverse_input_lines () {
	int c, i = 0;
	char * line_buffer = malloc (MAXCHARS * sizeof (char));

	while ((c = getchar ()) != EOF)
		if (c == '\n') {
			char * rev_line = reverse_string (line_buffer, i);
			printf("%s\n", rev_line);
			i = 0;
			free (rev_line);
		}
		else
			line_buffer[i++] = c;
	free (line_buffer);
}

void run_tests () {
	// char * longest_line;
	// longest_line = get_longest_line ();
	// printf("longest line: \n%s \n", longest_line);
	// free (longest_line);

	// line_longer_than_n_chars (60);

	// remove_trailing_whitespaces ();

	// char * s = reverse_string ("Hello", 5);
	// printf("%s\n", s);
	// free (s);

	reverse_input_lines ();
}

int main () {
	run_tests ();

	return 0;
}
