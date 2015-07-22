#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** Graphs
 */

typedef enum Bool {
	false,
	true
} Bool;

struct GNode;

/** Node of the adj list
 */
typedef struct List {
	struct GNode * node;
	struct List * next;
} List;

/** Node of the Graph
 */
typedef struct GNode {
	int val;
	unsigned deg;
	Bool status;
	List * adjlist;
} GNode;

List * create_listnode (GNode * w_node) {
	List * listnode = (List *) malloc (sizeof (List));
	listnode->node = w_node;
	listnode->next = NULL;
	return listnode;
}

void push_adj (List ** list, GNode * w_node) {
	List * listnode = create_listnode (w_node);

	if (* list == NULL) {
		* list = listnode;
		return;
	}

	listnode->next = * list;
	* list = listnode;
}

void print_node (GNode * node);

void print_list_rec (List * list) {
	if (list != NULL) {
		print_node (list->node);
		printf (", ");
		print_list_rec (list->next);
	}
}

void print_list (List * list) {
	printf ("[");
	print_list_rec (list);
	printf ("]\n");
}

GNode * create_gnode (int value) {
	GNode * node = (GNode *) malloc (sizeof (GNode));
	node->val = value;
	node->deg = 0;
	node->status = false;
	node->adjlist = NULL;
	return node;
}

void print_node (GNode * node) {
	if (node != NULL)
		printf ("%d-%d", node->val, node->deg);
}

void print_graph (GNode * node) {
	if (node != NULL && !node->status) {
		print_node (node);
		printf (": ");
		print_list (node->adjlist);
		node->status = true;

		List * it = node->adjlist;
		while (it != NULL) {
			print_graph (it->node);
			it = it->next;
		}
	}
}

void add_edge (GNode * v, GNode * w) {
	if (v == NULL || w == NULL)
		return;

	push_adj (&(v->adjlist), w);
	v->deg++;
}

void test_create_graph () {
	int xs[] = {1,2,3,4,5};
	GNode * node1 = create_gnode (xs[0]);
	GNode * node2 = create_gnode (xs[1]);
	GNode * node3 = create_gnode (xs[2]);
	GNode * node4 = create_gnode (xs[3]);

	add_edge (node1, node2);
	add_edge (node1, node3);
	add_edge (node1, node4);
	add_edge (node2, node3);
	add_edge (node2, node4);

	print_graph (node1);
}

void run_tests () {
	test_create_graph ();	
}

int main () {
	run_tests ();

	return 0;
}
