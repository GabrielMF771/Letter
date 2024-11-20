#include "common.h"
#include "score.h"

int horas = 0;
int minutos = 0;
int segundos = 0;

int capturouTempo = 0;

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