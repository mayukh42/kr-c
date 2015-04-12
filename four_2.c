#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double top (Stack * stack) {
	if (stack->index > 0)
		return stack->arr[stack->index - 1];
	else 
		return 0.0;
}

void swap_toptwo (Stack * stack) {
	if (stack->index > 1) {
		double tmp = stack->arr[stack->index - 1];
		stack->arr[stack->index - 1] = stack->arr[stack->index - 2];
		stack->arr[stack->index - 2] = tmp;
	}
}

void clear (Stack * stack) {
	stack->index = 0;
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
 * Operators: +, -, *, /, %, 
 	s/ c/ t = sin/ cos/ tan (unary)
 	^ = pow (binary)
 	e = exp (constant)
 		e is to be used as a symbol. e4 or 4e is not valid. Hence e has a state
 * TODO:
 	Handle errors
 	Use identifiers like sin, cos, tan, etc.
 */

void polish_calc (const char * expr) {
	const int NUM = 1, OUT = 0, NEG = -1, SIN = 2, COS = 3, TAN = 4, EXP = 5;
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
			push (stack, pop (stack) - num2);
			state = OUT;
		}
		else if (state == OUT && expr[i] == '*')
			push (stack, pop (stack) * pop (stack));

		else if (state == OUT && expr[i] == '/') {
			double num2 = pop (stack);
			push (stack, pop (stack) / num2);
		}
		else if (state == OUT && expr[i] == '%') {
			int num2 = (int) pop (stack);
			int num1 = (int) pop (stack);
			push (stack, (double) (num1 % num2));
		}
		else if (state == OUT && expr[i] == '^') {
			double num2 = pop (stack);
			double num1 = pop (stack);
			if (num2 < 0)
				push (stack, 1.0 / pow (num1, -num2));
			else
				push (stack, pow (num1, num2));
		}
		// sin
		else if (state == OUT && (expr[i] == 's' || expr[i] == 'S'))
			state = SIN;
		else if (state == SIN && expr[i] >= '0' && expr[i] <= '9') {
			num_str[j++] = expr[i];
		}
		else if (state == SIN && (expr[i] == ' ' || expr[i] == '\t')) {
			num_str[j] = '\0';
			double num = atof (num_str);
			j = 0;
			state = OUT;
			push (stack, sin (num));
		}
		// cos
		else if (state == OUT && (expr[i] == 'c' || expr[i] == 'C'))
			state = COS;
		else if (state == COS && expr[i] >= '0' && expr[i] <= '9') {
			num_str[j++] = expr[i];
		}
		else if (state == COS && (expr[i] == ' ' || expr[i] == '\t')) {
			num_str[j] = '\0';
			double num = atof (num_str);
			j = 0;
			state = OUT;
			push (stack, cos (num));
		}
		// tan
		else if (state == OUT && (expr[i] == 't' || expr[i] == 'T'))
			state = TAN;
		else if (state == TAN && expr[i] >= '0' && expr[i] <= '9') {
			num_str[j++] = expr[i];
		}
		else if (state == TAN && (expr[i] == ' ' || expr[i] == '\t')) {
			num_str[j] = '\0';
			double num = atof (num_str);
			j = 0;
			state = OUT;
			push (stack, tan (num));
		}
		// e
		else if (state == OUT && expr[i] == 'e')
			state = EXP;
		else if (state == EXP && (expr[i] == ' ' || expr[i] == '\t')) {
			state = OUT;
			push (stack, exp (1));
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
		push (stack, pop (stack) - num2);
		state = OUT;
	}

	double res = pop (stack);
	printf ("%s = %.3f\n", expr, res);

	free (num_str);
	free (stack->arr);
	free (stack);
}

void run_tests () {
	char * exprs[] = {
		"1 2 -", 
		"1 2 - 4 5 + *", 
		"62.0 8.0 /", 
		"100 8 %", 
		"10 -4 /", 
		"11 -3 -",
		"-11 5 %",
		"-11 -3 -",
		"12 2 ^",
		"3 -1 ^",
		"s10 s8 +",
		"c10 c8 -",
		"t10 t8 *",
		"e 4 *",
		"s10 s8 + e 4 * /",
		"3 -1 ^ t10 t8 * +"
	};
	unsigned num_exprs = 16;

	for (unsigned i = 0; i < num_exprs; i++)
		polish_calc (exprs[i]);
}

int main () {
	run_tests ();

	return 0;
}
