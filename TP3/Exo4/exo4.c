#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000

// La pile
char stack[STACK_SIZE];
int top = -1;

void push(char c) {
    if (top >= STACK_SIZE - 1) {
        printf("Erreur : débordement de la pile\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top < 0) {
        //erreur
        printf("document xml mal formé\n");
        exit(1);
    }
    return stack[top--];
}

void error() {
    printf("document xml mal formé\n");
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Veuillez fournir un fichier contenant la séquence lexicale.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    // Initialisation de la pile d'analyse
    push('$'); 
    push('S'); 

    // Lecture du premier caractère (symbole d'avance)
    char a = fgetc(file);
    while (a == ' ' || a == '\n' || a == '\r' || a == '\t') a = fgetc(file);
    if (a == EOF) a = '$';

    // Boucle d'analyse dirigée par la table LL(1)
    while (top >= 0) {
        char X = pop();

        // Si X est un terminal (ou la fin de chaîne)
        if (X == 'p' || X == 'o' || X == 't' || X == 'f' || X == '$') {
            if (X == a) {
                // Correspondance : on avance dans le fichier
                if (a != '$') {
                    a = fgetc(file);
                    while (a == ' ' || a == '\n' || a == '\r' || a == '\t') a = fgetc(file);
                    if (a == EOF) a = '$';
                }
            } else {
                error(); // Les terminaux ne correspondent pas
            }
        } 
        // Si X est le non-terminal S
        else if (X == 'S') {
            if (a == 'p') {
                // Table(S, p) = S -> p o E f
                // Empiler à l'envers : f, E, o, p
                push('f');
                push('E');
                push('o');
                push('p');
            } else {
                error();
            }
        } 
        // Si X est le non-terminal E
        else if (X == 'E') {
            if (a == 'o') {
                // Table(E, o) = E -> o E f E
                // Empiler à l'envers : E, f, E, o
                push('E');
                push('f');
                push('E');
                push('o');
            } else if (a == 't') {
                // Table(E, t) = E -> t
                push('t');
            } else if (a == 'f' || a == '$') {
                // Table(E, f) = E -> eps / Table(E, $) = E -> eps
                // Ne rien empiler (règle epsilon)
            } else {
                error();
            }
        } 
        // Symbole non reconnu
        else {
            error();
        }
    }

    // Si on arrive ici, la pile est vide et tout s'est bien passé
    printf("document xml bien formé\n");

    fclose(file);
    return 0;
}