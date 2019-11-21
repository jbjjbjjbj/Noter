#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "graph.h"

graph_t g;
graph_t newg;
int step;

void dfs_visit(graph_t *g, vertex_t *u, bool doprint) {
	if( doprint ) {
		printf("dfs_visit( %c )\n", u->ref);
	}
	step++;
	u->dtime = step;
	u->color = COLOR_GRAY;
	
	// For every adj
	edge_t *e = u->adj;
	while( e ) {
		vertex_t *v = e->to;
		if( v->color == COLOR_WHITE ) {
			graph_edge(&newg, v->ref, u->ref, 1);
			v->p = u;
			dfs_visit(g, v, doprint);
		}
		e = e->next;
	}

	u->color = COLOR_BLACK;
	step++;
	u->ftime = step;
}


void dfs(graph_t *g, bool doprint) {
	step = 0;

	// For every edge
	vertex_t *u = vertex_next(g, NULL);
	while( u ) {
		if( u->color == COLOR_WHITE ) {
			dfs_visit(g, u, doprint);
		}
		u = vertex_next(g, u);
	}
}

int main() {
	
	graph_edge(&g, 'M', 'O', 1);
	graph_edge(&g, 'O', 'P', 1);
	graph_edge(&g, 'P', 'F', 1);

	graph_edge(&g, 'C', 'F', 1);
	graph_edge(&g, 'F', 'c', 1);

	//graph_to_dot(stdout, &g);
	
	// Timing start
	clock_t t;
	t = clock();

	// Dfs slower when printing.
	dfs(&g, true);

	// Timing stop
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("Dfs took %f seconds\n", time_taken);

	//graph_to_dot(stdout, &newg);

	return 0;
}
