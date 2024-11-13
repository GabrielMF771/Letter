#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Configura a visão da janela (viewport)
    glViewport(0, 0, 800, 600);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        printf("Jogo iniciado\n");
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        printf("Mostrando estatisticas\n");
}

void desenhaQuadrado() {
    // Limpa o buffer com a cor preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o quadrado usando GL_QUADS
    glBegin(GL_QUADS); 
    glColor3f(0.0f, 1.0f, 0.0f);  // Cor verde
    glVertex2f(-0.5f, -0.5f); // Vértice inferior esquerdo
    glVertex2f( 0.5f, -0.5f); // Vértice inferior direito
    glVertex2f( 0.5f,  0.5f); // Vértice superior direito
    glVertex2f(-0.5f,  0.5f); // Vértice superior esquerdo
    glEnd(); 

    // Troca os buffers para exibir a cena
    glfwSwapBuffers(glfwGetCurrentContext());
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

        desenhaQuadrado();

        glfwSetKeyCallback(window, key_callback);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}