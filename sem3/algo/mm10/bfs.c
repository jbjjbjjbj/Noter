#include <stdio.h>
#include <stdlib.h>

#define COL_WHITE 0
#define COL_GRAY  1
#define COL_BLACK 2

typedef struct list_node_t_struct {
	struct list_node_t_struct *next;
	void *val;
} list_node_t;

typedef struct vertex_struct {
	char ref;
	int color;
	int dist;
	struct vertex_struct *p;
	list_node_t *adj;
} vertex_t;

vertex_t *create_vertex(char ref) {
	// Get some space TODO check for null
	vertex_t *v = malloc(sizeof(vertex_t));

	// Set values
	v->ref = ref;
	v->color = COL_WHITE;
	v->dist = -1;
	v->p = NULL;
	v->adj = NULL;
}

vertex_t *add_adj(vertex_t *v, vertex_t *add) {
	list_node_t *oldN = v->adj;

	// Create new list node
	list_node_t *n = malloc(sizeof(list_node_t));
	n->val = add;
	n->next = oldN;

	v->adj = n;

	return add;
}

void print_adj(vertex_t *v) {
	list_node_t *n = v->adj;
	printf("[ ");
	while(n) {
		printf("%c ", *((char *)n->val));
		n = n->next;
	}
	printf("]\n");
}

vertex_t *vertexes[128];

void add_edge(char a, char b) {
	// Does a exists
	if( vertexes[a] == NULL ) {
		vertexes[a] = create_vertex(a);
	}
	// What about b
	if( vertexes[b] == NULL ) {
		vertexes[b] = create_vertex(b);
	}

	// Add edge
	add_adj(vertexes[a], vertexes[b]);
}

typedef struct {
	unsigned int len;
	list_node_t *in;
	list_node_t *out;
} queue_t;

void enqueue(queue_t *q, vertex_t *v) {
	list_node_t *n = malloc(sizeof(list_node_t));
	n->val = v;

	// Add at end
	list_node_t *old = q->in;
	q->in = n;
	if( old ) {
		old->next = n;
	}

	// Make sure we have an out
	if( q->out == NULL ) {
		q->out = n;
	}

	q->len++;
}

vertex_t *dequeue(queue_t *q) {
	list_node_t *n = q->out;
	if( n == NULL ) {
		return NULL;
	}
	vertex_t *v = (vertex_t *)n->val;

	// Move out forward
	q->out = n->next;
	q->len--;

	// Free node and return
	free(n);
	return v;
}

void bfs(vertex_t *s) {
	queue_t q = {0, NULL, NULL };
	enqueue(&q, s);
	s->dist = 0;
	
	while( q.len ) {
		vertex_t *u = dequeue(&q);
		list_node_t *n = u->adj;
		while( n ) {
			vertex_t *v = (vertex_t *)n->val;
			if( v->color == COL_WHITE ) {
				v->color = COL_GRAY;
				v->dist = u->dist + 1;
				v->p = u;
				enqueue(&q, v);
			}
			n = n->next;
		}
		u->color = COL_BLACK;
	}
	
}

int main() {
	add_edge('s', 'd'); // S
	add_edge('s', 'c');
	add_edge('s', 'a');
	add_edge('d', 'e'); // D
	add_edge('d', 'c');
	add_edge('e', 'g'); // E
	add_edge('e', 'f');
	add_edge('c', 's'); // C
	add_edge('c', 'g');
	add_edge('g', 'f'); // G

	//print_adj(vertexes['d']);
	bfs(vertexes['s']);

	char c;
	while( (c = getchar()) != EOF) {
		if( vertexes[c] != NULL ) {
			print_adj(vertexes[c]);
			printf("%d\n", vertexes[c]->dist);
		} else if (c == 10) {
		} else {
			printf("Not found\n");
		}
	}


}
