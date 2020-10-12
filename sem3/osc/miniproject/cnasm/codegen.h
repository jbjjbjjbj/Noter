
#ifndef CODEGEN_HEADER
#define CODEGEN_HEADER

#include <stdio.h>
#include "ast.h"

struct genctx {
    unsigned int nested;
};

void gentree(FILE *f, struct genctx *ctx, ast_node_t *n);

#endif
