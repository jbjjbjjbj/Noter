#include <stdio.h>

#include "tree.h"

int main() {
	tree_t t;
	t.root = 0;

	node_t *a = tree_insert(&t, 1, "Hej");

	node_t *b = tree_insert(&t, 3, "med");

	tree_insert(&t, 11, "dig");
	tree_insert(&t, 9, "dig");
	tree_insert(&t, 12, "dig");

	tree_insert(&t, 10, "hvordan");

	tree_insert(&t, 8, "det");

	tree_insert(&t, 4, "branch");

	tree_insert(&t, 5, "2");


	tree_insert(&t, 0, "Og den sidste");

	tree_insert(&t, 2, "Cool nok");
	tree_print(&t);

	printf("%s\n", tree_search(&t, 10));
	printf("%s\n", tree_search(&t, 11));
	printf("%s\n", tree_search(&t, 1));
	printf("%s\n", tree_search(&t, 0));
	printf("%s\n", tree_search(&t, 99));

}
