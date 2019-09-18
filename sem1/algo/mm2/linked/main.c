#include <stdio.h>
#include "node.h"
#include "llist.h"

void list_print(node_t *root) {
	int index = 0;
	/* Loop through notes and print them */
	while( root != NULL ) {
		/* Print a value */
		printf("%d: %d\n", index++, root->val);

		/* Next value */
		root = root->next;
	}
}

/* Remove node */
int main() {
	
	/* Do some stuff */
	llist_t list;
	llist_init(&list);

	llist_append(&list, 11); // 0
	llist_append(&list, 22); // 1
	llist_append(&list, 33); // 2
	llist_append(&list, 44); // 3
	llist_append(&list, 89); // 4
	llist_append(&list, 12); // 5
	llist_append(&list, 2);  // 6
	llist_append(&list, 1);  // 7
	llist_append(&list, 7);  // 8
	llist_append(&list, 232);// 9

	list_print(list.root);
	printf("%d\n", llist_get(&list, 5));
	llist_pop(&list, 9);
	printf("%d\n", llist_get(&list, 7));

	list_print(list.root);

	while( list.len ) {
		printf("Popped %d\n", llist_pop(&list, 0));
	}
}
