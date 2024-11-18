#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL.h>

#include "common.h"
#include "screen.h"
#include "level.h"
#include "score.h"

Tela telaAtual = MENU;

GLuint startButtonTexture = 0;
GLuint statsButtonTexture = 0;
GLuint infiniteButtonTexture = 0;
GLuint TituloTexture = 0;

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
    infiniteButtonTexture = LoadTexture("assets/main-menu/InfinitoBotao.png");
    TituloTexture = LoadTexture("assets/main-menu/Titulo.png");
}

void liberaTexturasMenu() {
    DeleteButtonTexture(&statsButtonTexture);
    DeleteButtonTexture(&startButtonTexture);
    DeleteButtonTexture(&infiniteButtonTexture);
    DeleteButtonTexture(&TituloTexture);
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
    

    // Desenhar os botões
    DrawButton(tittleButton.texture, tittleButton.xPos - tittleButton.width / 2, tittleButton.yPos - tittleButton.height / 2, tittleButton.width, tittleButton.height);
    DrawButton(startButton.texture, startButton.xPos - startButton.width / 2, startButton.yPos - startButton.height / 2, startButton.width, startButton.height);
    DrawButton(statsButton.texture, statsButton.xPos - statsButton.width / 2, statsButton.yPos - statsButton.height / 2, statsButton.width, statsButton.height);

    if (fase >= 6){
        Button infiniteButton = {infiniteButtonTexture, 0.0f, -0.70f, 0.6f, 0.22f};

        DrawButton(infiniteButton.texture, infiniteButton.xPos - infiniteButton.width / 2, infiniteButton.yPos - infiniteButton.height / 2, infiniteButton.width, infiniteButton.height);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            // Verificar se o clique está no botão "Modo Infinito"
            if (isButtonClicked(infiniteButton, xpos, ypos, WIDTH, HEIGHT)) {
            printf("Modo Infinito pressionado!\n");
            telaAtual = JOGO;
            // Lógica para iniciar o jogo infinito

                gerarPalavraFases(fase);
                gerarLibrary();
                printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG
            }
        }
        
    }
    
    // Verificar se algum botão foi clicado
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);  // Posição do mouse na janela

        // Verificar se o clique está no botão "Estatísticas"
        if (isButtonClicked(statsButton, xpos, ypos, WIDTH, HEIGHT)) {
            printf("Estatisticas pressionado!\n");
            telaAtual = ESTATISTICAS;
            // Lógica para exibir as estatísticas

            printf("\nTempo decorrido: %02dh%02dm%02ds\n", horas, minutos, segundos); // DEBUG
            
        }
        
        // Verificar se o clique está no botão "Iniciar Jogo"
        if (isButtonClicked(startButton, xpos, ypos, WIDTH, HEIGHT)) {
            printf("Iniciar Jogo pressionado!\n");
            if (fase != 6){
                // Lógica para iniciar o jogo

                captura_tempo_inicio(&horas, &minutos, &segundos);
                printf("Tempo contando\n");

                captura_tempo_inicio(&horas, &minutos, &segundos);
                gerarPalavraFases(fase);
                gerarLibrary();
                printf("\nA palavra escolhida para a fase %d foi [%s]\n", fase, escolhida); // DEBUG

                telaAtual = JOGO;
            } else {
                printf("Utilize o modo infinito!\n");
                telaAtual = MENU;
            }
        }
    }

    glDisable(GL_BLEND);

    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
}

// Função para desenhar a tela de jogo
void desenhaTelaJogo(GLFWwindow* window) {
    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    glfwSwapBuffers(glfwGetCurrentContext());
}

// Função para desenhar a tela de estatísticas
void desenhaTelaEstatisticas(GLFWwindow* window) {
    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    glfwSwapBuffers(glfwGetCurrentContext());
}

// Função de atualização que chama a função correspondente à tela atual
void atualizaTela(GLFWwindow* window) {
    // Desenha a tela conforme o estado atual
    switch (telaAtual) {
        case MENU:
            if (fase >= 6) {
                captura_tempo_final_e_calcula(&horas, &minutos, &segundos);
                printf("Tempo parou de contar\n");
            }
            desenhaMenuPrincipal(window);
            break;
        case JOGO:
            desenhaTelaJogo(window);
            break;
        case ESTATISTICAS:
            desenhaTelaEstatisticas(window);
            break;
        default:
            break;
    }
}