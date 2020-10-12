#ifndef NODE_H
#define NODE_H

typedef struct node_struct {
    int val;
    struct node_struct *next;
    struct node_struct *prev;
} node_t;

/** @brief Create a new node after specified node 
 *  
 *  @param node Pointer to node where new node should be inserted, can also be NULL
 *  @param val Value to add to new node
 */
node_t *node_insert(node_t *node, int val);

/** @brief Pop node from chain and free's the resource
 *  
 *  @return Value in node
 */
int node_pop(node_t *node);

#endif
