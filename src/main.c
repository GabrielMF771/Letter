#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include "common.h"
#include "window.h"
#include "screen.h"
#include "level.h"
#include "score.h"

// Declaração de funções
void initOpenGL(GLFWwindow** window);
void desenhaQuadrado(GLFWwindow** window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void liberaRecursos();

const GLuint WIDTH = 900, HEIGHT = 900;

// Declaração das variáveis
pilhaLetra* pilha;
char *string;
GLFWwindow* window = NULL;

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
        switch (key) {
            case GLFW_KEY_UP:
                fase = (fase >= 6) ? 1 : 6;
                printf("\nFase alterada para %d\n", fase);
                isStartButtonClicked = 0;
                break;

            case GLFW_KEY_ESCAPE:
                if (telaAtual != MENU) {
                    telaAtual = MENU;  // Vai para a tela de menu
                    atualizaTela(window);
                    printf("Menu Principal\n");
                } else {
                    glfwSetWindowShouldClose(window, 1);
                }
                break;

            case GLFW_KEY_ENTER:
                if (telaAtual == JOGO) {
                    verificacao(escolhida, pilha);
                    break;
                }

            case GLFW_KEY_BACKSPACE:
                if (telaAtual == JOGO) {
                    if(isEmpty(pilha)){
                        break;
                    }
                    pop(pilha);  // Remove o elemento do topo da pilha
                    mostrarPilha(pilha);
                    backspace(1);
                }
                break;

            default:
                // Verifica se a tecla é uma letra (GLFW_KEY_A até GLFW_KEY_Z)
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z && telaAtual == JOGO) {
                    // Converte a tecla para minúscula
                    char letra = tolower('A' + (key - GLFW_KEY_A));
                    // Adiciona a letra na pilha
                    push(pilha, letra);
                }
                break;
        }
    }
}

void liberaRecursos(){
    liberaTexturasMenu();
    liberaTexturasJogo();
}

int main() {
    // Inicializa OpenGL
    initOpenGL(&window);

    // Função pra deixar tudo no centro da tela
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    carregaTexturasMenu();
    carregaTexturasJogo();
    pilha = criarpilha();

    while (!glfwWindowShouldClose(window)) {
        atualizaTela(window);

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

    liberaRecursos();
    free(pilha);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}