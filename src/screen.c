#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include "common.h"
#include "window.h"
#include "screen.h"
#include "level.h"
#include "score.h"

Tela telaAtual = MENU;

// Variaveis de textura
GLuint startButtonTexture = 0;
GLuint statsButtonTexture = 0;
GLuint infiniteButtonTexture = 0;
GLuint menuButtonTexture = 0;
GLuint TituloTexture = 0;

// Variaveis de textura do jogo
GLuint slotCinzaTexture = 0;
GLuint slotAmareloTexture = 0;
GLuint slotVerdeTexture = 0;

GLuint letraATexture = 0;
GLuint letraBTexture = 0;
GLuint letraCTexture = 0;
GLuint letraDTexture = 0;
GLuint letraETexture = 0;
GLuint letraFTexture = 0;
GLuint letraGTexture = 0;
GLuint letraHTexture = 0;
GLuint letraITexture = 0;
GLuint letraJTexture = 0;
GLuint letraKTexture = 0;
GLuint letraLTexture = 0;
GLuint letraMTexture = 0;
GLuint letraNTexture = 0;
GLuint letraOTexture = 0;
GLuint letraPTexture = 0;
GLuint letraQTexture = 0;
GLuint letraRTexture = 0;
GLuint letraSTexture = 0;
GLuint letraTTexture = 0;
GLuint letraUTexture = 0;
GLuint letraVTexture = 0;
GLuint letraWTexture = 0;
GLuint letraXTexture = 0;
GLuint letraYTexture = 0;
GLuint letraZTexture = 0;


// Flags e estados do clique
int mouseButtonPressed = 0;
int isStartButtonClicked = 0;
int isStatsButtonClicked = 0;
int isMenuButtonClicked = 0;
int isInfiniteButtonClicked = 0;

int linha_atual = 0; // Índice da linha atual
Linha linhas[MAX_LINHAS];

