%{
#include <stdio.h>
%}

%%
[a-zA-Z]+   { 
                if (yyleng < 10) {
                    printf("%s\n", yytext); 
                }
            }
.|\n        { /* Ignore other characters */ }
%%

int main() {
    yylex();
    return 0;
}