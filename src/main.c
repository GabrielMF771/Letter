#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include "common.h"
#include "screen.h"
#include "level.h"

// Declaração de funções
void initOpenGL(GLFWwindow** window);
void desenhaQuadrado(GLFWwindow** window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const GLuint WIDTH = 900, HEIGHT = 900;

// Função para configurar a janela e o contexto OpenGL
void initOpenGL(GLFWwindow** window) {
    // Inicializa o GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Falha ao inicializar o GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Cria a janela GLFW
    *window = glfwCreateWindow(WIDTH, HEIGHT, "Letter", NULL, NULL);
    if (!*window) {
        fprintf(stderr, "Falha ao criar a janela GLFW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Faz o contexto da janela atual
    glfwMakeContextCurrent(*window);

    // Define limites fixos para o tamanho da janela (largura, altura mínima e máxima)
    glfwSetWindowSizeLimits(*window, WIDTH, HEIGHT, WIDTH, HEIGHT);

    // Inicializa o GLAD para gerenciar funções do OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Falha ao inicializar o GLAD\n");
        exit(EXIT_FAILURE);
    }

    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, WIDTH, HEIGHT);
}

// Função pra deixar tudo no centro da tela
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

// Função retorno teclas do teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) {
            if (telaAtual == MENU) {
                telaAtual = JOGO;  // Vai para a tela de jogo
                desenhaTelaJogo(window);
            }
        }
        if (key == GLFW_KEY_2) {
            if (telaAtual == MENU) {
                telaAtual = ESTATISTICAS;  // Vai para a tela de estatísticas
                desenhaTelaEstatisticas(window);
            }
        }
        if (key == GLFW_KEY_LEFT_BRACKET) {
            if(fase >= 6){
                fase = 1;
                printf("Fase alterada para 1\n");
            } else {
                fase = 6;
                printf("Fase alterada para 6\n");
            }
        }
        if (key == GLFW_KEY_ESCAPE){
            if(telaAtual != MENU) {
                telaAtual = MENU;  // Vai para a tela de menu
                atualizaTela(window);
                printf("Menu Principal\n");
            } else {
                glfwSetWindowShouldClose(window, 1);
            }
        }
    }
}

int main() {
    GLFWwindow* window;

    // Inicializa OpenGL
    initOpenGL(&window);

    // Função pra deixar tudo no centro da tela
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Desenha a tela com base no estado atual
        if (telaAtual == MENU) {
            desenhaMenuPrincipal(window);
        } else if (telaAtual == JOGO) {
            desenhaTelaJogo(window);
        } else if (telaAtual == ESTATISTICAS) {
            desenhaTelaEstatisticas(window);
        }

        glfwSetKeyCallback(window, key_callback);
    }

    glDeleteTextures(1, &startButtonTexture);
    glDeleteTextures(1, &statsButtonTexture);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}