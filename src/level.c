#include "common.h"
#include "window.h"
#include "level.h"
#include "score.h"
#include "screen.h"

int fase = 1;

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
        file = fopen("assets/levels/Nivel1.txt","r");
        break;
    case 2:
        file = fopen("assets/levels/Nivel2.txt","r");
        break;
    case 3:
        file = fopen("assets/levels/Nivel3.txt","r");
        break;
    case 4:
        file = fopen("assets/levels/Nivel4.txt","r");
        break;
    case 5:
        file = fopen("assets/levels/Nivel5.txt","r");
        break;
    case 6:
        file = fopen("assets/levels/Nivel6.txt","r");
        break;
    default:
        file = fopen("assets/levels/Nivel1.txt","r");
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

char library[1004][TAMANHO_PALAVRA];
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

//Pilha

#define LIMITE_PILHA 5

int isEmpty(pilhaLetra *pilha){
    if(pilha->topo == NULL){
        return 1;
    }
    return 0;
}

pilhaLetra *criarpilha(){
    pilhaLetra *pilha = (pilhaLetra*)malloc(sizeof(pilhaLetra));

    if (pilha == NULL) {
        printf("Erro na alocaçao de memoria!\n");
        exit(1);
    }

    pilha->topo = NULL;
    return pilha;
}

slot *criarNo(char letra){
    slot *novoNo = (slot*)malloc(sizeof(slot));

    if (novoNo == NULL){
        printf("Erro na alocaçao de memoria!\n");
        exit(1);
    }

    novoNo->letra = letra;
    novoNo->proximo = NULL;
    return novoNo;
}

void mostrarPilhaRecursivo(slot *atual) {
    if (atual == NULL) {
        return;
    }
    // Primeiro, chama recursivamente para o próximo elemento
    mostrarPilhaRecursivo(atual->proximo);
    // Depois, imprime o elemento atual
    printf("%c", atual->letra);
}

void mostrarPilha(pilhaLetra *pilha) {
    if (isEmpty(pilha)) {
        printf(" \n");
    } else {
        mostrarPilhaRecursivo(pilha->topo);
        printf("\n");
    }
}

void push(pilhaLetra *pilha, char letra){
    int tamanhoPilha = 0;
    slot *atual = pilha->topo;

    // Conta o número de elementos na pilha
    while (atual != NULL) {
        tamanhoPilha++;
        atual = atual->proximo;
    }

    if (tamanhoPilha >= LIMITE_PILHA) {
        printf(" \n");
        return;
    }

    slot *novoNo = criarNo(letra);
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;

    printf("%c", novoNo->letra);
}

void pop(pilhaLetra *pilha){
    slot *aux;

    aux = pilha->topo;
    pilha->topo = aux->proximo;
    free(aux);
}

char* pilhaParaString(pilhaLetra *pilha) {
    // Primeiro, conta o número de elementos na pilha
    int tamanhoPilha = 0;
    slot *atual = pilha->topo;
    
    while (atual != NULL) {
        tamanhoPilha++;
        atual = atual->proximo;
    }

    // Aloca memória para a string resultante (incluindo o '\0')
    char *resultado = (char*)malloc(tamanhoPilha + 1);
    if (resultado == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }

    // Preenche a string com os caracteres da pilha, da base para o topo
    atual = pilha->topo;
    char *resultadoRev = (char*)malloc(tamanhoPilha + 1);
    int i = 0;
    
    // Armazena todos os elementos em uma string auxiliar
    while (atual != NULL) {
        resultadoRev[i++] = atual->letra;
        atual = atual->proximo;
    }
    resultadoRev[i] = '\0'; // Adiciona o terminador nulo

    // Inverte a string
    for (int j = 0; j < tamanhoPilha; j++) {
        resultado[j] = resultadoRev[tamanhoPilha - j - 1];
    }
    resultado[tamanhoPilha] = '\0'; // Termina a string corretamente

    // Libera memória da string auxiliar
    free(resultadoRev);

    return resultado;
}

void limparPilha(pilhaLetra *pilha) {
    slot *atual = pilha->topo;
    slot *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    pilha->topo = NULL;
}

// Teste das palavras

// 0 = VERMELHO
//1 = AMARELO
//2 = VERDE

void testeDeLetras(const char palavra_teste[], const char escolhida[], char ocorrencias[]) {
    // Inicializa ocorrências como "00000"
    for (int i = 0; i < 5; i++) {
        ocorrencias[i] = '0';
    }
    ocorrencias[5] = '\0';

    // Aloca os verdes
    for (int i = 0; i < 5; i++) {
        if (escolhida[i] == palavra_teste[i]) {
            ocorrencias[i] = '2';
        }
    }

    // Aloca os amarelos
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (ocorrencias[j] == '0' && ocorrencias[i] == '0' && escolhida[i] == palavra_teste[j]) {
                ocorrencias[j] = '1';
                break;
            }
        }
    }
}

int verificaVitoria(char ocorrencias[]){
        for (int i = 0; i < 5; i++) {
        if (ocorrencias[i] != '2') {
            return 0; // Se encontrar algo diferente de '2', ainda não venceu
        }
    }
    return 1; // Se percorreu tudo e só encontrou '2', venceu
}

// Jogo

void verificacao(const char* escolhida, pilhaLetra* pilha) {
    // Converte a pilha para string
    char* string = pilhaParaString(pilha);
    printf("\nPilha convertida para string: %s\n", string);

    // Verifica se a palavra está na biblioteca
    int resultado = buscarNaLibrary(string, 1004, 0, 0);
    if (resultado == 1) {
        printf("Palavra encontrada\n\n");

        // Testa as letras da palavra
        char ocorrencias[6];
        testeDeLetras(string, escolhida, ocorrencias);

        // Exibe as ocorrências
        printf("Ocorrencias: %s\n", ocorrencias);

        // Verifica se o jogador venceu
        if (verificaVitoria(ocorrencias)) {
            printf("Parabens! Voce venceu!\n");

            // Atualiza a fase atual
            if (fase < 6){
                fase++;
            } else {
                fase = 6;
            }

            // Altera a tela atual para o menu
            telaAtual = JOGO;
            atualizaTela(window); // Usa a variável global e faz o cast

            if (fase >= 5) {
                captura_tempo_final_e_calcula(&horas, &minutos, &segundos);
                printf("Tempo parou de contar\n");
            }

            if(fase < 6){
                iniciarFase();
            } else if (isInfiniteButtonClicked){
                iniciarFase();
            } else {
                telaAtual = MENU;
                atualizaTela(window);
            }
        }
    } else {
        printf("Palavra não encontrada\n\n");
    }

    // Limpa a pilha após o processamento
    limparPilha(pilha);
}

void iniciarFase(){
    if (fase < 6){
    // Lógica para iniciar o jogo
    printf("Tempo contando\n");
    captura_tempo_inicio(&horas, &minutos, &segundos);

    gerarPalavraFases(fase);
    gerarLibrary();
    printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG

    telaAtual = JOGO;
    atualizaTela(window);
    } else {
        gerarPalavraFases(fase);
        gerarLibrary();
        printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG

        telaAtual = JOGO;
        atualizaTela(window);
    }
}