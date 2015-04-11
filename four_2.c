#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

const int MAXSIZE = 1024;
const int MAXWIDTH = 16;

typedef struct Stack {
	double * arr;
	int index;
} Stack;

/** push () and pop () for the stack
 * push () shifts the index to one after the top
 * pop () must take into account this off by one index
 */

void push (Stack * stack, double number) {
	if (stack->index < MAXSIZE)
		stack->arr[stack->index++] = number;
}

double pop (Stack * stack) {
	if (stack->index > 0)
		return stack->arr[--stack->index];
	else
		return 0.0;
}

// helper function to debug the stack
void print_stack (Stack * stack) {
	int idx = stack->index;
	while (idx >= 0) {
		printf ("%d:%f\n", idx, stack->arr[idx]);
		idx--;
	}
}

/** Polish Calculator == Postfix Expression Evaluator 
 * Supports double/ negative numbers. Stateful
 * Operators: +, -, *, /, %
 * TODO:
 	Handle errors correctly
 */

void polish_calc (const char * expr) {
	const int NUM = 1, OUT = 0, NEG = -1;
	int state = OUT, i = 0, j = 0;
	char * num_str = malloc (MAXWIDTH * sizeof (char));

	Stack * stack = malloc (sizeof (Stack));
	stack->arr = malloc (MAXSIZE * sizeof (double));
	stack->index = 0;

	while (expr[i] != '\0') {
		if (state == OUT && expr[i] >= '0' && expr[i] <= '9') {
			state = NUM;
			num_str[j++] = expr[i];
		}
		else if (state == NUM && expr[i] >= '0' && expr[i] <= '9')
			num_str[j++] = expr[i];
		else if (state == NUM && expr[i] == '.')
			num_str[j++] = expr[i];
		else if (state == NUM && (expr[i] == ' ' || expr[i] == '\t')) {
			num_str[j] = '\0';			
			double num = atof (num_str);
			push (stack, num);
			state = OUT;
			j = 0;
		}
		else if (state == OUT && expr[i] == '+')
			push (stack, pop (stack) + pop (stack));
		else if (state == OUT && expr[i] == '-') 
			state = NEG;
		else if (state == NEG && expr[i] >= '0' && expr[i] <= '9') {
			state = NUM;
			num_str[j++] = '-';
			num_str[j++] = expr[i];
		}
		else if (state == NEG) {
			double num2 = pop (stack);
			double num1 = pop (stack);
			push (stack, num1 - num2);
			state = OUT;
		}
		else if (state == OUT && expr[i] == '*')
			push (stack, pop (stack) * pop (stack));
		else if (state == OUT && expr[i] == '/') {
			double num2 = pop (stack);
			double num1 = pop (stack);
			push (stack, num1 / num2);
		}
		else if (state == OUT && expr[i] == '%') {
			int num2 = (int) pop (stack);
			int num1 = (int) pop (stack);
			push (stack, (double) (num1 % num2));
		}
		else if (state == OUT && (expr[i] == ' ' || expr[i] == '\t'))
			;
		else {
			printf ("%s is not a valid expression\n", expr);
			break;
		}
		i++;
	}

	// the corner case when '-' is the last operand in expression
	if (state == NEG) {
		double num2 = pop (stack);
		double num1 = pop (stack);
		push (stack, num1 - num2);
		state = OUT;
	}

	double res = pop (stack);
	printf ("%s = %.3f\n", expr, res);

	free (num_str);
	free (stack->arr);
	free (stack);
}

void run_tests () {
	unsigned num_exprs = 8;
	char * exprs[] = {
		"1 2 -", 
		"1 2 - 4 5 + *", 
		"62.0 8.0 /", 
		"100 8 %", 
		"10 -4 /", 
		"11 -3 -",
		"-11 5 %",
		"-11 -3 -"
	};

	for (unsigned i = 0; i < num_exprs; i++)
		polish_calc (exprs[i]);
}

int main () {
	run_tests ();

	return 0;
}
