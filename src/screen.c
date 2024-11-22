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

// Letras
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
GLuint VazioTexture = 0;

// Título das fases
GLuint fase1Texture = 0;
GLuint fase2Texture = 0;
GLuint fase3Texture = 0;
GLuint fase4Texture = 0;
GLuint fase5Texture = 0;
GLuint fase6Texture = 0;

// Telas
GLuint vitoriaTela = 0;
GLuint derrotaTela = 0;

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
    VazioTexture = LoadTexture("assets/levels/letters/Vazio.png");

    fase1Texture = LoadTexture("assets/levels/Fase1.png");
    fase2Texture = LoadTexture("assets/levels/Fase2.png");
    fase3Texture = LoadTexture("assets/levels/Fase3.png");
    fase4Texture = LoadTexture("assets/levels/Fase4.png");
    fase5Texture = LoadTexture("assets/levels/Fase5.png");
    fase6Texture = LoadTexture("assets/levels/Fase6.png");

    vitoriaTela = LoadTexture("assets/levels/TelaVitoria.png");
    derrotaTela = LoadTexture("assets/levels/TelaDerrota.png");
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
    DeleteButtonTexture(&VazioTexture);

    DeleteButtonTexture(&fase1Texture);
    DeleteButtonTexture(&fase2Texture);
    DeleteButtonTexture(&fase3Texture);
    DeleteButtonTexture(&fase4Texture);
    DeleteButtonTexture(&fase5Texture);
    DeleteButtonTexture(&fase6Texture);

    DeleteButtonTexture(&vitoriaTela);
    DeleteButtonTexture(&derrotaTela);
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

void desenharLetra(float x, float y, GLuint textura) {
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + 0.1f, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + 0.1f, y + 0.1f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + 0.1f);
    glEnd();
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

// Variáveis globais para armazenar a última posição da letra
int ultimaLinha = -1;
int ultimaColuna = -1;

void desenharSlots() {
    float offsetX = -(TAMANHO_LINHA) * 0.1f;
    float offsetY = (MAX_LINHAS) * 0.1f;

    GLuint textura = 0;
    GLuint texturaLetra = 0;

    // Desenha os slots
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
                    textura = slotCinzaTexture;
                    break;
                default:
                    textura = slotCinzaTexture;
                    break;
            }

            // Redesenha o slot
            desenharSlot(x, y, textura);
        }
    }

    // Desenha as letras
    for (int i = 0; i < MAX_LINHAS; i++) {
        float y = offsetY - i * 0.2f;
        for (int j = 0; j < TAMANHO_LINHA; j++) {
            float x = offsetX + j * 0.2f;

            // Escolhe a textura com base na letra
            switch (linhas[i].letra[j]) {
                case 'a': texturaLetra = letraATexture; break;
                case 'b': texturaLetra = letraBTexture; break;
                case 'c': texturaLetra = letraCTexture; break;
                case 'd': texturaLetra = letraDTexture; break;
                case 'e': texturaLetra = letraETexture; break;
                case 'f': texturaLetra = letraFTexture; break;
                case 'g': texturaLetra = letraGTexture; break;
                case 'h': texturaLetra = letraHTexture; break;
                case 'i': texturaLetra = letraITexture; break;
                case 'j': texturaLetra = letraJTexture; break;
                case 'k': texturaLetra = letraKTexture; break;
                case 'l': texturaLetra = letraLTexture; break;
                case 'm': texturaLetra = letraMTexture; break;
                case 'n': texturaLetra = letraNTexture; break;
                case 'o': texturaLetra = letraOTexture; break;
                case 'p': texturaLetra = letraPTexture; break;
                case 'q': texturaLetra = letraQTexture; break;
                case 'r': texturaLetra = letraRTexture; break;
                case 's': texturaLetra = letraSTexture; break;
                case 't': texturaLetra = letraTTexture; break;
                case 'u': texturaLetra = letraUTexture; break;
                case 'v': texturaLetra = letraVTexture; break;
                case 'w': texturaLetra = letraWTexture; break;
                case 'x': texturaLetra = letraXTexture; break;
                case 'y': texturaLetra = letraYTexture; break;
                case 'z': texturaLetra = letraZTexture; break;
                default: texturaLetra = VazioTexture; break;
            }

            // Desenha a letra
            if (texturaLetra != VazioTexture) {
                desenharLetra(x + 0.05f, y - 0.15f, texturaLetra);

                // Armazena a última posição da letra
                ultimaLinha = i;
                ultimaColuna = j;
            }
        }
    }
}

// Função que apaga uma letra da tela
void backspace(int vezes) {
    for (int i = 0; i < vezes; i++) {
        // Verifica se há uma letra a ser apagada
        if (ultimaLinha != -1 && ultimaColuna != -1) {
            // Substitui a última letra por um espaço em branco
            linhas[ultimaLinha].letra[ultimaColuna] = ' ';
            
            // Calcula as coordenadas para o slot
            float x = -(TAMANHO_LINHA) * 0.1f + ultimaColuna * 0.2f;
            float y = (MAX_LINHAS) * 0.1f - ultimaLinha * 0.2f;

            // Redesenha o slot com a textura padrão (cinza)
            GLuint textura = slotCinzaTexture;
            desenharSlot(x, y, textura);

            // Substitui a letra por uma textura vazia
            desenharLetra(x + 0.05f, y - 0.15f, VazioTexture);

            if (ultimaColuna > 0) {
                ultimaColuna--;
            } else if (ultimaLinha > 0) {
                ultimaLinha--;
                ultimaColuna = TAMANHO_LINHA - 1;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

// Função que desenha a tela da vitória
void desenharVitoria() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Button Vitoria = {vitoriaTela, 0.0f, 0.0f, 1.5f, 0.8f};
    DrawButton(Vitoria.texture, Vitoria.xPos - Vitoria.width / 2, Vitoria.yPos - Vitoria.height / 2, Vitoria.width, Vitoria.height);
    
    glDisable(GL_BLEND);
}

// Função que desenha a tela de derrota
void desenharDerrota() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Button Derrota = {derrotaTela, 0.0f, 0.0f, 1.5f, 0.8f};
    DrawButton(Derrota.texture, Derrota.xPos - Derrota.width / 2, Derrota.yPos - Derrota.height / 2, Derrota.width, Derrota.height);

    glDisable(GL_BLEND);
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

    //Desenhar o título da fase
    GLuint faseTexture = 0;

    switch (fase)
    {
    case 1:
        faseTexture = fase1Texture;
        break;

    case 2:
        faseTexture = fase2Texture;
        break;
    case 3:
        faseTexture = fase3Texture;
        break;
    case 4:
        faseTexture = fase4Texture;
        break;
    case 5:
        faseTexture = fase5Texture;
        break;
    case 6:
        faseTexture = fase6Texture;
        break;
    default:
        faseTexture = fase1Texture;
    break;
    }

    Button FaseButton = {faseTexture, 0.0f, 0.78f, 0.7f, 0.25f};
    DrawButton(FaseButton.texture, FaseButton.xPos - FaseButton.width / 2, FaseButton.yPos - FaseButton.height / 2, FaseButton.width, FaseButton.height);

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
        case VITORIA:
            desenharVitoria();
            break;
        case DERROTA:
            desenharDerrota();
            break;
        default:
            break;
    }

    // Faz a troca de buffers e processa eventos
    glfwSwapBuffers(window);
    glfwPollEvents();
}