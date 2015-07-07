#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

#define SIZE 5

struct LinkedList;

typedef struct LinkedList {
	int val;
	struct LinkedList * next;
} LinkedList;

LinkedList * create_node (int v) {
	LinkedList * node = (LinkedList *) malloc (sizeof (LinkedList));
	node->val = v;
	node->next = NULL;
	return node;
}

void delete_nodes (LinkedList * list) {
	if (list != NULL) {
		delete_nodes (list->next);
	}
	free (list);
}

void print_list (LinkedList * list) {
	if (list != NULL) {
		printf ("%d, ", list->val);
		print_list (list->next);
	}
}

LinkedList * append_node (LinkedList * list, LinkedList * node) {
	if (list == NULL)
		return node;
	if (node == NULL)
		return list;

	LinkedList * it = list;
	while (it->next != NULL) {
		it = it->next;
	}
	it->next = node;
	return list;
}

LinkedList * reverse_arrows (LinkedList * list) {
	if (list == NULL)
		return list;

	if (list->next == NULL)
		return list;
	else {
		LinkedList * tail = list->next;
		list->next = NULL;
		return append_node (reverse_arrows (tail), list);
	}
}

void test_reverse_arrows () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = NULL;
	for (int i = 0; i < SIZE; i++) {
		LinkedList * node = create_node (xs[i]);
		if (list == NULL)
			list = node;
		else 
			list = append_node (list, node);
	}

	print_list (list); printf ("\n");

	list = reverse_arrows (list);
	print_list (list); printf ("\n");

	delete_nodes (list);
}


void find_y_point (LinkedList * list1, LinkedList * list2) {
	int len1 = 0, len2 = 0;
	LinkedList * first = list1;
	LinkedList * second = list2;
	while (first != NULL) {
		len1++;
		first = first->next;
	}
	while (second != NULL) {
		len2++;
		second = second->next;
	}

	first = list1;
	second = list2;

	if (len1 > len2) {
		int n = len1 - len2;
		while (n > 0) {
			first = first->next;
			n--;
		}		
	} else if (len2 > len1) {
		int n = len2 - len1;
		while (n > 0) {
			second = second->next;
			n--;
		}
	}

	while (first != NULL && second != NULL) {
		if (first->val == second->val) {
			printf ("The lists meet at value = %d\n", first->val);
			return;
		}
		first = first->next;
		second = second->next;
	}
	printf ("Lists are separate\n");
}

void test_y_point () {
	int xs[] = {1,2,3,4,5};
	LinkedList * list = NULL;
	LinkedList * last = NULL;
	for (int i = 0; i < SIZE; i++) {
		LinkedList * node = create_node (xs[i]);
		if (list == NULL) {
			list = node;
			last = list;
		}
		else {
			last->next = node;
			last = node;
		}
	}

	LinkedList * list2 = create_node (-1);
	LinkedList * node = create_node (0);
	node->next = list;
	list2->next = node;

	print_list (list); printf ("\n");
	print_list (list2); printf ("\n");

	find_y_point (list, list2);

	delete_nodes (list2);
}

void run_tests () {
	// test_y_point ();
	test_reverse_arrows ();
}

int main () {
	run_tests ();

	return 0;
}
