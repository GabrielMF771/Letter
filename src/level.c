#include "common.h"
#include "level.h"

int fase = 2;

//vetor q vai armazenar todas as palavras em ordem
char plvrDaFase[9][TAMANHO_PALAVRA];
char auxDaFase[MAX_PALAVRASDASFASES][TAMANHO_PALAVRA];
//var q armazena a palavra da fase atual
char escolhida[6];

//recebe o numero da fase
char gerarPalavraFases(int fase){
    FILE *file;
    //escolhe o txt de acordo com a fase
    switch(fase){
    case 1:
        file = fopen("assets/levels/primeiroNivel.txt","r");
        break;
    case 2:
        file = fopen("assets/levels/segundoNivel.txt","r");
        break;
    case 3:
        file = fopen("assets/levels/terceiroNivel.txt","r");
        break;
    case 4:
        file = fopen("assets/levels/quartoNivel.txt","r");
        break;
    case 5:
        file = fopen("assets/levels/quintoNivel.txt","r");
        break;
    default:
        file = fopen("assets/levels/primeiroNivel.txt","r");
        break;
    }

    if(file == NULL){
        printf("Erro ao abrir txt da fase\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Txt da fase aberto com sucesso\n");
    }

    //aloca no auxiliar
    int i = 0;
    while(fgets(auxDaFase[i],TAMANHO_PALAVRA,file)!= NULL && i < MAX_PALAVRASDASFASES){
            i++;
    }

    //ajusta as alocações, coloca 1 palavra em cada vetor da library
    int j =0;
    for(i = 0; i <20; i++){
        if(i %2 == 0){
    strcpy(plvrDaFase[j], auxDaFase[i]);
        j++;
        }
    }

    //escolhendo a palavra - var "escolhida" é global e vai ser usada em todas as fases
    srand(time(NULL));
    strcpy(escolhida,plvrDaFase[(rand())%10]);

}

char library[988][TAMANHO_PALAVRA];
char aux[MAX_PALAVRAS][TAMANHO_PALAVRA];

void gerarLibrary() {
    //abre o arq
    FILE *file = fopen("assets/levels/palavras.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir txt da library\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Txt da library aberto com sucesso\n");
    }

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