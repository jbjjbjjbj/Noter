#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

static vertex_t *create_vertex(char ref) {
	// Get some space TODO check for null
	vertex_t *v = malloc(sizeof(vertex_t));

	// Set values
	v->ref = ref;
	v->dist = -1;
	v->p = NULL;
	v->adj = NULL;
	return v;
}

static edge_t *create_edge(vertex_t *from, vertex_t *to, int weight) {
	edge_t *old = from->adj;

	// Create new list node
	edge_t *e = malloc(sizeof(edge_t));
	e->weight = weight;
	e->from = from;
	e->to = to;

	// Do new link
	e->next = old;
	if( old ) {
		e->prev = old->prev;
		old->prev = e;
	} else { e->prev = NULL; }
	
	if( e->prev ) {
		e->prev->next = e;
	}

	from->adj = e;

	return e;
}

// For iterating edges
edge_t *edge_next(graph_t *g, edge_t *e) {
	if(e == NULL || e->next == NULL ) {
		// Find next index
		
		// Chose starting index 0 if NULL e
		unsigned char i = e ? e->from->ref+1 : 0;
		for( ; i < 128; i++ ) {
			if( g->vertexes[i] && g->vertexes[i]->adj ) {
				return g->vertexes[i]->adj;
			}
		}
		// No next vertex
		return NULL;
	}

	// Not finished with this adj list
	return e->next;
}

vertex_t *vertex_next(graph_t *g, vertex_t *v) {
	unsigned char ref = v ? v->ref+1 : 0;
	for( ; ref < 128; ref++ ) {
		if( g->vertexes[ref] ) {
			return g->vertexes[ref];
		}
	}

	return NULL;
}

void graph_edge(graph_t *g, char from, char to, int weight) {
	// Does a exists
	if( g->vertexes[from] == NULL ) {
		g->vertexes[from] = create_vertex(from);
	}
	// What about b
	if( g->vertexes[to] == NULL ) {
		g->vertexes[to] = create_vertex(to);
	}

	// Add edge
	create_edge(g->vertexes[from], g->vertexes[to], weight);
}

int graph_print_adj(graph_t *g, char ref) {
	if( g->vertexes[ref] == NULL ) {
		return 1;
	}
	
	edge_t *e = g->vertexes[ref]->adj;
	printf("[ ");
	while(e && e->from->ref == ref) {
		printf("%c[%d] ", e->to->ref, e->weight);
		e = e->next;
	}
	printf("]\n");

	return 0;
}

int graph_to_dot(FILE *f, graph_t *g) {
	// print pre stuff
	fprintf(f, "digraph coolgraph {\n");

	// Label all nodes
	vertex_t *v = vertex_next(g, NULL);
	while( v ) {
		fprintf(f, "%c [label=\"%c(%d)\"];\n", v->ref, v->ref, v->dist);
		v = vertex_next(g, v);
	}
	// Print all the edges
	edge_t *e = edge_next(g, NULL);
	while( e ) {
		fprintf(f, "%c -> %c [label = %d%s];\n", e->from->ref, e->to->ref, e->weight, e->to->p == e->from ? " color=blue" : "");
		e = edge_next(g, e);
	}

	// done
	fprintf(f, "}\n");
}

