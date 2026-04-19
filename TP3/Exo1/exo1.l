%{
#include <stdio.h>
%}

%%

"<?xml?>"               { fprintf(yyout, "p"); }
"</"[a-zA-Z0-9_]+">"    { fprintf(yyout, "f"); }
"<"[a-zA-Z0-9_]+">"     { fprintf(yyout, "o"); }
[ \t\n\r]+              { /* Ignorer les espaces, tabulations et sauts de ligne */ }
[^<>\n\t\r ]+([ \t\n\r]+[^<>\n\t\r ]+)* { fprintf(yyout, "t"); }
.                       { /* Ignorer tout autre caractère inattendu */ }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    }
    if (argc > 2) {
        yyout = fopen(argv[2], "w");
    } else {
        yyout = stdout; 
    }
    
    yylex();
    
    return 0;
}