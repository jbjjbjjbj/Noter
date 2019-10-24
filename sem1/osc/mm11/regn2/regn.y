%{
#include <stdio.h>
#include <math.h>
#include <string.h>
%}

%union {
	double          dval;
}

%token <dval> TAL
%token LOG EXP SQRT

%left '-' '+'
%left LOG EXP SQRT
%left '*' '/'
%right UMINUS

%type <dval> expression

%%

statement_list: statement '\n'
	  | statement_list statement '\n' ;

statement:  expression					{;};

expression: expression '+' expression   {printf("sum \n");}
	  | expression '-' expression		{printf("sub \n");}
	  | expression '*' expression		{printf("mul \n");}
	  | expression '/' expression		{if ($3 == 0.0) 
                                           yyerror("divide dy zero");
                                         else printf("div \n");}
	  | '-' expression %prec UMINUS		{printf("neg \n");}
	  | '(' expression ')'				{;}
	  | LOG expression					{printf("log \n");}
	  | EXP expression					{printf("exp \n");}
	  | SQRT expression					{printf("sqrt \n");}
          | TAL                         {printf("load %f \n", $$);};
%%

int main()
{ 
  yyparse(); 
}

