%{
#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "codegen.h"

#define CLEAN_BOTH 2
#define CLEAN_DST 1

char *strconcat(char *dst, char *src, unsigned int clean) {
	size_t dstlen = strlen(dst) + 1;
	size_t srclen = strlen(src) + 1;

	// Create new duplicate
	char *new = malloc(( dstlen + srclen ) * sizeof(char));

	// Copy stuff
	memcpy(new, dst, dstlen);
	strcat(new, src);

	// Free old one
	if( clean-- ) {
		free(dst);

		if( clean ) {
			free(src);
		}
	}
	return new;
}

// Trace node

%}

%token IFF EELSE FFOR RP RCP RSP LP LCP LSP ID COLON CMP NO WHILE

%union {
	char				*string;
	struct ast_node		*node;
	struct cond			*condition;
	uint8_t				cmp;
}

%type <string>	ID 
%type <node>	statement stm_list 
%type <cmp>		CMP
%type <condition> condition

%%

program: stm_list 			{gentree(stdout, NULL, $1);printf("\n");};

stm_list: statement				{ $$ = $1; }
		| stm_list statement 	{ $$ = insert_stm($2, $1); };

condition: ID CMP ID		{ $$ = insert_cond($2, $1, $3); }
		 | ID				{ $$ = insert_cond(CNEQ, $1, "0");};

statement: ID																{$$ = insert_ident($1);}
		 | IFF LP condition RP LCP stm_list RCP								{$$ = insert_ctrl(TIF, $3, $6, NULL);}
		 | IFF LP condition RP LCP stm_list RCP	EELSE LCP stm_list RCP		{$$ = insert_ctrl(TIF, $3, $6, $10);}
		 | WHILE LP condition RP LCP stm_list RCP							{$$ = insert_ctrl(TWHILE, $3, $6, NULL);}
		 | FFOR LP ID LP condition LP ID RP LCP stm_list RCP				{$$ = insert_for($3, $5, $7, $10);};

%%


int main() {

	/*for(;;) {
		int t = yylex();
		printf("yylex: %d\n", t);
	} */

	yyparse(); 
}

