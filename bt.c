#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Binary Trees
 * Stanford CS Education Library
 * http://cslibrary.stanford.edu/110
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

int max (int a, int b) {
	return a > b ? a : b;
}

Bool lookup (Node * root, int value) {
	if (root == NULL) 
		return false;
	
	if (root->val == value)
		return true;
	else if (root->val < value)
		return lookup (root->left, value);
	else 
		return lookup (root->right, value);
}

Node * create_node (int value) {
	Node * node = (Node *) malloc (sizeof (Node));
	node->val = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void insert (Node ** root, int value) {
	if (* root == NULL) {
		Node * node = create_node (value);
		* root = node;
		return;
	} 
	else if (value < (* root)->val) 
		insert (&(* root)->left, value);
	else if (value > (* root)->val)
		insert (&(* root)->right, value);
	else
		return;
}

/** 1 - create_basic_tree ()
 * creates a balanced BST w/ values in the given range 
 * including lower, excluding upper
 */
Node * create_basic_tree (Node * root, int m, int n) {
	if (m >= n)
		return root;

	int middle = ((n - m) / 2) + m;
	root = create_node (middle);
	root->left = create_basic_tree (root->left, m, middle);
	root->right = create_basic_tree (root->right, middle + 1, n);
	return root;
} 

void print_nodes (Node * root) {
	if (root != NULL) {
		print_nodes (root->left);
		printf ("%d, ", root->val);
		print_nodes (root->right);
	}
}

void print_tree (Node * root) {
	printf ("[");
	print_nodes (root);
	printf ("]\n");
}

void delete_tree (Node * root) {
	if (root != NULL) {
		delete_tree (root->left);
		delete_tree (root->right);
		free (root);
	}
}

void test_create () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 0, 5);
	print_tree (tree);
	delete_tree (tree);
}

/** 2 - size ()
 */
int size (Node * root) {
	if (root != NULL) 
		return 1 + size (root->left) + size (root->right);
	else
		return 0;
}

void test_size () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 0, 5);
	print_tree (tree);
	printf ("Size of the tree = %d\n", size (tree));
}

/** 3 - max_depth ()
 * balanced BST must have max_depth == lg (n) + 1
 * where n = upper - lower in the range from which tree was created
 */
int max_depth (Node * root) {
	if (root == NULL)
		return 0;
	else 
		return max (max_depth (root->left) + 1, max_depth (root->right) + 1);
}

Bool is_balanced (Node * tree) {
	if (tree != NULL) {
		int leftdepth = max_depth (tree->left);
		int rightdepth = max_depth (tree->right);
		return abs (leftdepth - rightdepth) <= 1 ? true : false;
	}
	else
		return false;
}

void test_max_depth () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree);

	double gold = log2 (size (tree));
	int depth = max_depth (tree);
	printf ("Max depth of the tree = %d\n", depth);
	printf ("Depth check: %s\n", abs (ceil (gold) - (double) depth) <= 1.0 ? "ok" : "not ok");
	printf ("Balanced check: %s\n", is_balanced (tree) == true ? "ok" : "not ok");
}

Bool is_leaf (Node * root) {
	if (root != NULL && root->left == NULL && root->right == NULL)
		return true;
	else 
		return false;
}

/** 4 - min_val (), max_val ()
 * returns the min value in tree
 */
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

void test_min_max () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 17);
	print_tree (tree);
	int min_v = min_val (tree);
	int max_v = max_val (tree);
	printf ("Minimum = %d, Maximum = %d\n", min_v, max_v);
}

void run_tests () {
	// test_create ();
	// test_size ();
	// test_max_depth ();
	test_min_max ();
}

int main () {
	run_tests ();

	return 0;
}
