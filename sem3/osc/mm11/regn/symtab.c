#include "symtab.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(char *s) {
	uint32_t hv = 0;
	for( int i = 0; s[i] != '\0'; i++ ) {
		// take MSB 6 bits of hv and xors with LSB of s[i]
		uint32_t v = ( hv >> 26 ) ^ (s[i] & 0x3f);

		// Push those back on hv
		hv = (hv << 4) | v;
	}
	// Return appropriate size
	return hv % HASHSIZE;
}


symnode_t *sym_insert(char *var) {
	unsigned int index = hash(var);

	// Save old value
	symnode_t *oldSym = symbolarray[index];

	// Make new
	symbolarray[index] = malloc(sizeof(symnode_t));
	if( symbolarray[index] == NULL ) {
		// If malloc failed
		symbolarray[index] = oldSym;
		return NULL;
	}

	// Link old one
	symbolarray[index]->next = oldSym;
	symbolarray[index]->name = var;

	return symbolarray[index];
}

symnode_t *sym_lookup(char *var) {
	unsigned int index = hash(var);
	symnode_t *n = symbolarray[index];

	// Look trough list
	while(n != NULL && strcmp(n->name, var) != 0) {
		n = n->next;
	}

	return n;
}
