#include "common.h"
#include "screen.h"

Tela telaAtual = MENU;

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
        return 1;  // Clique dentro do botão
    }
    return 0;  // Clique fora do botão
}

// Função para mudar o cursor dependendo da posição do mouse
void mudaCursor(GLFWwindow* window, Button button, double mouseX, double mouseY, int windowWidth, int windowHeight) {
    if (isButtonClicked(button, mouseX, mouseY, windowWidth, windowHeight)) {
        glfwSetCursor(window, glfwCreateStandardCursor(GLFW_HAND_CURSOR)); // Cursor de mão
    } else {
        glfwSetCursor(window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR)); // Cursor padrão
    }
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

// Função para desenhar o menu principal
void desenhaMenuPrincipal(GLFWwindow* window) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    statsButtonTexture = LoadTexture("assets/main-menu/EstatisticasBotao.png");
    startButtonTexture = LoadTexture("assets/main-menu/IniciarBotao.png");
    TituloTexture = LoadTexture("assets/main-menu/Titulo.png");

    glClearColor(1.0f, 0.91f, 0.73f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Criar os botões
    Button tittleButton = {TituloTexture, 0.0f, 0.3f, 1.0f, 0.42f}; // Título
    Button startButton = {startButtonTexture, 0.0f, -0.2f, 0.6f, 0.22f}; // Botão "Iniciar Jogo"
    Button statsButton = {statsButtonTexture, 0.0f, -0.45f, 0.6f, 0.22f}; // Botão "Estatísticas"

    // Desenhar os botões
    DrawButton(tittleButton.texture, tittleButton.xPos - tittleButton.width / 2, tittleButton.yPos - tittleButton.height / 2, tittleButton.width, tittleButton.height);
    
    DrawButton(startButton.texture, startButton.xPos - startButton.width / 2, startButton.yPos - startButton.height / 2, startButton.width, startButton.height);
    
    DrawButton(statsButton.texture, statsButton.xPos - statsButton.width / 2, statsButton.yPos - statsButton.height / 2, statsButton.width, statsButton.height);

    // Pegar a posição do mouse
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);  // Posição do mouse na janela

    // Mudar o cursor para mão ou seta dependendo de onde o mouse está
    mudaCursor(window, tittleButton, xpos, ypos, WIDTH, HEIGHT);
    mudaCursor(window, startButton, xpos, ypos, WIDTH, HEIGHT);
    mudaCursor(window, statsButton, xpos, ypos, WIDTH, HEIGHT);

    // Verificar se algum botão foi clicado
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);  // Posição do mouse na janela

        // Verificar se o clique está no botão "Estatísticas"
        if (isButtonClicked(statsButton, xpos, ypos, WIDTH, HEIGHT)) {
            printf("Estatísticas pressionado!\n");
            telaAtual = ESTATISTICAS;
            // Lógica para exibir as estatísticas
        }
        
        // Verificar se o clique está no botão "Iniciar Jogo"
        if (isButtonClicked(startButton, xpos, ypos, WIDTH, HEIGHT)) {
            printf("Iniciar Jogo pressionado!\n");
            telaAtual = JOGO;
            // Lógica para iniciar o jogo
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