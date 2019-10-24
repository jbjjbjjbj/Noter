%{
#include <math.h>
#include <string.h>
#include "regn.tab.h"
%}

realtal      ([0-9]+|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)?
op_log		 log
op_exp		 exp
op_sqrt		 sqrt

%%
{realtal}      {yylval.dval = atof(yytext); 
                return TAL;}
{op_log}	   {return LOG;}
{op_exp}	   {return EXP;}
{op_sqrt}	   {return SQRT;}

[ \t] ;


'$'            {return 0;} 

\n|.           {return yytext[0];} 

%%

