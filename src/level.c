#include "common.h"
#include "window.h"
#include "level.h"
#include "score.h"
#include "screen.h"

int fase = 1;

//vetor q vai armazenar todas as palavras em ordem
char plvrDaFase[10][TAMANHO_PALAVRA];
char plvrDaFase6[2145][TAMANHO_PALAVRA];
char auxDaFase[MAX_PALAVRASDASFASES][TAMANHO_PALAVRA];
char auxDaFase6[MAX_PALAVRASDAFASE6][TAMANHO_PALAVRA];
//var q armazena a palavra da fase atual
char escolhida[6];

// Variavel para mostrar a resposta da fase
int mostrarResposta = 0;

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
    }

    if(fase == 6){
        // Aloca no auxiliar
        int i = 0;
        while(fgets(auxDaFase6[i], TAMANHO_PALAVRA, file) != NULL && i < MAX_PALAVRASDAFASE6){
            auxDaFase6[i][strcspn(auxDaFase6[i], "\n")] = '\0';  // Remove o '\n' no final
            i++;
        }

        // Ajusta as alocações, coloca 1 palavra em cada vetor da library
        int j = 0;
        for(i = 0; i < MAX_PALAVRASDAFASE6; i++){
            if(i % 2 == 0){
                strcpy(plvrDaFase6[j], auxDaFase6[i]);
                j++;
            }
        }

        srand(time(NULL));
        strcpy(escolhida, plvrDaFase6[rand() % j]); // Garante que a palavra escolhida está dentro do vetor preenchido
    } else {
        //aloca no auxiliar
        int i = 0;
        while(fgets(auxDaFase[i], TAMANHO_PALAVRA, file)!= NULL && i < MAX_PALAVRASDASFASES){
            auxDaFase[i][strcspn(auxDaFase[i], "\n")] = '\0';  // Remove o '\n' no final
            i++;
        }

        // Ajusta as alocações, coloca 1 palavra em cada vetor da library
        int j = 0;
        for(i = 0; i < MAX_PALAVRASDASFASES; i++){
            if(i % 2 == 0){
                strcpy(plvrDaFase[j], auxDaFase[i]);
                j++;
            }
        }

        // Escolhendo a palavra
        srand(time(NULL));
        strcpy(escolhida, plvrDaFase[rand() % j]);  // Garante que a palavra escolhida está dentro do vetor preenchido
    }
}

char library[1073][TAMANHO_PALAVRA];
char aux[MAX_PALAVRAS][TAMANHO_PALAVRA];

void gerarLibrary() {
    //abre o arq
    FILE *file = fopen("assets/levels/palavras.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir txt da library\n");
        exit(EXIT_FAILURE);
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

int indiceLinha = 0;
int indiceSlot = 0;

void push(pilhaLetra *pilha, char letra){
    indiceLinha = linha_atual;
    int tamanhoPilha = 0;
    slot *atual = pilha->topo;

    // Conta o número de elementos na pilha
    while (atual != NULL) {
        tamanhoPilha++;
        atual = atual->proximo;
    }

    slot *novoNo = criarNo(letra);
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;

    indiceSlot = tamanhoPilha;
    linhas[indiceLinha].letra[indiceSlot] = letra;
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

char ocorrencias[6] = "00000";

void testeDeLetras(const char palavra_teste[], const char escolhida[]) {
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

int tentativas = 6; // Inicializa as tentativas

void verificacao(const char* escolhida, pilhaLetra* pilha) {
    // Converte a pilha para string
    char* string = pilhaParaString(pilha);

    // Verifica se a palavra está na biblioteca
    int resultado = buscarNaLibrary(string, 1073, 0, 0);
    
    if (resultado == 1) {  // Se a palavra for encontrada
        printf("Palavra encontrada\n\n");
        tentativas--;

        // Testa as letras da palavra
        testeDeLetras(string, escolhida);

        atualizarOcorrencias();  // Redesenha os slots com base nas novas ocorrências

        // Exibe as ocorrências
        printf("Ocorrencias: %s\n", ocorrencias);

        // Exibe as tentativas restantes
        printf("Tentativas restantes %d\n", tentativas);

        // Verifica se o jogador venceu
        if (verificaVitoria(ocorrencias)) {
            printf("Parabens! Voce venceu!\n");

            // Atualiza a fase atual
            if (fase < 6) {
                fase++;
            } else {
                fase = 6;
            }

            // Resetando a string ocorrencias
            for (int i = 0; i < 6; i++) {
                ocorrencias[i] = '0'; // Resetando as ocorrências
            }

            if (fase < 6) {
                iniciarFase();
            } else if (isInfiniteButtonClicked) {
                iniciarFase();
            } else {
                captura_tempo_final_e_calcula(&horas, &minutos, &segundos);
                printf("Tempo parou de contar\n");
                escreverArquivoScore(horas, minutos, segundos);
                
                // Desenhar a tela de vitória
                telaAtual = VITORIA;
                atualizaTela(window);
            }
            // Limpa a pilha após o processamento
            limparPilha(pilha);
            return;
        }
    } else {
        printf("Palavra não encontrada\n\n");
        backspace(5);

        // Se a palavra não for encontrada, não decrementa as tentativas
        printf("Tentativas restantes: %d\n", tentativas);
    }

    // Se não houver tentativas restantes, o jogador perde
        if (tentativas == 0 && !verificaVitoria(ocorrencias)) {
            printf("Voce perdeu! O jogo esta sendo reiniciado.\n");
            tentativas = 6; // Reseta o número de tentativas
            fase = 1; // Reseta a fase

            // Desenhar a tela de derrota
            telaAtual = DERROTA;
            atualizaTela(window);
        }

    // Limpa a pilha após o processamento
    limparPilha(pilha);
}

void iniciarFase() {
    tentativas = 6;
    if (fase == 1){
        printf("Tempo contando\n");
        captura_tempo_inicio(&horas, &minutos, &segundos);
    }

    if (fase < 6) {
        // Lógica para iniciar o jogo
        gerarPalavraFases(fase);
        gerarLibrary();

        if (mostrarResposta == 1){
            printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG
        }

        // Resetando as ocorrências e as linhas
        linha_atual = 0; // Resetando a linha atual
        memset(linhas, 0, sizeof(linhas)); // Limpa as linhas

        // Redesenha os slots
        desenharSlots();

        telaAtual = JOGO;
        atualizaTela(window);
    } else {
        gerarPalavraFases(fase);
        gerarLibrary();
        
        if (mostrarResposta == 1){
            printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG
        }

        // Resetando as ocorrências e as linhas
        linha_atual = 0;  // Resetando a linha atual
        memset(linhas, 0, sizeof(linhas));  // Limpa as linhas

        // Redesenha os slots
        desenharSlots();

        telaAtual = JOGO;
        atualizaTela(window);
    }
}