%{
#include <stdio.h>
#include <math.h>
#include "symtab.h"
#include <string.h>
%}

%union {
	char           *string;
	double          dval;
}

%token <string> VAR
%token <dval> TAL
%token LOG EXP SQRT VAR_BEGIN

%left '-' '+'
%right LOG EXP SQRT
%left '*' '/'
%right UMINUS

%type <dval> expression

%%

statement_list: statement '\n'
	  | statement_list statement '\n' ;

statement:  expression					{printf("= %f\n",$1);}
	  | VAR_BEGIN VAR '=' expression	{symnode_t *n = sym_lookup($2);
										 if( !n ) {n = sym_insert($2); }
										 n->value = $4;};

expression: expression '+' expression   {$$ = $1 + $3;}
	  | expression '-' expression   {$$ = $1 - $3;}
	  | expression '*' expression   {$$ = $1 * $3;}
	  | expression '/' expression   {if ($3 == 0.0) 
                                           yyerror("divide dy zero");
                                         else $$ = $1 / $3;}
	  | '-' expression %prec UMINUS {$$ =  - $2;}
	  | '(' expression ')'          {$$= $2;}
	  | LOG expression				{$$ = log($2);}
	  | EXP expression				{$$ = exp($2);}
	  | SQRT expression				{$$ = sqrt($2);}
          | TAL                         {$$ = $1;}
	  | VAR							{symnode_t *n = sym_lookup($1);
									 if( !n ) { yyerror("Var not found"); } else { $$ = n->value;} };
%%

int main()
{ 
  yyparse(); 
}

