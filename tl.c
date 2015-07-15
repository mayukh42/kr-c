#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Tree List Recursion problem
 * convert a BST to doubly linked list
 * Stanford CS Education Library
 * http://cslibrary.stanford.edu/110
 */

/** Common node for BinaryTree and LinkedList
 */
typedef struct Node {
	int val;
	struct Node * left;
	struct Node * right;
} Node;

typedef enum Bool {
	false,
	true
} Bool;

Node * create_node (int value) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->val = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/** Ordered Binary Tree
 */
Node * create_tree (Node * root, int * xs, int lo, int hi) {
	if (lo >= hi)
		return root;

	int midx = ((hi - lo) / 2) + lo;
	root = create_node (xs[midx]);
	root->left = create_tree (root->left, xs, lo, midx);
	root->right = create_tree (root->right, xs, midx + 1, hi);
	return root;
}

typedef void (* pf) (Node * root);

void inorder (Node * root) {
	if (root != NULL) {
		inorder (root->left);
		printf ("%d, ", root->val);
		inorder (root->right);
	}
}

void print_tree (Node * root, pf print) {
	printf ("[");
	print (root);
	printf ("]\n");
}

void delete_tree (Node * root) {
	if (root != NULL) {
		delete_tree (root->left);
		delete_tree (root->right);
		free (root);
	}
}

void test_create_tree () {
	Node * tree = NULL;
	int xs[] = {1,2,3,4,5,6,7};
	tree = create_tree (tree, xs, 0, 7);

	print_tree (tree, inorder);
	delete_tree (tree);
}

int size (Node * root) {
	if (root != NULL) 
		return 1 + size (root->left) + size (root->right);
	else
		return 0;
}

Bool is_leaf (Node * root) {
	if (root != NULL && root->left == NULL && root->right == NULL)
		return true;
	else 
		return false;
}

int min_val (Node * root) {
	if (is_leaf (root)) 
		return root->val;
	else if (root != NULL)
		return min_val (root->left);
	else
		return -1;	
}

int max_val (Node * root) {
	if (is_leaf (root)) 
		return root->val;
	else if (root != NULL)
		return max_val (root->right);
	else
		return -1;	
}

/** Circular Linked List
 * returns the last node added
 */
Node * insert_node (Node ** head, Node * first, Node * second) {
	if (second == NULL)
		return first;

	if (first == NULL) {
		* head = second;
		second->left = second;
		second->right = second;
		return second;
	} else {
		first->right->left = second;
		second->right = first->right;
		first->right = second;
		second->left = first;
		return second;
	}
}

/** concat_lists ()
 * joins end if 1st list to start of 2nd list
 * both lists are circular
 * input: last of 1st list, first of 2nd list
 */
void concat_lists (Node ** head, Node ** first, Node ** second) {
	if (* first == NULL) {
		* head = * second;
		return;
	}

	if (* second == NULL)
		return;
	else {
		(* first)->right->left = (* second)->left;
		(* second)->left->right = (* first)->right;
		(* first)->right = * second;
		(* second)->left = * first;
	}
}

Node * create_list (Node * head, int * xs, int n) {
	Node * last = NULL;
	for (int i = 0; i < n; i++) {
		Node * node = create_node (xs[i]);
		last = insert_node (&head, last, node);
	}
	return head;
}

void print_list (Node * head) {
	printf ("[");
	Node * it = head;
	while (it != NULL) {
		printf ("%d, ", it->val);
		it = it->right;
		if (it == head)
			break;
	}
	printf ("]\n");
}

void test_create_list () {
	Node * head = NULL;
	int xs[] = {1,2,3};
	head = create_list (head, xs, 3);
	print_list (head);
}

void test_concat_lists () {
	Node * first = NULL;
	Node * second = NULL;
	Node * head = NULL;

	int xs[] = {1};
	int ys[] = {5};

	for (int i = 0; i < 1; i++) {
		Node * node = create_node (xs[i]);
		first = insert_node (&head, first, node);
	}
	second = create_list (second, ys, 1);
	printf ("%d\n", first->val);
	printf ("%d\n", second->val);
	printf ("%d\n", second->left->val);

	print_list (head);
	print_list (second);

	concat_lists (&head, &first, &second);
	print_list (head);
	printf ("%d\n", head->left->val);
}

/** tree2list ()
 * convert ordered BinaryTree to circular LinkedList
 * returns last node added
 */
Node * tree2list (Node * root, Node ** head) {
	if (root != NULL) {
		Node * smaller = NULL;
		Node * larger = NULL;

		if (root->left != NULL)
			smaller = tree2list (root->left, head);

		if (root->right != NULL)
			larger = tree2list (root->right, head);

		printf ("at node %d:\n", root->val);
		print_list (smaller);
		print_list (larger);

		root->left = root;
		root->right = root;
		smaller = insert_node (head, smaller, root);
		* head = smaller->right;

		if (larger != NULL) {
			printf ("larger->right = %d\n", larger->right->val);
			printf ("smaller = %d\n", smaller->val);
			concat_lists (head, &smaller, &(larger->right));
		}

		print_list (* head);

		return (* head)->left;
	} else
		return root;
}

void test_tree2list () {
	Node * tree = NULL;
	int xs[] = {1,2,3,4,5,6,7};
	tree = create_tree (tree, xs, 0, 7);
	print_tree (tree, inorder);

	Node * list = NULL;
	Node * last = tree2list (tree, &list);
	print_list (list);
}



void run_tests () {
	// test_create_tree ();
	// test_create_list ();
	// test_concat_lists ();
	test_tree2list ();
}

int main () {
	run_tests ();

	return 0;
}
