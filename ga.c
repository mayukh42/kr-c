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

void push_list (List ** list, GNode * w_node) {
	List * listnode = create_listnode (w_node);

	if (* list == NULL) {
		* list = listnode;
		return;
	}

	listnode->next = * list;
	* list = listnode;
}

List * append_list (List * last, List * node) {
	if (last == NULL)
		return node;

	last->next = node;
	last = node;
	return last;
}

GNode * pop (List ** list) {
	if (* list == NULL)
		return NULL;

	List * head = * list;
	GNode * headnode = head->node;
	* list = head->next;
	free (head);
	return headnode;
}

void print_node (GNode * node);

void print_list_rec (List * list) {
	if (list != NULL) {
		print_node (list->node);
		print_list_rec (list->next);
	}
}

void print_list (List * list) {
	printf ("[");
	print_list_rec (list);
	printf ("]\n");
}

void delete_list (List * list) {
	if (list != NULL) {
		delete_list (list->next);
		free (list);
	}
}

GNode * create_gnode (int value) {
	GNode * node = (GNode *) malloc (sizeof (GNode));
	node->val = value;
	node->deg = 0;
	node->status = false;
	node->adjlist = NULL;
	return node;
}

void delete_gnode (GNode * node) {
	if (node != NULL) {
		delete_list (node->adjlist);
		free (node);
	}
}

void print_node (GNode * node) {
	if (node != NULL)
		printf ("%d-%d, ", node->val, node->deg);
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

/** add_edge ()
 * adds a directed edge v->w
 */
void add_edge (GNode * v, GNode * w) {
	if (v == NULL || w == NULL)
		return;

	push_list (&(v->adjlist), w);
	v->deg++;
}

/** struct Queue
 * container queue for graph traversal
 */
typedef struct Queue {
	List * head;
	List * tail;
} Queue;

Queue * create_empty_queue () {
	Queue * q = (Queue *) malloc (sizeof (Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enq (Queue * q, List * node) {
	if (node == NULL || q == NULL)
		return;

	if (q->head == NULL) {
		q->head = node;
		q->tail = node;
		return;
	}

	q->tail->next = node;
	q->tail = node;
}

List * deq (Queue * q) {
	if (q == NULL)
		return NULL;

	if (q->head == NULL)
		return NULL;

	List * node = q->head;
	q->head = node->next;
	
	if (node->next == NULL)
		q->tail = NULL;

	return node;
}

Bool is_empty (Queue * q) {
	if (q == NULL)
		return true;

	return q->head == NULL;
}

void print_queue (Queue * q) {
	print_list (q->head);
}

void test_queue () {
	Queue * q = create_empty_queue ();
	int xs[] = {1,2,3,4,5};
	unsigned n = 5;

	while (n > 0) {
		GNode * node = create_gnode (xs[n-1]);
		List * listnode = create_listnode (node);
		enq (q, listnode);
		n--;
	}
	print_queue (q);

	while (!is_empty (q)) {
		List * it = deq (q);
		print_node (it->node);
		delete_gnode (it->node);
		free (it);
	}
	printf ("\n");
	free (q);
}

void bfs (GNode * v) {
	if (v == NULL)
		return;

	Queue * q = create_empty_queue ();
	v->status = true;
	List * q_node = create_listnode (v);
	enq (q, q_node);

	while (!is_empty (q)) {
		List * it = deq (q);
		GNode * vertex = it->node;
		print_node (vertex); 
		free (it);

		List * neighbors = vertex->adjlist;
		while (neighbors != NULL) {
			if (neighbors->node != NULL && !neighbors->node->status) {
				neighbors->node->status = true;
				List * q_it = create_listnode (neighbors->node);
				enq (q, q_it);
			}
			neighbors = neighbors->next;
		}
	}
	printf ("\n");
	free (q);
}

void test_graph () {
	int xs[] = {1,2,3,4,5,6};
	unsigned v = 6;
	GNode ** vs = malloc (sizeof (GNode *) * v);

	for (unsigned i = 0; i < v; i++)
		vs[i] = create_gnode (xs[i]);

	add_edge (vs[0], vs[1]);
	add_edge (vs[0], vs[3]);
	add_edge (vs[3], vs[1]);
	add_edge (vs[4], vs[3]);
	add_edge (vs[1], vs[4]);
	add_edge (vs[4], vs[2]);
	add_edge (vs[2], vs[5]);

	// print_graph (vs[0]);

	bfs (vs[0]);

	for (unsigned i = 0; i < v; i++)
		delete_gnode (vs[i]);
	free (vs);
}


void run_tests () {
	test_graph ();	
	// test_queue ();
}

int main () {
	run_tests ();

	return 0;
}
