#include "codegen.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"

static void gencondjmp(FILE *f, cond_t *c, bool neg)
{
    uint8_t cmp = neg ? c->cmp ^ 0x80 : c->cmp;
    fprintf(f, "cmp %s %s\n", c->a, c->b);
    switch (cmp) {
    case CEQ:
        fprintf(f, "je ");
        break;
    case CNEQ:
        fprintf(f, "jne ");
        break;
    case CGT:
        fprintf(f, "jg ");
        break;
    case CLT:
        fprintf(f, "jl ");
        break;
    case CLEQ:
        fprintf(f, "jle ");
        break;
    case CGEQ:
        fprintf(f, "jge ");
        break;
    default:
        fprintf(stderr, "Invalid cmp type %x", cmp);
        fprintf(f, "jmp ");
    }
}

static void genif(FILE *f, struct genctx *ctx, ast_node_t *n)
{
    bool doElse = n->flowctrl.iffalse;
    // Create conditional jump
    gencondjmp(f, n->flowctrl.condition, true);
    if (doElse) {
        fprintf(f, "else_%d\n", ctx->nested);
    } else {
        fprintf(f, "end_%d\n", ctx->nested);
    }

    struct genctx octx = { ctx->nested + 1 };
    // Paste code
    gentree(f, &octx, n->flowctrl.iftrue);

    // Do else
    if (doElse) {
        fprintf(f, "jmp end_%d\n", ctx->nested);
        fprintf(f, "else_%d:\n", ctx->nested);
        gentree(f, &octx, n->flowctrl.iffalse);
    }

    // End block
    fprintf(f, "end_%d:\n", ctx->nested);
}

static void genwhile(FILE *f, struct genctx *ctx, ast_node_t *n)
{
    // Create loop label
    fprintf(f, "loop_%d:\n", ctx->nested);

    // Create conditional jump
    gencondjmp(f, n->flowctrl.condition, true);
    fprintf(f, "end_%d\n", ctx->nested);

    struct genctx octx = { ctx->nested + 1 };
    // Paste code
    gentree(f, &octx, n->flowctrl.iftrue);

    // Jump to start
    fprintf(f, "jmp loop_%d\n", ctx->nested);

    // End block
    fprintf(f, "end_%d:\n", ctx->nested);
}

static void genfor(FILE *f, struct genctx *ctx, ast_node_t *n)
{
    // Do pre stuff
    fprintf(f, "%s\n", n->forloop.pre);

    // Create loop label
    fprintf(f, "loop_%d:\n", ctx->nested);

    // Create conditional jump
    gencondjmp(f, n->flowctrl.condition, true);
    fprintf(f, "end_%d\n", ctx->nested);

    struct genctx octx = { ctx->nested + 1 };
    // Paste code
    gentree(f, &octx, n->forloop.stuff);

    // Do inc stuff
    fprintf(f, "%s\n", n->forloop.inc);
    // Jump to start
    fprintf(f, "jmp loop_%d\n", ctx->nested);

    // End block
    fprintf(f, "end_%d:\n", ctx->nested);
}

void gentree(FILE *f, struct genctx *ctx, ast_node_t *n)
{
    if (!n) {
        return;
    }
    if (ctx == NULL) {
        ctx = malloc(sizeof(struct genctx));
        ctx->nested = 0;
    }
    switch (n->t) {
    case TSTM_LIST:
        gentree(f, ctx, n->list.children[0]);
        gentree(f, ctx, n->list.children[1]);
        break;
    case TIF:
        genif(f, ctx, n);
        break;
    case TIDENT:
        fprintf(f, "%s\n", n->ident);
        break;
    case TFOR:
        genfor(f, ctx, n);
        break;
    case TWHILE:
        genwhile(f, ctx, n);
        break;
    default:
        return;
    }
}
