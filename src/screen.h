#ifndef SCREEN_H
#define SCREEN_H

// Definição do enum para controlar o estado do programa
typedef enum {
    MENU,         // Tela principal do menu
    JOGO,         // Tela do jogo
    ESTATISTICAS  // Tela de estatísticas
} Tela;

// Struct dos botões do menu
typedef struct Button {
    GLuint texture;  // A textura do botão
    float xPos, yPos;  // Posição do centro do botão
    float width, height;  // Tamanho do botão
} Button;

// Variável global para armazenar o estado atual da tela
extern Tela telaAtual;

GLuint startButtonTexture;
GLuint statsButtonTexture;
GLuint TituloTexture;

extern const GLuint WIDTH;
extern const GLuint HEIGHT;

// Funções dos botões
int isButtonClicked(Button button, double mouseX, double mouseY, int windowWidth, int windowHeight);
void DrawButton(GLuint texture, float x, float y, float width, float height);

// Declaração das funções de desenho das telas
void desenhaMenuPrincipal(GLFWwindow* window);
void desenhaTelaJogo(GLFWwindow* window);
void desenhaTelaEstatisticas(GLFWwindow* window);
void atualizaTela(GLFWwindow* window);

#endif
