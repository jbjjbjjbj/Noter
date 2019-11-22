#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

graph_t g;
graph_t newg;
int step;

void dfs_visit(graph_t *g, vertex_t *u, bool doprint) {
	if( doprint ) {
		printf("dfs_visit( %s )\n", u->ref);
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

#define BENCH 9999

int main() {

	// benchmark

	// Start by generating
	for(int i = 0; i < BENCH; i++) {
		char from[5];
		char to[5];
		sprintf(from, "%d", i);
		sprintf(to, "%d", rand() % BENCH);
		graph_edge(&g, from, to, 1);
	}
	FILE *f = fopen("hej.dot", "w");
	graph_to_dot(f, &g);

	{
		// Timing start
		clock_t t;
		t = clock();

		dfs(&g, true);

		// Timing stop
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
		printf("Dfs took %f seconds\n", time_taken);
	}
	
	return 0;
	
	graph_edge(&g, "hej", "med", 1);
	graph_edge(&g, "med", "dig", 1);
	graph_edge(&g, "dig", "hvordan", 1);

	graph_edge(&g, "det", "hvordan", 1);
	graph_edge(&g, "hvordan", "det", 1);

	graph_to_dot(stdout, &g);
	
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
