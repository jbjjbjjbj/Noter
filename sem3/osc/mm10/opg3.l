%{

#include <stdio.h>

#define BEGIN_T 1
#define END_T 2
#define NUM_T 3
#define VAR_T 4

%}

VAR			[a-zA-Z][a-zA-Z\_\-0-9]*
TAL			[0-9]+

%%

begin		{printf("Found a BEGIN\n"); return BEGIN_T;}
end			{printf("Found a END\n"); return END_T;}
{VAR}		{printf("Found a variable %s\n", yytext); return VAR_T;}
{TAL}		{printf("Found a number %d\n", strtol(yytext, NULL, 10)); return NUM_T;}

%%

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
