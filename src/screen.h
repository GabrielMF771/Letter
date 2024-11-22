#ifndef SCREEN_H
#define SCREEN_H

// Definição do enum para controlar o estado do programa
typedef enum {
    MENU, // Tela principal do menu
    JOGO, // Tela do jogo
    ESTATISTICAS // Tela de estatísticas
} Tela;

// Struct dos botões do menu
typedef struct Button {
    GLuint texture; // A textura do botão
    float xPos, yPos; // Posição do centro do botão
    float width, height; // Tamanho do botão
} Button;

// Struct dos slots
typedef struct Slot {
    GLuint texture;
    float width, height;
    int desenhado;
} Slot;

// Struct das linhas
#define TAMANHO_LINHA 5
#define MAX_LINHAS 6

typedef struct Linha{
    char estado[TAMANHO_LINHA]; // Estado de cada letra ('2', '1', '0')
    int atual; // 1 se a linha for a atual, 0 caso contrário
    char letra[TAMANHO_LINHA]; // Armazena a letra digitada
} Linha;

extern Linha linhas[MAX_LINHAS];
extern int linha_atual; // Índice da linha atual

// Variáveis globais
extern Tela telaAtual;
extern int isInfiniteButtonClicked;
extern int isStartButtonClicked;

// Texturas - Menu
extern GLuint startButtonTexture;
extern GLuint statsButtonTexture;
extern GLuint infiniteButtonTexture;
extern GLuint TituloTexture;

// Texturas - Jogo
extern GLuint menuButtonTexture;
extern GLuint slotCinzaTexture;
extern GLuint slotVerdeTexture;
extern GLuint slotAmareloTexture;

// Letras
extern GLuint letraTexture;
extern GLuint letraATexture;
extern GLuint letraBTexture;
extern GLuint letraCTexture;
extern GLuint letraDTexture;
extern GLuint letraETexture;
extern GLuint letraFTexture;
extern GLuint letraGTexture;
extern GLuint letraHTexture;
extern GLuint letraITexture;
extern GLuint letraJTexture;
extern GLuint letraKTexture;
extern GLuint letraLTexture;
extern GLuint letraMTexture;
extern GLuint letraNTexture;
extern GLuint letraOTexture;
extern GLuint letraPTexture;
extern GLuint letraQTexture;
extern GLuint letraRTexture;
extern GLuint letraSTexture;
extern GLuint letraTTexture;
extern GLuint letraUTexture;
extern GLuint letraVTexture;
extern GLuint letraWTexture;
extern GLuint letraXTexture;
extern GLuint letraYTexture;
extern GLuint letraZTexture;
extern GLuint VazioTexture;

// Variáveis externas para o tamanho da tela
extern const GLuint WIDTH;
extern const GLuint HEIGHT;

// Funções dos botões
int isButtonClicked(Button button, double mouseX, double mouseY, int windowWidth, int windowHeight);
void DeleteButtonTexture(GLuint* texture);
void carregaTexturasMenu();
void carregaTexturasJogo();
void liberaTexturasMenu();
void liberaTexturasJogo();
void DrawButton(GLuint texture, float x, float y, float width, float height);

// Declaração das funções de desenho das telas
void desenhaMenuPrincipal(GLFWwindow* window);
void desenhaTelaJogo(GLFWwindow* window);
void desenhaTelaEstatisticas(GLFWwindow* window);
void atualizaTela(GLFWwindow* window);

// Funções do jogo
void desenharSlot(float x, float y, GLuint textura);
void atualizarOcorrencias();
void desenharSlots();
void desenharLetra(float x, float y, GLuint textura);
void backspace();

#endif
