#ifndef SCREEN_H
#define SCREEN_H

// Definição do enum para controlar o estado do programa
typedef enum {
    MENU,         // Tela principal do menu
    JOGO,         // Tela do jogo
    ESTATISTICAS  // Tela de estatísticas
} Tela;

// Variável global para armazenar o estado atual da tela
extern Tela telaAtual;

// Declaração das funções de desenho das telas
void desenhaMenuPrincipal();
void desenhaTelaJogo();
void desenhaTelaEstatisticas();

#endif
