#include "node.h"

#include <string.h>
#include <stdlib.h>

/* Insert after node */
node_t *node_insert(node_t *node, int val)
{
	/* Create new node */
	node_t *newNode = (node_t *) malloc( sizeof(node_t) );
	if ( newNode == NULL ) {
		return NULL;
	}


	newNode->val = val;
	newNode->prev = node;

	/* Check if there is node before */
	if ( node == NULL ) {
		/* If not then there is no after */
		newNode->next = NULL;
		return newNode;
	}

	/* Set next node */
	newNode->next = node->next;
	node->next = newNode;

	/* Check node after */
	if ( newNode->next != NULL ) {
		/* Backlink next node */
		newNode->next->prev = newNode;
	}

	return newNode;
}

/* Pop node */
int node_pop(node_t *node)
{
	int val = node->val;

	/* Check prev */
	if ( node->prev != NULL ) {
		/* Point last node to next node */
		node->prev->next = node->next;
	}

	/* Check next */
	if ( node->next != NULL ) {
		node->next->prev = node->prev;
	}

	/* Free memory */
	free(node);

	return val;
}