GLuint LoadTexture(const char* filePath) {
    GLuint texture = SOIL_load_OGL_texture(
        filePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
    );

    if (!texture) {
        printf("Falha ao carregar textura: %s\n", filePath);
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

// Função para verificar se o clique está dentro do botão
int isButtonClicked(Button button, double mouseX, double mouseY, int windowWidth, int windowHeight) {
    // Normaliza as coordenadas para OpenGL [-1, 1]
    float xNorm = (float)((mouseX / windowWidth) * 2 - 1);
    float yNorm = (float)(1 - (mouseY / windowHeight) * 2);

    // Ajusta as coordenadas do botão para o sistema de coordenadas normalizado
    float left = button.xPos - button.width / 2;
    float right = button.xPos + button.width / 2;
    float bottom = button.yPos - button.height / 2;
    float top = button.yPos + button.height / 2;

    // Verifica se o clique está dentro da área do botão
    if (xNorm >= left && xNorm <= right && yNorm >= bottom && yNorm <= top) {
        return 1;
    }
    return 0;
}

void DrawButton(GLuint texture, float x, float y, float width, float height) {
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    glEnd();
}

void DeleteButtonTexture(GLuint* texture) {
    if (texture && *texture != 0) {
        glDeleteTextures(1, texture); // Libera o ID da textura
        *texture = 0; // Marca como não utilizada
    }
}

void carregaTexturasMenu() {
    statsButtonTexture = LoadTexture("assets/main-menu/EstatisticasBotao.png");
    startButtonTexture = LoadTexture("assets/main-menu/IniciarBotao.png");
    menuButtonTexture = LoadTexture("assets/main-menu/MenuBotao.png");
    infiniteButtonTexture = LoadTexture("assets/main-menu/InfinitoBotao.png");
    TituloTexture = LoadTexture("assets/main-menu/Titulo.png");
}

void liberaTexturasMenu() {
    DeleteButtonTexture(&statsButtonTexture);
    DeleteButtonTexture(&startButtonTexture);
    DeleteButtonTexture(&infiniteButtonTexture);
    DeleteButtonTexture(&menuButtonTexture);
    DeleteButtonTexture(&TituloTexture);
}

void carregaTexturasJogo(){
    slotCinzaTexture = LoadTexture("assets/levels/SlotCinza.png");
    slotAmareloTexture = LoadTexture("assets/levels/SlotAmarelo.png");
    slotVerdeTexture = LoadTexture("assets/levels/SlotVerde.png");

    letraATexture = LoadTexture("assets/levels/letters/A.png");
    letraBTexture = LoadTexture("assets/levels/letters/B.png");
    letraCTexture = LoadTexture("assets/levels/letters/C.png");
    letraDTexture = LoadTexture("assets/levels/letters/D.png");
    letraETexture = LoadTexture("assets/levels/letters/E.png");
    letraFTexture = LoadTexture("assets/levels/letters/F.png");
    letraGTexture = LoadTexture("assets/levels/letters/G.png");
    letraHTexture = LoadTexture("assets/levels/letters/H.png");
    letraITexture = LoadTexture("assets/levels/letters/I.png");
    letraJTexture = LoadTexture("assets/levels/letters/J.png");
    letraKTexture = LoadTexture("assets/levels/letters/K.png");
    letraLTexture = LoadTexture("assets/levels/letters/L.png");
    letraMTexture = LoadTexture("assets/levels/letters/M.png");
    letraNTexture = LoadTexture("assets/levels/letters/N.png");
    letraOTexture = LoadTexture("assets/levels/letters/O.png");
    letraPTexture = LoadTexture("assets/levels/letters/P.png");
    letraQTexture = LoadTexture("assets/levels/letters/Q.png");
    letraRTexture = LoadTexture("assets/levels/letters/R.png");
    letraSTexture = LoadTexture("assets/levels/letters/S.png");
    letraTTexture = LoadTexture("assets/levels/letters/T.png");
    letraUTexture = LoadTexture("assets/levels/letters/U.png");
    letraVTexture = LoadTexture("assets/levels/letters/V.png");
    letraWTexture = LoadTexture("assets/levels/letters/W.png");
    letraXTexture = LoadTexture("assets/levels/letters/X.png");
    letraYTexture = LoadTexture("assets/levels/letters/Y.png");
    letraZTexture = LoadTexture("assets/levels/letters/Z.png");
}

void liberaTexturasJogo(){
    DeleteButtonTexture(&slotCinzaTexture);
    DeleteButtonTexture(&slotAmareloTexture);
    DeleteButtonTexture(&slotVerdeTexture);

    DeleteButtonTexture(&letraATexture);
    DeleteButtonTexture(&letraBTexture);
    DeleteButtonTexture(&letraCTexture);
    DeleteButtonTexture(&letraDTexture);
    DeleteButtonTexture(&letraETexture);
    DeleteButtonTexture(&letraFTexture);
    DeleteButtonTexture(&letraGTexture);
    DeleteButtonTexture(&letraHTexture);
    DeleteButtonTexture(&letraITexture);
    DeleteButtonTexture(&letraJTexture);
    DeleteButtonTexture(&letraKTexture);
    DeleteButtonTexture(&letraLTexture);
    DeleteButtonTexture(&letraMTexture);
    DeleteButtonTexture(&letraNTexture);
    DeleteButtonTexture(&letraOTexture);
    DeleteButtonTexture(&letraPTexture);
    DeleteButtonTexture(&letraQTexture);
    DeleteButtonTexture(&letraRTexture);
    DeleteButtonTexture(&letraSTexture);
    DeleteButtonTexture(&letraTTexture);
    DeleteButtonTexture(&letraUTexture);
    DeleteButtonTexture(&letraVTexture);
    DeleteButtonTexture(&letraWTexture);
    DeleteButtonTexture(&letraXTexture);
    DeleteButtonTexture(&letraYTexture);
    DeleteButtonTexture(&letraZTexture);
}

// Função para desenhar o menu principal
void desenhaMenuPrincipal(GLFWwindow* window) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Criar os botões
    Button tittleButton = {TituloTexture, 0.0f, 0.3f, 1.0f, 0.42f};
    Button startButton = {startButtonTexture, 0.0f, -0.2f, 0.6f, 0.22f};
    Button statsButton = {statsButtonTexture, 0.0f, -0.45f, 0.6f, 0.22f};
    
    // Criar o botão "Modo Infinito" somente se a fase >= 6
    Button infiniteButton = {infiniteButtonTexture, 0.0f, -0.70f, 0.6f, 0.22f};
    if (fase >= 6) {
        DrawButton(infiniteButton.texture, infiniteButton.xPos - infiniteButton.width / 2, infiniteButton.yPos - infiniteButton.height / 2, infiniteButton.width, infiniteButton.height);
    }

    // Desenhar os botões
    DrawButton(tittleButton.texture, tittleButton.xPos - tittleButton.width / 2, tittleButton.yPos - tittleButton.height / 2, tittleButton.width, tittleButton.height);
    DrawButton(startButton.texture, startButton.xPos - startButton.width / 2, startButton.yPos - startButton.height / 2, startButton.width, startButton.height);
    DrawButton(statsButton.texture, statsButton.xPos - statsButton.width / 2, statsButton.yPos - statsButton.height / 2, statsButton.width, statsButton.height);

    // Verificar se algum botão foi clicado
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);  // Posição do mouse na janela

        // Verificar clique no botão "Modo Infinito" se a fase >= 6
        if (fase >= 6 && isButtonClicked(infiniteButton, xpos, ypos, WIDTH, HEIGHT)) {
            if (!isInfiniteButtonClicked) {
                printf("Modo Infinito pressionado!\n");
                isInfiniteButtonClicked = 1;
                telaAtual = JOGO;
                iniciarFase();
            }
        }

        // Verificar se o clique está no botão "Estatísticas"
        if (isButtonClicked(statsButton, xpos, ypos, WIDTH, HEIGHT) && !isStatsButtonClicked) {
            printf("Estatisticas pressionado!\n");
            isStatsButtonClicked = 1;
            telaAtual = ESTATISTICAS;
            // Lógica para exibir as estatísticas

            printf("\nTempo decorrido: %02dh%02dm%02ds\n", horas, minutos, segundos); // DEBUG
            
        }
        
        // Verificar se o clique está no botão "Iniciar Jogo"
        if (isButtonClicked(startButton, xpos, ypos, WIDTH, HEIGHT) && !isStartButtonClicked) {
            printf("\nIniciar Jogo pressionado!\n");
            isStartButtonClicked = 1;
            if(fase < 6){
                iniciarFase();
            } else {
                printf("Utilize o modo infinito!\n");
            }
            
        }
    }

    glDisable(GL_BLEND);
}

