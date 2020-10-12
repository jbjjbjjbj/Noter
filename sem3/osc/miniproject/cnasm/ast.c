#include "ast.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static ast_node_t *create_empty_node()
{
    ast_node_t *n = malloc(sizeof(ast_node_t));
    memset(n, 0, sizeof(ast_node_t));
}

ast_node_t *insert_ctrl(enum ntype t, cond_t *c, ast_node_t *iftrue,
                        ast_node_t *iffalse)
{
    ast_node_t *n = create_empty_node();

    n->t = t;
    n->flowctrl.condition = c;
    n->flowctrl.iftrue = iftrue;
    n->flowctrl.iffalse = iffalse;

    return n;
}

ast_node_t *insert_for(char *pre, cond_t *c, char *inc, ast_node_t *stuff)
{
    ast_node_t *n = create_empty_node();

    n->t = TFOR;
    n->forloop.condition = c;
    n->forloop.pre = pre;
    n->forloop.inc = inc;
    n->forloop.stuff = stuff;

    return n;
}

ast_node_t *insert_stm(ast_node_t *stm, ast_node_t *stm_list)
{
    ast_node_t *n = create_empty_node();

    n->t = TSTM_LIST;
    n->list.children[0] = stm_list;
    n->list.children[1] = stm;

    return n;
}
ast_node_t *insert_ident(char *ident)
{
    ast_node_t *n = create_empty_node();

    n->t = TIDENT;
    n->ident = ident;

    return n;
}

cond_t *insert_cond(uint8_t cmp, char *a, char *b)
{
    cond_t *c = malloc(sizeof(cond_t));

    c->cmp = cmp;
    c->a = a;
    c->b = b;
}

void node_print(ast_node_t *node)
{
    if (!node) {
        printf("Nil");
        return;
    }
    switch (node->t) {
    case TSTM_LIST:
        printf("Stm_list(");
        node_print(node->list.children[0]);
        printf(",");
        node_print(node->list.children[1]);
        printf(")");
        break;
    case TIF:
        printf("If");
        printf("(%s %c %s) {", node->flowctrl.condition->a,
               node->flowctrl.condition->cmp, node->flowctrl.condition->b);
        node_print(node->flowctrl.iftrue);
        printf("}{");
        node_print(node->flowctrl.iffalse);
        printf("}");
        break;
    case TIDENT:
        printf("%s", node->ident);
        break;
    case TWHILE:
        printf("while");
        printf("(%s %c %s) {", node->flowctrl.condition->a,
               node->flowctrl.condition->cmp, node->flowctrl.condition->b);
        node_print(node->flowctrl.iftrue);
        printf("}");
        break;
    default:
        printf("invalid");
    }
}
