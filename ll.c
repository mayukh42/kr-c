#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * Linked List Problems 
 * Taken from Document #105, Stanford CS Education Library
 * http://cslibrary.stanford.edu/
 */

typedef struct Node {
	int val;
	struct Node * next;
} Node;

/**
 * Utility functions
 */
int length (Node * list) {
	if (list == NULL)
		return 0;
	else 
		return 1 + length (list->next);
}

Node * create_node (int v) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->val = v;
	node->next = NULL;
	return node;
}

Node * add (Node * list, int v) {
	Node * node = create_node (v);
	node->next = list;
	return node;
}

void push (Node ** node, int v) {
	Node * v_node = create_node (v);

	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = * node;
	* node = v_node;
}

void append (Node ** node, int v) {
	Node * v_node = create_node (v);

	if (* node == NULL) {
		* node = v_node;
		return;
	}

	(* node)->next = v_node;
}

Node * create_basic_list (int n) {
	Node * list = NULL;
	for (int i = n; i >= 1; i--) 
		push (&list, i);
	return list;
}

Node * find_last (Node * list) {
	if (list == NULL)
		return list;

	while (list->next != NULL)
		list = list->next;
	return list;
}

Node * create_basic_list_2 (int n) {
	Node * list = NULL;

	for (int i = 1; i <= n; i++) {
		Node * last = find_last (list);
		if (last == NULL) 
			append (&list, i);
		else 
			append (&last, i);
	}
	return list;
}

Node * create_basic_list_3 (int n) {
	Node * list = NULL;
	Node * last = NULL;

	for (int i = 1; i <= n; i++) {
		if (list == NULL) {
			push (&list, i);
			last = list;
		} else {
			push (&(last->next), i);
			last = last->next;
		}
	}
	return list;
}

void print_nodes (Node * list) {
	if (list != NULL) {
		printf ("%d, ", list->val);
		print_nodes (list->next);
	}
}

void print_list (Node * list) {
	printf ("[");
	print_nodes (list);
	printf ("]\n");
}

void delete_list (Node * node) {
	if (node != NULL) {
		delete_list (node->next);
		free (node);
	}
}


void test_utilities () {
	Node * list = create_basic_list_3 (5);
	print_list (list);
	delete_list (list);
}


/** 1 - count frequency of an element in list
 */
int count_value (Node * list, int value) {
	if (list != NULL) {
		if (list->val == value)
			return 1 + count_value (list->next, value);
		else 
			return count_value (list->next, value);
	} else {
		return 0;
	}
}

void test_count_value () {	
	Node * list = create_basic_list_2 (5);
	int value = 2;
	int freq = count_value (list, value);
	printf ("%d occurs %d times in the list\n", value, freq);
}

/** 2 - get nth element if at least n elements exists, else throw error
 */
int nth (Node * list, int n) {
	if (n < 0 || list == NULL)
		return -1;

	if (n == 0)
		return list->val;
	else 
		return nth (list->next, n - 1);
}

void test_nth () {
	Node * list = create_basic_list (5);
	int idx0 = 3, idx1 = 6;

	printf ("%dth element (index: %d) = %d\n", idx0 + 1, idx0, nth (list, idx0));
	printf ("%dth element (index: %d) = %d\n", idx1 + 1, idx1, nth (list, idx1));
}

/** 3 - pop the head: beheads and returns value
 * list changes
 */
int pop (Node ** node) {
	int res = -1;
	if (* node != NULL) {
		res = (* node)->val;
		Node * head = * node;
		* node = (* node)->next;
		free (head);
	}
	return res;
}

void test_pop () {
	Node * list = create_basic_list_3 (5);
	print_list (list);
	while (list != NULL) {
		int val = pop (&list);
		printf ("popped value = %d\n", val);
	}
}


void run_tests () {
	// test_utilities ();

	// test_count_value ();
	// test_nth ();
	test_pop ();
}

int main () {
	run_tests ();

	return 0;
}
