#ifndef LEVEL_H
#define LEVEL_H

#define MAX_PALAVRAS 1976
#define MAX_PALAVRASDASFASES 20
#define TAMANHO_PALAVRA 6

// Validação da palavra
char gerarPalavraFases(int fase);
void gerarLibrary();
int buscarNaLibrary(char palavrateste[], int final, int meio, int inicio);

// Pilha

//Cria a estrutura do nó
typedef struct slot{
    char letra;
    struct slot *proximo;
}slot;

//Cria a estrutura da pilha
typedef struct{
    slot *topo;
}pilhaLetra;

// Declarações da pilha
int isEmpty(pilhaLetra *pilha);
pilhaLetra *criarpilha();
slot *criarNo(char letra);
void mostrarPilha(pilhaLetra *pilha);
void push(pilhaLetra *pilha, char letra);
void pop(pilhaLetra *pilha);
char* pilhaParaString(pilhaLetra *pilha);
void limparPilha(pilhaLetra *pilha);

// Teste das palavras
void testeDeLetras(const char palavra_teste[], const char escolhida[], char ocorrencias[]);
int verificaVitoria(char ocorrencias[]);

// Jogo
void verificacao(const char* escolhida, pilhaLetra* pilha);
void iniciarFase();

#endif