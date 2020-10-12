#ifndef AST_HEADER
#define AST_HEADER

#include <stdbool.h>
#include <stdint.h>

#define CEQ 0x10
#define CNEQ CEQ ^ 0x80
#define CGT 0x20
#define CLT 0x30
#define CLEQ CGT ^ 0x80
#define CGEQ CLT ^ 0x80

enum ntype { TSTM_LIST, TIF, TFOR, TIDENT, TWHILE };

typedef struct cond {
    uint8_t cmp;
    char *a;
    char *b;
} cond_t;

typedef struct ast_node {
    enum ntype t;
    // Dependent on type
    union {
        struct {
            cond_t *condition;
            struct ast_node *iftrue;
            struct ast_node *iffalse;
        } flowctrl;
        struct {
            cond_t *condition;
            char *pre;
            char *inc;
            struct ast_node *stuff;
        } forloop;
        char *ident;
        struct {
            struct ast_node *children[2];
        } list;
    };
} ast_node_t;

ast_node_t *insert_ctrl(enum ntype t, cond_t *c, ast_node_t *iftrue,
                        ast_node_t *iffalse);
ast_node_t *insert_stm(ast_node_t *stm, ast_node_t *stm_list);
ast_node_t *insert_ident(char *ident);
ast_node_t *insert_for(char *pre, cond_t *c, char *inc, ast_node_t *stuff);

cond_t *insert_cond(uint8_t cmp, char *a, char *b);

void node_print(ast_node_t *node);

#endif
