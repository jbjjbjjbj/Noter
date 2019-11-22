#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

// Hashtable
static unsigned int hash(char *s) {
	uint32_t hv = 0;
	for( int i = 0; s[i] != '\0'; i++ ) {
		// take MSB 6 bits of hv and xors with LSB of s[i]
		uint32_t v = ( hv >> 26 ) ^ (s[i] & 0x3f);

		// Push those back on hv
		hv = (hv << 4) | v;
	}
	// Return appropriate size
	return hv % HASHSIZE;
}


static void table_insert(graph_t *g, vertex_t *v, char *var) {
	unsigned int index = hash(var);

	// Save old value
	vertex_t *oldSym = g->hashtable[index];

	// Make new
	g->hashtable[index] = v;

	// Link old one
	g->hashtable[index]->next = oldSym;
}

static vertex_t *table_lookup(graph_t *g, char *var) {
	unsigned int index = hash(var);
	vertex_t *n = g->hashtable[index];

	// Look trough list
	while(n != NULL && strcmp(n->ref, var) != 0) {
		n = n->next;
	}

	return n;
}

static vertex_t *create_vertex(char *ref) {
	// Get some space TODO check for null
	vertex_t *v = malloc(sizeof(vertex_t));

	// Set values
	v->ref = strdup(ref);
	v->color = COLOR_WHITE;
	v->next = NULL;
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
		vertex_t *v = e ? e->from : NULL;

		// Find next vertex
		v = vertex_next(g, v);
		while( v ) {
			// Check if found
			if( v->adj ) {
				return v->adj;
			}

			v = vertex_next(g, v);
		}

		// No next vertex
		return NULL;
	}

	// Not finished with this adj list
	return e->next;
}

vertex_t *vertex_next(graph_t *g, vertex_t *v) {
	if( v == NULL || v->next == NULL) {
		// Go to next index in hashtable
		int i = v ? hash(v->ref)+1 : 0;
		for( ; i < HASHSIZE; i++) {
			if( g->hashtable[i] ) {
				return g->hashtable[i];
			}
		}

		// No next
		return NULL;
	}

	return v->next;
}

void graph_edge(graph_t *g, char *from, char *to, int weight) {
	vertex_t *fromv, *tov;
	// Does a exists
	if( (fromv = table_lookup(g, from)) == NULL ) {
		fromv = create_vertex(from);
		table_insert(g, fromv, from);
	}
	// What about b
	if( (tov = table_lookup(g, to)) == NULL ) {
		tov = create_vertex(to);
		table_insert(g, tov, to);
	}

	// Add edge
	create_edge(fromv, tov, weight);
}

int graph_print_adj(graph_t *g, char *ref) {
	vertex_t *v = table_lookup(g, ref);
	if( v == NULL ) {
		return 1;
	}
	
	edge_t *e = v->adj;
	printf("[ ");
	while(e && e->from->ref == ref) {
		printf("%s[%d] ", e->to->ref, e->weight);
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
		fprintf(f, "%s [label=\"%s\"];\n", v->ref, v->ref);
		v = vertex_next(g, v);
	}
	// Print all the edges
	edge_t *e = edge_next(g, NULL);
	while( e ) {
		fprintf(f, "%s -> %s [label = %d];\n", e->from->ref, e->to->ref, e->weight);
		e = edge_next(g, e);
	}

	// done
	fprintf(f, "}\n");
}

