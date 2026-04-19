%{
#include <stdio.h>
%}

%%
A+|C+|G+|T+ { 
                if (yyleng == 1) {
                    printf("%c", yytext[0]);
                } 
                else {
                    printf("%c%d", yytext[0], yyleng);
                }
            }
\n          { printf("\n"); }
.
%%

int main() {
    yylex();
    return 0;
}