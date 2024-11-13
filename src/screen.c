#include "common.h"
#include "screen.h"

Tela telaAtual = MENU;

// Função para desenhar o menu principal
void desenhaMenuPrincipal() {
    // Limpa o buffer com a cor preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Texto ou elementos do menu principal
    printf("MENU PRINCIPAL: Pressione 1 para Jogo, 2 para Estatísticas.\n");

    // Troca os buffers para exibir a cena
    glfwSwapBuffers(glfwGetCurrentContext());
}

// Função para desenhar a tela de jogo
void desenhaTelaJogo() {
    // Limpa o buffer com a cor preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Elementos do jogo
    printf("Jogo Iniciado!\n");

    // Troca os buffers para exibir a cena
    glfwSwapBuffers(glfwGetCurrentContext());
}

// Função para desenhar a tela de estatísticas
void desenhaTelaEstatisticas() {
    // Limpa o buffer com a cor preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Elementos das estatísticas
    printf("Estatísticas: Aqui estão as estatísticas do jogo.\n");

    // Troca os buffers para exibir a cena
    glfwSwapBuffers(glfwGetCurrentContext());
}