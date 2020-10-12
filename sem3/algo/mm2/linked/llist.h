#ifndef LIST_H
#define LIST_H

#include "node.h"

typedef struct {
    node_t *root;
    node_t *head;
    unsigned int len;
} llist_t;

void llist_init(llist_t *list);

void llist_append(llist_t *list, int val);

node_t *llist_get_node(llist_t *list, unsigned int index);

int llist_get(llist_t *list, unsigned int index);

int llist_pop(llist_t *list, unsigned int index);

#endif
