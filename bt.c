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

/** prototype for traversal functions
 */
typedef void (* pf) (Node * root);

/** 5 - inorder ()
 * in-order traversal of the tree
 */
void inorder (Node * root) {
	if (root != NULL) {
		inorder (root->left);
		printf ("%d, ", root->val);
		inorder (root->right);
	}
}

/** 6 - postorder ()
 * post-order traversal of the tree
 */
void postorder (Node * root) {
	if (root != NULL) {
		postorder (root->left);
		postorder (root->right);
		printf ("%d, ", root->val);
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

void test_create () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);
	print_tree (tree, postorder);
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
	print_tree (tree, inorder);
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
	print_tree (tree, inorder);

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
	print_tree (tree, inorder);
	int min_v = min_val (tree);
	int max_v = max_val (tree);
	printf ("Minimum = %d, Maximum = %d\n", min_v, max_v);
}

/** 7 - has_path ()
 * returns true if a root-leaf path exists that sum to the given value
 */
Bool has_path (Node * root, int total) {
	if (is_leaf (root) && total == root->val)
		return true;
	else if (root != NULL) 
		return (has_path (root->left, total - root->val) || 
			has_path (root->right, total - root->val));
	else
		return false;
}

void test_has_path () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	// possible totals: 7, 9, 15, 17
	int total = 9;
	Bool res = has_path (tree, total);
	if (res)
		printf ("The tree has a path that sums to %d\n", total);
	else
		printf ("The tree does not have a path that sums to %d\n", total);

	delete_tree (tree);
}

void print_array (int * xs, int n) {
	printf ("[");
	for (int i = 0; i < n; i++)
		printf ("%d, ", xs[i]);
	printf ("]\n");
}

/** 8 - print_paths ()
 * print path-from-root for all leaves
 * one per line
 */
void print_paths (Node * root, int * xs, int n) {
	if (is_leaf (root)) {
		xs[n++] = root->val;
		print_array (xs, n);
	}
	else if (root != NULL) {
		xs[n++] = root->val;
		print_paths (root->left, xs, n);
		print_paths (root->right, xs, n);
	}
}

void test_print_paths () {
	int lo = 1, hi = 8;
	Node * tree = NULL;
	tree = create_basic_tree (tree, lo, hi);
	size_t height = ((unsigned) log2 (hi - lo)) + 1;
	int * xs = (int *) malloc (sizeof (int) * height);

	print_paths (tree, xs, 0);

	delete_tree (tree);
	free (xs);
}

/** 9 - mirror ()
 * mirrors the tree - swaps the left and right nodes
 * changes the tree
 */
void mirror (Node ** root) {
	if (* root != NULL) {
		Node * tmp = (* root)->left;
		(* root)->left = (* root)->right;
		(* root)->right = tmp;
		mirror (&((* root)->left));
		mirror (&((* root)->right));
	}
}

void test_mirror () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);

	mirror (&tree);
	print_tree (tree, inorder);

	delete_tree (tree);
}

/** 10 - double_nodes ()
 * creates a duplicate of each node and inserts in the tree
 */
void double_nodes (Node ** root) {
	if (* root != NULL) {
		double_nodes (&((* root)->left));
		double_nodes (&((* root)->right));
		Node * node = create_node ((* root)->val);
		node->left = (* root)->left;
		(* root)->left = node;
	}
}

void test_double_nodes () {
	Node * tree = NULL;
	tree = create_basic_tree (tree, 1, 8);
	print_tree (tree, inorder);

	double_nodes (&tree);
	print_tree (tree, inorder);

	delete_tree (tree);
}

/** 11 - is_same ()
 * returns true iff 2 trees are exactly same
 * structurally, value-wise for each node
 */
Bool is_same (Node * one, Node * two) {
	if (one != NULL && two != NULL) {
		Bool atm = one->val == two->val;
		return (atm && is_same (one->left, two->left) && 
			is_same (one->right, two->right));
	} else if (one == NULL && two == NULL)		// controversial ?
		return true;
	else
		return false;
}

void test_same () {
	Node * first = NULL;
	Node * second = NULL;
	first = create_basic_tree (first, 1, 8);
	second = create_basic_tree (second, 1, 8);

	Bool res = is_same (first, second);

	if (res)
		printf ("The trees are same.\n");
	else
		printf ("The trees are different.\n");

	delete_tree (first);
	delete_tree (second);
}

void run_tests () {
	// test_create ();
	// test_size ();
	// test_max_depth ();
	// test_min_max ();
	// test_has_path ();
	// test_print_paths ();
	// test_mirror ();
	// test_double_nodes ();
	test_same ();
}

int main () {
	run_tests ();

	return 0;
}
