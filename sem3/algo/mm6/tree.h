#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#define CHILD_LEFT 0
#define CHILD_RIGHT 1

typedef struct node_struct {
    struct node_struct *p;
    struct node_struct *children[2];
    unsigned int index;
    bool black;
    char *value;
} node_t;

typedef struct {
    node_t *root;
} tree_t;

void tree_print(tree_t *tree);

node_t *tree_insert(tree_t *tree, unsigned int index, char *val);
node_t *tree_insert_pleb(tree_t *tree, unsigned int index, char *val);

void node_rotate(tree_t *tree, node_t *x, int dir);

char *tree_search(tree_t *tree, unsigned int index);

#endif
