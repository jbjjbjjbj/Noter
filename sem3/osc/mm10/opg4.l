%{

#include <stdio.h>
#include <stdint.h>

#define BEGIN_T 1
#define END_T 2
#define NUM_T 3
#define VAR_T 4
#define HASHSIZE 100

typedef struct symnode_struct {
	struct symnode_struct *next;
	char *name;
} symnode_t;

symnode_t *sym_insert(char *var);
symnode_t *sym_lookup(char *var);

%}

VAR			[a-zA-Z][a-zA-Z\_\-0-9]*
TAL			[0-9]+

%%

begin		{printf("Found a BEGIN\n"); return BEGIN_T;}
end			{printf("Found a END\n"); return END_T;}
{VAR}		{printf("Found a variable %s\n", yytext); 
				if( !sym_lookup(yytext) ) { 
					printf("Not found inserting\n");
					sym_insert(yytext);
				}
				return VAR_T;}
{TAL}		{printf("Found a number %d\n", strtol(yytext, NULL, 10)); return NUM_T;}

%%

symnode_t *symlist[HASHSIZE];

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
	symnode_t *oldSym = symlist[index];

	// Make new
	symlist[index] = malloc(sizeof(symnode_t));
	if( symlist[index] == NULL ) {
		// If malloc failed
		symlist[index] = oldSym;
		return NULL;
	}

	// Link old one
	symlist[index]->next = oldSym;
	symlist[index]->name = var;

	return symlist[index];
}

symnode_t *sym_lookup(char *var) {
	unsigned int index = hash(var);
	symnode_t *n = symlist[index];

	// Look trough list
	while(n != NULL && strcmp(n->name, var) != 0) {
		n = n->next;
	}

	return n;
}


int main(void) {

	for(;;) {
		int t = yylex();
		printf("yylex: %d\n", t);
		if( t == END_T ) {
			break;
		}
	}

	return 0;
	
}
