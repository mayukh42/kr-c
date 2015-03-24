#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

// #define DEBUG 1

const int TABSIZE = 4;
const int MAXSIZE = 1024;

void detab (int n) {
	int c;

	while ((c = getchar ()) != EOF) {
		if (c == '\t')
			for (int i = 0; i < n; i++)
				putchar (' ');
		else
			putchar (c);
	}
}

/** Ex. 1.21 rephrased: 
 * Write a program that takes as input text with spaces and produces as output visually equivalent text using tabs to the maximum extent possible.
 * So if |spaces| = n, n > TABSIZE, replace with n / TABSIZE tabs and n % TABSIZE spaces
 * if there are spaces + tabs, reduce it to the above expression by convertig TABS to spaces
 * Test: A well-intended source code should not change.
 */

void entab (int n) {
	const int IN = 1, OUT = 0;
	int c, spaces = 0, state = OUT;

	while ((c = getchar ()) != EOF) {
		if (c == ' ') {
			state = OUT;
			spaces++;
		}
		else if (c == '\t') {
			state = OUT;
			spaces += n;
		}
		else if (state == OUT) {
			state = IN;

			int insert_tabs = spaces / n;
			int insert_spaces = spaces % n;
			
			for (int i = 0; i < insert_tabs; i++)
				putchar ('\t');
			
			for (int i = 0; i < insert_spaces; i++)
				putchar (' ');
			
			spaces = 0;
			putchar (c);
		}
		else if (state == IN)
			putchar (c);
	}
}

// stateful
void fold_lines (int limit, int tabsize) {
	const int IN = 1, OUT = 0;
	int c, col = 0, word_length = 0, state = OUT;

	char * word_buffer = malloc (limit * sizeof (char));

	while ((c = getchar ()) != EOF) {
		if (c == ' ' || c == '\t') {
			state = OUT;
			if (col + word_length > limit) {
				putchar ('\n');
				col = 0;
			}
			for (int i = 0; i < word_length; i++)
				putchar (word_buffer[i]);
			col += word_length;
			word_length = 0;

			int width = (c == ' ') ? 1 : tabsize;
			if (col + width > limit) {
				for (int i = 0; i < width; i++)
					word_buffer[word_length++] = ' ';
			}
			else {
				putchar (c);
				col += width;
			}
		}
		else if (state == OUT) {
			state = IN;
			word_buffer[word_length++] = c;
		} 
		else if (state == IN) {
			// TODO: extreme case: word length > limit
			word_buffer[word_length++] = c;
		}
	}

	if (col + word_length > limit)
		putchar ('\n');

	for (int i = 0; i < word_length; i++)
		putchar (word_buffer[i]);

	free (word_buffer);
}

void uncomment_cpp () {
	const int OUT = 0, LINE = 1, MULTILINE = 2, START = 3, END = 4;
	int c, state = OUT;
	char buf = '\0';

	while ((c = getchar ()) != EOF) {
		if (state == OUT && c == '/') {
			state = START;
			buf = c;
		}
		else if (state == START && c == '*')
			state = MULTILINE;
		else if (state == START && c == '/')
			state = LINE;
		else if (state == START) {
			state = OUT;
			putchar (buf);
			buf = '\0';
			putchar (c);
		}
		else if (state == MULTILINE && c == '*')
			state = END;
		else if (state == END && c == '/')
			state = OUT;
		else if (state == END)
			state = MULTILINE;
		else if (state == LINE && c == '\n') {
			state = OUT;
			putchar (c);
		}
		else if (state == OUT)
			putchar (c);
	}
}

int char_exists (char c, char * s, int n) {
	int i = 0;
	while (i++ < n) {
		if (s[i] == c)
			return i;
	}
	return -1;
}

/** check rudimentary errors in c program
 * this can be a part of lexer at best. does not check semantics
 * DONE: 
 	first, second, third bracket matching, 
 	quotes matching
 	escape characters
 	comments
 */

typedef enum State {
	ESCAPE, QUOTE, COMMENT_START, COMMENT, COMMENT_END, OUT
} State;

int rudimentary_errors () {
	// const int ESCAPE = 6, QUOTE = 7, OUT = 8, COMMENT_START = 9, COMMENT = 10, COMMENT_END = 11;
	int c, index = 0;
	State state = OUT;
	char * parens = "(){}[]";
	char * sp_chars = "ntr";
	int num_sp_chars = 3;
	const char SINGLE_QUOTE = '\'';
	const char DOUBLE_QUOTE = '"';
	char * buf = malloc (MAXSIZE * sizeof (char));

	while ((c = getchar ()) != EOF) {
		if (index > MAXSIZE)
			return 0;

		switch (state) {
			case OUT:
				if (c == parens[0] || c == parens[2] || c == parens[4])
					buf[index++] = c;
				else if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE) {
					buf[index++] = c;
					state = QUOTE;
				}
				else if (c == '/')
					state = COMMENT_START;
				else if ((c == parens[1] && buf[index-1] == parens[0]) ||
					(c == parens[3] && buf[index-1] == parens[2]) ||
					(c == parens[5] && buf[index-1] == parens[4]))
					index--;
				break;

			case COMMENT_START:
				if (c == '*') {
					buf[index++] = '/';
					buf[index++] = '*';
					state = COMMENT;
				}
				else 
					state = OUT;
				break;

			case COMMENT:
				if (c == '*')
					state = COMMENT_END;
				break;

			case COMMENT_END:
				if (c == '/') {
					index -= 2;
					state = OUT;
				}
				else 
					state = COMMENT;
				break;

			case QUOTE:
				if (c == '\\')
					state = ESCAPE;	
				else if ((c == SINGLE_QUOTE && buf[index-1] == SINGLE_QUOTE) ||
					(c == DOUBLE_QUOTE && buf[index-1] == DOUBLE_QUOTE)) {
					index--;
					state = OUT;
				}
				break;

			case ESCAPE:
				if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE || char_exists (c, sp_chars, num_sp_chars))
					state = QUOTE;
				break;
		}
	}

#ifdef DEBUG
	buf[index] = '\0';
	printf ("buf = %s\n", buf);
#endif	

	free (buf);

	if (index > 0) 
		return 0;
	else
		return 1;
}

void run_tests () {
	// int tabsize = TABSIZE;

	// detab (tabsize);
	// entab (tabsize);
	// fold_lines (60, tabsize);

	// uncomment_cpp ();

	int err = rudimentary_errors ();
	printf ("the code is %sOK\n", err ? "" : "not ");
}

int main () {
	run_tests ();

	return 0;
}
