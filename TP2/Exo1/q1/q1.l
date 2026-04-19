%{
#include <stdio.h>
#include <string.h>
%}

%%
[a-zA-Z]+   { 
                if (strlen(yytext) < 10) {
                    printf("%s\n", yytext); 
                }
            }
.|\n        { /* Ignore other characters */ }
%%

int main() {
    yylex();
    return 0;
}