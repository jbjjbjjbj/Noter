#include "llist.h"

#include <string.h>
#include <stdio.h>


#define OUT_OFF_BOUNDS 2

void llist_init(llist_t *list)
{
	/* Zero out structure */
	list->head = list->root = NULL;

	list->len = 0;

}

void llist_append(llist_t *list, int val)
{
	/* Insert node after HEAD */
	list->head = node_insert(list->head, val);

	/* Check if was list is empty */
	if ( list->len == 0 ) {
		/* Set root */
		list->root = list->head;
	}

	/* Increase count */
	list->len++;
}

node_t *llist_get_node(llist_t *list, unsigned int index)
{
	/* Check if we have it */
	if ( index >= list->len ) {
		return NULL;
	}

	/* Find the best way to go down the list */
	int direc = index > (list->len / 2) ? -1 : 1;

	/* Setup start location */
	int pos = direc > 0 ? 0 : list->len-1;
	node_t *node = direc > 0 ? list->root : list->head;
	
	/* Go to index */
	while ( pos != index ) {
		/* TODO kinda risky, we trust our math and len */
		node = direc > 0 ? node->next : node->prev;

		pos += direc;
	}

	return node;
}

int llist_get(llist_t *list, unsigned int index)
{
	/* Get node */
	node_t *node = llist_get_node(list, index);
	if ( node == NULL ) {
		/* Yes i know this is stupid */
		return -1;
	}

	/* Return value */
	return node->val;
}


int llist_pop(llist_t *list, unsigned int index)
{
	/* Get node */
	node_t *node = llist_get_node(list, index);
	if ( node == NULL ) {
		/* Yes i know this is stupid */
		return -1;
	}

	/* Update root and head if we delete it */
	if ( node == list->root ) {
		list->root = node->next;
	}
	if ( node == list->head ) {
		list->head = node->prev;
	}
	
	/* Keep len up to date */
	list->len--;

	/* Delete stuff */
	return node_pop(node);
}
