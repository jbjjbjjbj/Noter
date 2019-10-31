%{
#include <math.h>
#include <string.h>
#include "regn.tab.h"
#include "ast.h"
%}

id		[a-zA-Z0-9_;]([^\n=><(){}])*
if		if[ \t]*
else	else[ \t]*
for		for[ \t]*
while	while[ \t]*

%%

{if} {return IFF;};
{else} {return EELSE;};
{for} {return FFOR;};
{while} {return WHILE;};
"(" {return LP;};
")" {return RP;};
"{" {return LCP;};
"}" {return RCP;};
"<" {yylval.cmp = CLT; return CMP;};
">" {yylval.cmp = CGT; return CMP;};
"=" {yylval.cmp = CEQ; return CMP;};
"!=" {yylval.cmp = CNEQ; return CMP;};
{id} {yylval.string = strdup(yytext);return ID;};
[1-9][0-9]* {yylval.string = yytext;return NO;};



[ \t\n] ;

.           {return yytext[0];} 

%%

// TODO match normal assembler
