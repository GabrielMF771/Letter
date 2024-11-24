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

// Função para carregar o ícone da janela
GLuint carregarIcone(const char* caminho) {
    // Carrega a imagem com SOIL
    int largura, altura, canais;
    unsigned char* dados = SOIL_load_image(caminho, &largura, &altura, &canais, SOIL_LOAD_AUTO);

    if (!dados) {
        fprintf(stderr, "Falha ao carregar o ícone da janela: %s\n", caminho);
        return 0;
    }

    // Cria uma textura OpenGL para a imagem
    GLuint textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, dados);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(dados); // Libera os dados da imagem

    return textura;
}

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

    // Define o ícone da janela
    GLFWimage icone;
    icone.pixels = SOIL_load_image("assets/icon.png", &icone.width, &icone.height, 0, SOIL_LOAD_RGBA);
    if (icone.pixels) {
        glfwSetWindowIcon(*window, 1, &icone); // Define o ícone da janela
        SOIL_free_image_data(icone.pixels); // Libera a memória da imagem
    }

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
            case GLFW_KEY_DOWN:
                limparArquivoScore();
                break;

            case GLFW_KEY_ESCAPE:
                if (telaAtual != MENU) {
                    telaAtual = MENU;  // Vai para a tela de menu
                    atualizaTela(window);
                } else {
                    glfwSetWindowShouldClose(window, 1);
                }
                break;

            case GLFW_KEY_ENTER:
                if (telaAtual == JOGO) {
                    verificacao(escolhida, pilha);
                    break;
                }

            case GLFW_KEY_PAGE_UP:
                if (mostrarResposta == 0) {
                    mostrarResposta = 1;
                    printf("\nMostrar Resposta Habilitado!\n");
                    break;
                } else {
                    mostrarResposta = 0;
                    printf("\nMostrar Resposta Desabilitado!\n");
                    break;
                }

            case GLFW_KEY_BACKSPACE:
                if (telaAtual == JOGO) {
                    if(isEmpty(pilha)){
                        break;
                    }
                    pop(pilha);  // Remove o elemento do topo da pilha
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