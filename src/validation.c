#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"

char library[988][TAMANHO_PALAVRA];
char aux[MAX_PALAVRAS][TAMANHO_PALAVRA];

void gerarLibrary() {
    //abre o arq
    FILE *file = fopen("assets/levels/palavras.txt", "r");
    if (file == NULL) {
        printf("\nErro ao abrir arquivo\n");
        exit(EXIT_FAILURE);
    }
    printf("\nArquivo aberto com sucesso\n");

    //aloca no auxiliar
    int i = 0;
    while (i < MAX_PALAVRAS && fgets(aux[i], TAMANHO_PALAVRA, file) != NULL) {
        aux[i][strcspn(aux[i], "\n")] = '\0'; // Remove '\n'
        i++;
    }
    fclose(file);

    //ajusta as alocações, coloca 1 palavra em cada vetor da library
    int j = 0;
    for (i = 0; i < MAX_PALAVRAS; i++) {
        if (i % 2 == 0) {
            strcpy(library[j], aux[i]);
            j++;
        }
    }
}

int buscarNaLibrary(char palavrateste[], int final, int meio, int inicio) {
    if (inicio > final) {
        return 0;
    }

    meio = inicio + (final - inicio) / 2;

    if (strcmp(palavrateste, library[meio]) == 0) {
        return 1;
    } else if (strcmp(palavrateste, library[meio]) > 0) {
        return buscarNaLibrary(palavrateste, final, meio + 1, meio + 1);
    } else {
        return buscarNaLibrary(palavrateste, meio - 1, meio - 1, inicio);
    }
}