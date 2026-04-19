%{
#include <stdio.h>
%}

%%
[a-zA-Z]{10,} { /* Word is 10 or more letters: do nothing */ }
[a-zA-Z]+     { printf("%s\n", yytext); /* Word is < 10 letters: print it */ }
.|\n          { /* Ignore other characters */ }
%%

int main() {
    yylex();
    return 0;
}