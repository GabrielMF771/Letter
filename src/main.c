#include "common.h"
#include "screen.h"

// Declaração de funções
void initOpenGL(GLFWwindow** window);
void desenhaQuadrado();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Função para configurar a janela e o contexto OpenGL
void initOpenGL(GLFWwindow** window) {
    // Inicializa o GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Falha ao inicializar o GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Cria a janela GLFW
    *window = glfwCreateWindow(800, 600, "Jogo", NULL, NULL);
    if (!*window) {
        fprintf(stderr, "Falha ao criar a janela GLFW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Faz o contexto da janela atual
    glfwMakeContextCurrent(*window);

    // Inicializa o GLAD para gerenciar funções do OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Falha ao inicializar o GLAD\n");
        exit(EXIT_FAILURE);
    }
}

// Função pra deixar tudo no centro da tela
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

// Função de carregar input
void processInput(GLFWwindow* window){

    //Botão de fechar se o "esc" for clicado
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        // Comando que a Janela deve fechar
        glfwSetWindowShouldClose(window, 1);
    }
}

// Função retorno teclas do teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) {
            if (telaAtual == MENU) {
                telaAtual = JOGO;  // Vai para a tela de jogo
                printf("Tela de Jogo\n");
            }
        }
        if (key == GLFW_KEY_2) {
            if (telaAtual == MENU) {
                telaAtual = ESTATISTICAS;  // Vai para a tela de estatísticas
                printf("Tela de Estatísticas\n");
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
        processInput(window);
        glfwPollEvents();

        // Desenha a tela com base no estado atual
        if (telaAtual == MENU) {
            desenhaMenuPrincipal();
        } else if (telaAtual == JOGO) {
            desenhaTelaJogo();
        } else if (telaAtual == ESTATISTICAS) {
            desenhaTelaEstatisticas();
        }

        glfwSetKeyCallback(window, key_callback);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}