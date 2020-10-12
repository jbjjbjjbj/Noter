#ifndef GRAPH_H_
#define GRAPH_H_

struct vertex_struct;

// Linked list
typedef struct edge_struct {
    int weight;
    struct vertex_struct *from;
    struct vertex_struct *to;
    // Linked list stuff
    struct edge_struct *next;
    struct edge_struct *prev;
} edge_t;

typedef struct vertex_struct {
    char ref;
    int dist;
    struct vertex_struct *p;
    edge_t *adj;
} vertex_t;

typedef struct {
    vertex_t *vertexes[128];

} graph_t;

int graph_to_dot(FILE *f, graph_t *g);
int graph_print_adj(graph_t *g, char ref);
void graph_edge(graph_t *g, char from, char to, int weight);
edge_t *edge_next(graph_t *g, edge_t *e);
vertex_t *vertex_next(graph_t *g, vertex_t *v);

#endif // GRAPH_H_
