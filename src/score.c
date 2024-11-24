#include "common.h"
#include "score.h"

int horas = 0;
int minutos = 0;
int segundos = 0;

int capturouTempo = 0;

// Função de comparação para ordenar os tempos em ordem crescente
int compararTempos(const void *a, const void *b) {
    Tempo *t1 = (Tempo *)a;
    Tempo *t2 = (Tempo *)b;

    int tempo1 = t1->horas * 3600 + t1->minutos * 60 + t1->segundos;
    int tempo2 = t2->horas * 3600 + t2->minutos * 60 + t2->segundos;

    return tempo1 - tempo2; // Ordem crescente
}

// Função q aloca o tempo em q foi iniciada a primeira fase - CHAMAR QND INICIAR O JOGO
void captura_tempo_inicio(int *horas,int *minutos,int *segundos) {
    if (capturouTempo == 0){
        time_t agora;
        time(&agora);
        struct tm *tempo_local = localtime(&agora);
        *horas = tempo_local->tm_hour;
        *minutos = tempo_local->tm_min;
        *segundos = tempo_local->tm_sec;
    } else {
        printf("Impossivel capturar novamente!");
    }
}

// Função q vai pegar o tempo final e subtrair com o inicial - CHAMAR QND ENCERRAR O JOGO 
void captura_tempo_final_e_calcula(int *horas, int *minutos, int *segundos) {
    time_t agora;
    time(&agora);
    struct tm *tempo_local = localtime(&agora);

    // Captura o tempo atual
    int hora_fim = tempo_local->tm_hour;
    int minuto_fim = tempo_local->tm_min;
    int segundo_fim = tempo_local->tm_sec;

    // Converte tudo para segundos
    int inicio_em_segundos = (*horas) * 3600 + (*minutos) * 60 + (*segundos);
    int fim_em_segundos = hora_fim * 3600 + minuto_fim * 60 + segundo_fim;

    // Calcula a diferença total em segundos
    int diferenca = fim_em_segundos - inicio_em_segundos;
    if (diferenca < 0) {
        diferenca += 24 * 3600; // Ajusta para o caso de troca de dia
    }

    // Converte de volta para horas, minutos e segundos
    *horas = diferenca / 3600;
    *minutos = (diferenca % 3600) / 60;
    *segundos = diferenca % 60;

    capturouTempo = 1;
}

void escreverArquivoScore(int horas, int minutos, int segundos) {
    FILE *file = fopen("assets/levels/score.dat", "r"); // Abre o arquivo para leitura
    if (file == NULL) {
        // Cria o arquivo se não existir
        file = fopen("assets/levels/score.dat", "w");
        if (file == NULL) {
            printf("Erro ao abrir o score\n");
            exit(EXIT_FAILURE);
        }
    }

    Tempo tempos[4]; // Para armazenar até 3 tempos antigos + 1 novo
    int numScores = 0;

    // Lê os tempos existentes no arquivo
    while (fscanf(file, "%*d - %02dh%02dm%02ds\n",
                  &tempos[numScores].horas, &tempos[numScores].minutos, &tempos[numScores].segundos) == 3) {
        numScores++;
    }
    fclose(file); // Fecha o arquivo após a leitura

    // Adiciona o novo tempo
    tempos[numScores].horas = horas;
    tempos[numScores].minutos = minutos;
    tempos[numScores].segundos = segundos;
    numScores++;

    // Ordena os tempos em ordem crescente
    qsort(tempos, numScores, sizeof(Tempo), compararTempos);

    // Limita a 3 tempos
    if (numScores > 3) {
        numScores = 3;
    }

    // Reabre o arquivo em modo "w" para sobrescrever o conteúdo
    file = fopen("assets/levels/score.dat", "w");
    if (file == NULL) {
        printf("Erro ao abrir o score para escrita\n");
        exit(EXIT_FAILURE);
    }

    // Escreve os tempos ordenados no arquivo
    for (int i = 0; i < numScores; i++) {
        fprintf(file, "%d - %02dh%02dm%02ds\n", i + 1, tempos[i].horas, tempos[i].minutos, tempos[i].segundos);
    }

    fclose(file);
    printf("Score salvo com sucesso!\n");
}

// Função que lê os tempos no arquivo score
void lerArquivoScore() {
    FILE *file = fopen("assets/levels/score.dat", "r"); // Abre o arquivo para leitura
    if (file == NULL) {
        printf("Nenhum score salvo ainda.\n");
        return;
    }

    int indice;
    int horas, minutos, segundos;

    printf("\nMelhor Tempo:\n");
    while (fscanf(file, "%d - %02dh%02dm%02ds\n", &indice, &horas, &minutos, &segundos) == 4) {
        printf("%d - %02dh%02dm%02ds\n", indice, horas, minutos, segundos);
    }

    fclose(file);
}

void limparArquivoScore() {
    FILE *file = fopen("assets/levels/score.dat", "w"); // Abre o arquivo no modo escrita
    if (file == NULL) {
        printf("Erro ao abrir o arquivo score.dat para limpeza.\n");
        exit(EXIT_FAILURE);
    }
    
    // Fecha o arquivo, deixando-o vazio
    fclose(file);
    printf("Arquivo score.dat limpo com sucesso!\n");
}