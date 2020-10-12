#include <stdint.h>
#define HASHSIZE 100

typedef struct symnode_struct {
    char *name;
    struct symnode_struct *next;
    double value;
} symnode_t;

symnode_t *sym_insert(char *var);
symnode_t *sym_lookup(char *var);

struct symnode {
    struct symnode *next;
    char *name;
    int type;
    double value;
};

symnode_t *symbolarray[HASHSIZE];
