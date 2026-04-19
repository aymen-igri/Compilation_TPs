#include <stdio.h>
#include <stdlib.h>

char lookahead;
FILE *file;

void S();
void E();

void error() {
    printf("document xml mal formé\n");
    exit(1);
}

void match(char expected) {
    if (lookahead == expected) {
        lookahead = fgetc(file);
    } else {
        error();
    }
}

// Fonction pour le non-terminal E
void E() {
    if (lookahead == 'o') {
        // Règle: E -> o E f E
        match('o');
        E();
        match('f');
        E();
    } else if (lookahead == 't') {
        // Règle: E -> t
        match('t');
    } else if (lookahead == 'f' || lookahead == EOF || lookahead == '\n' || lookahead == '\r') {
        // Règle: E -> epsilon (car FOLLOW(E) = {f, $})
        return;
    } else {
        error();
    }
}

// Fonction pour l'axiome S
void S() {
    if (lookahead == 'p') {
        match('p');
        match('o');
        E();
        match('f');
    } else {
        error();
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Veuillez fournir un fichier contenant la séquence lexicale.\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    // Lecture du premier caractère
    lookahead = fgetc(file);
    
    // Lancement l'analyse par l'axiome
    S();

    // Ignorer les éventuels sauts de ligne ou espaces à la fin du fichier
    while (lookahead == ' ' || lookahead == '\n' || lookahead == '\r') {
        lookahead = fgetc(file);
    }

    // Si on a terminé l'analyse et qu'on est bien à la fin du fichier ($)
    if (lookahead == EOF) {
        printf("document xml bien formé\n");
    } else {
        error();
    }

    fclose(file);
    return 0;
}