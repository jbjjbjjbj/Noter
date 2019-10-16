%{

#include <stdio.h>

%}

ting		(a|b)abcd

%%

{ting}		{ printf("Fandt ting %s\n", yytext); return 1; }
.			{ printf("Meh"); }

%%

int main(void) {

	printf("yylex: %d\n", yylex());

	return 0;
	
}
