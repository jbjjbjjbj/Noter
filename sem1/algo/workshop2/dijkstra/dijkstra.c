#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct list_item {
	vertex_t *v;
	struct list_item *next;
	struct list_item *prev;
} list_item_t;

typedef struct {
	int len;
	struct list_item *begin;
	struct list_item *end;
} list_t;

void list_push(list_t *s, vertex_t *v) {
	// Create 
	list_item_t *i = malloc(sizeof(list_item_t));
	i->next = NULL;
	i->prev = NULL;
	i->v = v;

	// Link
	if( s->len == 0 ) {
		s->begin = i;
	} else {
		s->end->next = i;
		i->prev = s->end;
	}

	s->end = i;
	s->len++;
}

vertex_t *list_pop_smallest(list_t *s) {
	//printf("beginning %s(%d)\n", s->begin->v->ref, s->begin->v->dist);
	list_item_t *smallest = s->begin;

	// Search
	list_item_t *i = s->begin;
	while( i ) {
		if( smallest->v->dist == -1 || (i->v->dist != -1 && i->v->dist < smallest->v->dist) ) {
			smallest = i;
		}
		i = i->next;
	}

	if( smallest == s->begin ) {
		s->begin = smallest->next;
	} else {
		smallest->prev->next = smallest->next;
	}

	if( smallest == s->end ) {
		s->end = smallest->prev;
	} else {
		smallest->next->prev = smallest->prev;
	}

	vertex_t *v = smallest->v;
	free(smallest);

	s->len--;

	return v;
}

graph_t g;

// Assumes u has an edge to v
void relax(vertex_t *u, vertex_t *v) {
	// Get edge between these two guys
	edge_t *e = u->adj;
	while(e && e->next && strcmp(e->to->ref, v->ref)) { 
		e = e->next; 
	}

	if( v->dist == -1 || v->dist > (u->dist + e->weight) ) {
		v->dist = u->dist + e->weight;
		v->p = u;
	}
}

void dijkstra(graph_t *g, vertex_t *s) {
	list_t list;
	list.len = 0;
	list.end = list.begin = 0;

	s->dist = 0;

	{
		vertex_t *v = vertex_next(g, NULL);
		while( v ) {
			list_push(&list, v);
			v = vertex_next(g, v);
		}
	}

	while( list.len ) {
		vertex_t *u = list_pop_smallest(&list);
		edge_t *e = u->adj;
		while( e ) {
			relax(u, e->to );
			e = e->next;
		}
	}
}

int main() {

	graph_from_dot(stdin, &g);

	dijkstra(&g, graph_vertex(&g, "0"));

	graph_to_dot(stdout, &g);

	return 0;
}
