%{
#include <stdio.h>
%}

%%
"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" { 
    printf("Mot-cle : %s\n", yytext); 
}

[a-zA-Z_][a-zA-Z0-9_]* { 
    printf("Identificateur : %s\n", yytext); 
}

[0-9]+ { 
    printf("Nombre entier : %s\n", yytext); 
}

"++"|"--"|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="|"=="|"!="|"<="|">="|"&&"|"||"|"<<"|">>"|"->"|"+"|warn"-"|"*"|"/"|"%"|"="|"<"|">"|"!"|"~"|"&"|"|"|"^"|"?"|":"|","|"."|";" { 
    printf("Operateur : %s\n", yytext); 
}

[ \t\n]+ { 
    /* Ignorer les espaces, tabulations et sauts de ligne */ 
}

. { 
    /* Ignorer ou traiter les autres caractères (parenthèses, accolades, crochets, etc.) */ 
}

%%

int main() {
    yylex();
    return 0;
}