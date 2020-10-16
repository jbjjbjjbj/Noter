/* Simple regex program
 * Uses NFA trees, and follows multiple possible paths
 *
 * This is part of the tutorial in https://swtch.com/~rsc/regexp/regexp1.html
 *
 * '|' choice
 * '?' optional
 * '*' multiple
 * '+' one or more
 *
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define STATE_SPLIT 256
#define STATE_MATCH 257

#define STACK_SIZE 100

#define VIZ_ENABLE 1

typedef struct state {
    // c < 256: character matching, c >= 256 Split or Match
    unsigned short c;
    struct state *n1;
    struct state *n2;

#if VIZ_ENABLE == 1
    // Used for vizualization
    int v;
#endif
} state_t;

typedef struct stlist {
    state_t **st;
    struct stlist *next;
} stlist_t;

// Used when compiling for intermediate state machines
typedef struct {
    state_t *start;
    // Possible output states of the state machine
    stlist_t *out;
} frag_t;

state_t *st_crt(unsigned short c, state_t *n1, state_t *n2) {
    state_t *s = (state_t *) malloc(sizeof(state_t));
    assert(s);

    s->c = c;
    s->n1 = n1;
    s->n2 = n2;
#if VIZ_ENABLE == 1
    s->v = -1;
#endif
    return s;
}

stlist_t *list_crt(state_t **init) {
    stlist_t *l = (stlist_t *) malloc(sizeof(stlist_t));
    assert(l);

    l->st = init;
    l->next = NULL;
    return l;
}

// This will append b to a and return a
stlist_t *list_append(stlist_t *a, stlist_t *b) {
    stlist_t *end;
    for (end = a; end->next; end++);
    end->next = b;

    return a;
}

// Sets all pointers in list to s
void list_patch(stlist_t *l, state_t *s) {
    for ( ; l; l = l->next) {
        *l->st = s;
    }
}

void frag_init(frag_t *f, state_t *start, stlist_t *out) {
    f->start = start;
    f->out = out;
}

/*
 * Compiles a regex in the postfix notation.
 *
 * '.' for concat is added.
 *
 * a(bb)+a becomes abb.+.a.
 */
state_t *compile(char *postfix) {
    char *c;
    frag_t stack[STACK_SIZE];

    state_t *s;

    frag_t *cur = stack, *e1, *e2;
#define PUSH (cur++)
#define POP (--cur)

    for (c = postfix; *c; c++) {
        switch(*c) {
            case '.':
                e2 = POP;
                e1 = POP;
                //patch e2 on e1
                list_patch(e1->out, e2->start);
                frag_init(PUSH, e1->start, e2->out);
                break;
            case '|':
                e2 = POP;
                e1 = POP;
                s = st_crt(STATE_SPLIT, e1->start, e2->start);
                frag_init(PUSH, s, list_append(e1->out, e2->out));
                break;
            case '?':
                e1 = POP;
                s = st_crt(STATE_SPLIT, e1->start, NULL);
                frag_init(PUSH, s, list_append(e1->out, list_crt(&s->n2)));
                break;
            case '*':
                e1 = POP;
                s = st_crt(STATE_SPLIT, e1->start, NULL);
                list_patch(e1->out, s);
                frag_init(PUSH, s, list_crt(&s->n2));
                break;
            case '+':
                e1 = POP;
                s = st_crt(STATE_SPLIT, e1->start, NULL);
                list_patch(e1->out, s);
                frag_init(PUSH, e1->start, list_crt(&s->n2));
                break;
            default:
                s = st_crt(*c, NULL, NULL);
                frag_init(PUSH, s, list_crt(&s->n1));
        }
    }

    // Connect dangling ends to a matching state
    cur--;
    list_patch(cur->out, st_crt(STATE_MATCH, NULL, NULL));
    return cur->start;
}

#if VIZ_ENABLE == 1
int viz(state_t *s, int *ip) {
    if (ip == NULL) {
        // First run, print begin and end of graph
        int i = 0;

        printf("digraph G {\n");
        printf("0 [label=\"s\"]");
        viz(s, &i);
        printf("}\n");

        return i;
    }

    if (s->v != -1) {
        return s->v;
    }

    int this_i = (*ip)++;
    s->v = this_i;

    switch (s->c) {
        case STATE_SPLIT:
            printf("%d -> %d;\n", this_i, viz(s->n1, ip));
            printf("%d -> %d;\n", this_i, viz(s->n2, ip));
            break;
        case STATE_MATCH:
            printf("%d [label=\"m\"];\n", this_i);
            break;
        default:
            printf("%d -> %d [label=\"%c\"];\n", this_i, viz(s->n1, ip), s->c);
    }

    return this_i;
}
#endif

int main() {
    state_t *s = compile("c+a.de.|");
    viz(s, 0);
}
