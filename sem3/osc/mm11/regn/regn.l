%{
#include <math.h>
#include <string.h>
#include "symtab.h"
#include "regn.tab.h"
%}

realtal      ([0-9]+|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)?
var_begin	 let
op_log		 log
op_exp		 exp
op_sqrt		 sqrt
var			 [A-Za-z][A-Za-z0-9]*

%%
{realtal}      {yylval.dval = atof(yytext); 
                return TAL;}
{var_begin}	   {return VAR_BEGIN;}
{op_log}	   {return LOG;}
{op_exp}	   {return EXP;}
{op_sqrt}	   {return SQRT;}

{var}		   {yylval.string = strdup(yytext); return VAR;}

[ \t] ;


'$'            {return 0;} 

\n|.           {return yytext[0];} 

%%

void init_sym()
{
	int  i;
	for (i = 0; i < HASHSIZE; i++)
		symbolarray[i] = NULL;
}

