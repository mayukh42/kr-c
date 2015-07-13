#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42

 * Linked List Problems, Stanford CS Education Library
 * http://cslibrary.stanford.edu/105
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

	v_node->next = (* node)->next;
	(* node)->next = v_node;
}

void append_node (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = (* node)->next;
	(* node)->next = v_node;
}

Node * create_basic_list (int * xs, int n) {
	Node * list = NULL;
	for (int i = n-1; i >= 0; i--) 
		push (&list, xs[i]);
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
			push (&list, i*2);
			last = list;
		} else {
			push (&(last->next), i*2);
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

/** 4 - delete list 
 */
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
	int xs[] = {1,2,3,4,5};
	Node * list = create_basic_list (xs, 5);
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

/** 5 - insert nth - inserts at nth index 
 */
void insert_at (Node ** list, int n, int val) {
	int len = length (* list);
	if (n < 0 || n > len)
		return;

	Node ** it = list;
	while (n > 0) {
		it =  &((* it)->next);
		n--;
	}
	push (it, val);
}

void test_insert_at () {
	Node * list = create_basic_list_3 (5);
	print_list (list);

	insert_at (&list, 3, 8);
	print_list (list);

	insert_at (&list, 0, 10);
	print_list (list);

	Node * empty = NULL;
	insert_at (&empty, 0, 11);
	print_list (empty);

	delete_list (list);
	delete_list (empty);
}

void push_node (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	v_node->next = * node;
	* node = v_node;
}

/** 6 - sorted insert - insert at the right position
 * in a sorted list
 */
void sorted_insert (Node ** list, Node * v_node) {
	Node ** it = list;
	while (* it != NULL && v_node->val > (* it)->val)
		it = &((* it)->next);

	push_node (it, v_node);
}

void test_sorted_insert () {
	Node * list = create_basic_list_3 (5);
	print_list (list);

	sorted_insert (&list, create_node (3));
	sorted_insert (&list, create_node (1));
	sorted_insert (&list, create_node (20));
	print_list (list);

	Node * empty = NULL;
	sorted_insert (&empty, create_node (6));
	print_list (empty);

	delete_list (list);
	delete_list (empty);
}

/** 7 - insertion sort 
 * O(n^2)
 */
void isort_list (Node ** list) {
	if (* list == NULL)
		return;

	Node * it = * list;
	* list = NULL;
	while (it != NULL) {
		Node * it2 = it->next;
		it->next = NULL;
		sorted_insert (list, it);
		it = it2;
	}
}

void test_isort () {
	Node * list = NULL;
	append (&list, 8);
	append (&list, 0);
	append (&list, 2);
	append (&list, 7);
	append (&list, 0);
	append (&list, 1);

	print_list (list);

	isort_list (&list);
	print_list (list);
}

void append_list (Node ** node, Node * v_node) {
	if (* node == NULL) {
		* node = v_node;
		return;
	}

	(* node)->next = v_node;
}

/** 8 - append (concat) lists
 * ++
 */
void concat (Node ** first, Node ** second) {
	if (* first == NULL) {
		* first = * second;
		return;
	}
	
	Node ** it = first;
	while (* it != NULL) 
		it = &((* it)->next);
	append_list (it, * second);
	* second = NULL;
}

void test_concat () {
	Node * first = create_basic_list_2 (4);
	Node * second = create_basic_list_3 (5);
	concat (&first, &second);
	print_list (first);

	delete_list (first);

	Node * third = NULL;
	Node * fourth = NULL;
	Node * fifth = create_basic_list_3 (3);
	concat (&third, &fourth);
	print_list (third);

	concat (&fifth, &fourth);
	print_list (fifth);
}

/** 9 - split into 2 halves
 * longer half goes in the first
 */
void split (Node ** list, Node ** second) {
	int n = length (* list);
	if (n == 0)
		return;

	n = n - n/2;
	Node ** it = list;
	while (n > 1) {
		it = &((* it)->next);
		n--;
	}
	* second = (* it)->next;
	(* it)->next = NULL;
}

void test_split () {
	Node * list = create_basic_list_3 (3);

	Node * second = NULL;
	split (&list, &second);

	print_list (list);
	print_list (second);
}

void remove_next (Node ** node) {
	if (* node == NULL)
		return;
	else if ((* node)->next == NULL)
		return;

	Node * next = (* node)->next;
	(* node)->next = next->next;
	free (next);
}

/** 10 - remove duplicates
 * assume sorted list
 */
void distinct (Node ** list) {
	if (* list == NULL)
		return;

	Node ** it = list;
	while (* it != NULL) {
		Node * next = (* it)->next;
		if (next != NULL && next->val == (* it)->val) {
			remove_next (it);
			continue;
		} else {
			it = &((* it)->next);
		}
	}
}

void test_distinct () {
	int xs[] = {1,1,2,3,3,3,4,4,5};
	Node * list = create_basic_list (xs, 9);
	print_list (list);
	// remove_next (&list);
	distinct (&list);
	print_list (list);
}

/** 11 - move_node: move head of 2nd list to head of 1st list
 */
void move_node (Node ** first, Node ** second) {
	if (* second == NULL)
		return;

	Node * s0 = * second;
	* second = (* second)->next;
	s0->next = NULL;
	push_node (first, s0);
}

void test_move_node () {
	Node * list = create_basic_list_3 (5);
	Node * list2 = create_basic_list_2 (5);

	move_node (&list, &list2);
	print_list (list);
	print_list (list2);
}

/** 12 - alter_split ()
 * split every alternate element into the same list
 * return 2 lists
 */
void alter_split (Node ** list, Node ** first, Node ** second) {
	if (* list == NULL)
		return;

	int select = 1;
	Node ** it = list;
	while (* it != NULL) {
		if (select)
			move_node (first, it);
		else
			move_node (second, it);		
		select = (select + 1) % 2;
	}
}

void test_alter_split () {
	Node * list = create_basic_list_2 (9);
	print_list (list);

	Node * first = NULL;
	Node * second = NULL;

	alter_split (&list, &first, &second);
	print_list (first);
	print_list (second);
}

void move_node_last (Node ** first, Node ** second) {
	
}

/** shuffle_merge ()
 * merges 2 lists, each element taken alternately until either list runs out
 * at which point, the remaining elements of the other list are copied as is
 */
void shuffle_merge (Node ** first, Node ** second, Node ** list) {
	while (* first != NULL && * second != NULL) {
		move_node (list, first);
		move_node (list, second);
	} 
	while (* first != NULL)
		move_node (list, first);
	while (* second != NULL)
		move_node (list, second);
}

void test_shuffle_merge () {
	int xs[] = {1,3,5,7,9};
	Node * first = create_basic_list (xs, 5);
	Node * second = create_basic_list_3 (3);
	Node * list = NULL;

	print_list (first);
	print_list (second);

	shuffle_merge (&first, &second, &list);
	print_list (list);
}

/** sorted_merge ()
 * merge 2 lists in order
 */


void run_tests () {
	// test_utilities ();

	// test_count_value ();
	// test_nth ();
	// test_pop ();
	// test_insert_at ();
	// test_sorted_insert ();
	// test_isort ();
	// test_concat ();
	// test_split ();
	// test_distinct ();
	// test_move_node ();
	// test_alter_split ();
	test_shuffle_merge ();
}

int main () {
	run_tests ();

	return 0;
}
