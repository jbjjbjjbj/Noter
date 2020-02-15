#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

static node_t *create_node(unsigned int index, char *val)
{
	node_t *node = malloc( sizeof(node_t) );
	memset(node, 0, sizeof(node_t));

	node->value = val;
	node->index = index;
}

/* Comments are based of dir = CHILD_LEFT */
void node_rotate(tree_t *tree, node_t *x, int dir)
{
	/* Node below which we should rotate with */
	node_t *y = x->children[!dir];

	/* Move y's left to x's right */
	x->children[!dir] = y->children[dir];

	/* Update parent */
	if ( y->children[dir] ) {
		y->children[dir]->p = x;
	}

	/* Switch around x and y */
	y->p = x->p;

	/* Check if y is new root if not update x's parent */
	if ( !y->p ) {
		tree->root = y;
	} else if ( x == x->p->children[CHILD_LEFT]) {
		x->p->children[CHILD_LEFT] = y;
	} else {
		x->p->children[CHILD_RIGHT] = y;
	}
	
	/* Update y's ref */
	y->children[dir] = x;
	x->p = y;

}

static void insert_fixup(tree_t *tree, node_t *z)
{
	while ( z->p && z->p->black == false ) {
		/* Set the right direction */
		int dir = (z->p == z->p->p->children[CHILD_LEFT]) ? CHILD_RIGHT : CHILD_LEFT;

		/* Get uncle */
		node_t *y = z->p->p->children[dir];
		if ( y && !y->black ) {
			/* Case 1 */
			z->p->black = true;
			y->black = true;
			z->p->p->black = false;

			z = z->p->p;
		} else if ( z == z->p->children[dir] ) {
			/* Case 2 */
			z = z->p;
			node_rotate(tree, z, !dir);
		} else {
			/* Case 3 */
			z->p->black = true;
			z->p->p->black = false;
			node_rotate(tree, z->p->p, dir);
		}
	}

	tree->root->black = true;

}

static node_t *insert_recur(node_t *node, unsigned int index, char *val)
{
	int dir = node->index < index ? CHILD_RIGHT : CHILD_LEFT;

	if ( node->children[dir] ) {
		return insert_recur(node->children[dir], index, val);
	}

	/* Found stop */
	node_t *new = create_node(index, val);
	new->p = node;
	node->children[dir] = new;

	return new;
}

node_t *tree_insert_pleb(tree_t *tree, unsigned int index, char *val)
{
	if ( !tree->root ) {
		tree->root = create_node(index, val);
		return tree->root;
	}

	return insert_recur(tree->root, index, val); 
}

node_t *tree_insert(tree_t *tree, unsigned int index, char *val)
{
	if ( !tree->root ) {
		tree->root = create_node(index, val);
		tree->root->black = true;
		return tree->root;
	}

	node_t *new = insert_recur(tree->root, index, val); 
	insert_fixup(tree, new);

	return new;
}

char *tree_search(tree_t *tree, unsigned int index)
{
	node_t *z = tree->root;
	while ( z->index != index ) {
		z = z->children[z->index < index ? CHILD_RIGHT : CHILD_LEFT];
		if ( !z ) {
			return NULL;
		}
	}

	return z->value;
}

static inline void print_indent(int num)
{
	for ( int i = 0; i < num; i++ ) {
		printf("  ");
	}
}

static inline void print_text(node_t *node, bool bold)
{
	if ( bold ) {
		printf("\033[1m%d\033[22m\n", node->index);
	} else {
		printf("%d\n", node->index);
	}

}

static void print_recur(node_t *node, int ident)
{
	if ( !node ) {
		return;
	}
	print_recur(node->children[CHILD_RIGHT], ident+1);
	
	print_indent(ident);	
	print_text(node, node->black);

	print_recur(node->children[CHILD_LEFT], ident+1);
}

void tree_print(tree_t *tree)
{
	print_recur(tree->root, 0);	
}

