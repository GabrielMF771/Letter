#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração de funções

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 
    600, "Jogo", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Função pra deixar tudo no centro da tela
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwSetKeyCallback(window, key_callback);
    }

    glfwTerminate();
    return 0;
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
//funcao retorno teclas do teclado

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        printf("Jogo iniciado\n");
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        printf("Mostrando estatisticas\n");
}