void atualizarOcorrencias() {
    if (linha_atual < MAX_LINHAS) {
        // Atualiza o estado da linha atual
        for (int i = 0; i < TAMANHO_LINHA; i++) {
            linhas[linha_atual].estado[i] = ocorrencias[i];
        }
        linhas[linha_atual].atual = 1;

        // Avança para a próxima linha
        linha_atual++;
    }
}


void desenharSlot(float x, float y, GLuint textura) {
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + 0.2f, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + 0.2f, y - 0.2f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y - 0.2f);
    glEnd();
}
void desenharSlots() {
    float offsetX = -(TAMANHO_LINHA) * 0.1f;
    float offsetY = (MAX_LINHAS) * 0.1f;

    GLuint textura = 0;

    for (int i = 0; i < MAX_LINHAS; i++) {
        float y = offsetY - i * 0.2f;
        for (int j = 0; j < TAMANHO_LINHA; j++) {
            float x = offsetX + j * 0.2f;

            // Escolhe a textura com base no estado
            switch (linhas[i].estado[j]) {
                case '2':
                    textura = slotVerdeTexture;
                    break;
                case '1':
                    textura = slotAmareloTexture;
                    break;
                case '0':
                default:
                    textura = slotCinzaTexture;
                    break;
            }

            // Redesenha o slot
            desenharSlot(x, y, textura);
        }
    }
}

// Função para desenhar a tela de jogo
void desenhaTelaJogo(GLFWwindow* window) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Cria o botão
    Button menuButton = {menuButtonTexture, -0.88f, 0.88f, 0.2f, 0.2f};
    
    // Desenha o botão
    DrawButton(menuButton.texture, menuButton.xPos - menuButton.width / 2, menuButton.yPos - menuButton.height / 2, menuButton.width, menuButton.height);

    // Verificar se o botão foi clicado
    int currentMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (currentMouseState == GLFW_PRESS && mouseButtonPressed == 0) {
        mouseButtonPressed = 1;  // Botão pressionado

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Verificar se o clique está no botão "Menu"
        if (isButtonClicked(menuButton, xpos, ypos, WIDTH, HEIGHT) && !isMenuButtonClicked) {
            isMenuButtonClicked = 1;
            telaAtual = MENU;
            atualizaTela(window);
        }
    } if (currentMouseState == GLFW_RELEASE) {
        mouseButtonPressed = 0;  // Botão liberado
    }

    // Cria os slots
    Slot slotCinza = {slotCinzaTexture, 0.2f, 0.2f};
    Slot slotAmarelo = {slotAmareloTexture, 0.2f, 0.2f};
    Slot slotVerde = {slotVerdeTexture, 0.2f, 0.2f};

    //Desenhar os slots
    desenharSlots();

    glDisable(GL_BLEND);
}

// Função para desenhar a tela de estatísticas
void desenhaTelaEstatisticas(GLFWwindow* window) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Cria o botão
    Button menuButton = {menuButtonTexture, -0.88f, 0.88f, 0.2f, 0.2f};
    
    // Desenha o botão
    DrawButton(menuButton.texture, menuButton.xPos - menuButton.width / 2, menuButton.yPos - menuButton.height / 2, menuButton.width, menuButton.height);

    // Verificar se algum botão foi clicado
    int currentMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (currentMouseState == GLFW_PRESS && mouseButtonPressed == 0) {
        mouseButtonPressed = 1;  // Botão pressionado

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Verificar se o clique está no botão "Menu"
        if (isButtonClicked(menuButton, xpos, ypos, WIDTH, HEIGHT) && !isMenuButtonClicked) {
            isMenuButtonClicked = 1;
            telaAtual = MENU;
            atualizaTela(window);
        }
    }

    if (currentMouseState == GLFW_RELEASE) {
        mouseButtonPressed = 0;  // Botão liberado
    }

    glDisable(GL_BLEND);
}

// Função de atualização que chama a função correspondente à tela atual
void atualizaTela(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha a tela conforme o estado atual
    switch (telaAtual) {
        case MENU:
            desenhaMenuPrincipal(window);
            isStatsButtonClicked = 0;
            isInfiniteButtonClicked = 0;
            isMenuButtonClicked = 0;
            mouseButtonPressed = 0;
            break;
        case JOGO:
            desenhaTelaJogo(window);
            isStartButtonClicked = 0;
            mouseButtonPressed = 0;
            break;
        case ESTATISTICAS:
            desenhaTelaEstatisticas(window);
            break;
        default:
            break;
    }

    // Faz a troca de buffers e processa eventos
    glfwSwapBuffers(window);
    glfwPollEvents();
}
