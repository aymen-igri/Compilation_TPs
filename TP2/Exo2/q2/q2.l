%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[ACGT][0-9]+ { 
                char c = yytext[0];
                int count = atoi(yytext + 1);
                
                for (int i = 0; i < count; i++) {
                    printf("%c", c);
                }
             }
[ACGT]       { 
                printf("%c", yytext[0]); 
             }
\n           { printf("\n"); }
.
%%

int main() {
    yylex();
    return 0;
}