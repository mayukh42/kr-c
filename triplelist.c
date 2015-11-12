#include <stdio.h>
#include <stdlib.h>
#include "triplelist.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_create_TList () {
	int x0s[] = {5,33,17,2,1};
	TList * list0 = create_List_from_Array (NULL, x0s, 5);

	int x1s[] = {6,25,6};
	TList * list1 = create_List_from_Array (NULL, x1s, 3);

	int x2s[] = {2,7};
	TList * list2 = create_List_from_Array (NULL, x2s, 2);

	list0->child = list1;
	list0->next->next->next->child = list2;

	int x3s[] = {8};
	TList * list3 = create_List_from_Array (NULL, x3s, 1);

	int x4s[] = {9};
	TList * list4 = create_List_from_Array (NULL, x4s, 1);

	int x5s[] = {12,5};
	TList * list5 = create_List_from_Array (NULL, x5s, 2);

	list1->next->child = list3;
	list1->next->next->child = list4;
	list2->child = list5;

	int x6s[] = {7};
	TList * list6 = create_List_from_Array (NULL, x6s, 1);

	int x7s[] = {21,3};
	TList * list7 = create_List_from_Array (NULL, x7s, 2);

	list4->child = list6;
	list5->child = list7;

	print_TList (list0);
}

void run_tests() {
	test_create_TList ();
}

int main() {
	run_tests();

	return 0;
}
