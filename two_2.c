#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int STRSIZE = 128;

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

void run_char_tests () {
	char ds[] = "hello";
	char * vowels = "aeiou";

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

	int first_occurrence = any (ds, vowels);
	printf ("a char from %s was found in %s at %d\n", vowels, ds, first_occurrence);
}

void run_tests () {
	run_char_tests ();
}

int main () {
	run_tests ();

	return 0;
}
