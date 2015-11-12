#include <stdio.h>
#include <stdlib.h>
#include "objectlist.h"

/** author: mayukh
 * github.com/mayukh42
 */

void test_basic_olist () {
	OList * list = create_OList_from_Array ();
	print_OList (list);
	delete_OList (list);
}

void run_tests() {
	test_basic_olist ();	
}

int main() {
	run_tests();

	return 0;
}
