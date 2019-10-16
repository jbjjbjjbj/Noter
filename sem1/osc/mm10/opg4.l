%{

#include <stdio.h>
#include <stdint.h>

#define BEGIN_T 1
#define END_T 2
#define NUM_T 3
#define VAR_T 4
#define HASHSIZE 100

%}

VAR			[a-zA-Z][a-zA-Z\_\-0-9]*
TAL			[0-9]+

%%

begin		{printf("Found a BEGIN\n"); return BEGIN_T;}
end			{printf("Found a END\n"); return END_T;}
{VAR}		{printf("Found a variable %s\n", yytext); return VAR_T;}
{TAL}		{printf("Found a number %d\n", strtol(yytext, NULL, 10)); return NUM_T;}

%%

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

int main(void) {

	char str[100];
	while( fgets(str, 100, stdin) ) {
		printf("%s: %d\n", str, hash(str));
	}

	return 0;

	for(;;) {
		int t = yylex();
		printf("yylex: %d\n", t);
		if( t == END_T ) {
			break;
		}
	}

	return 0;
	
}
