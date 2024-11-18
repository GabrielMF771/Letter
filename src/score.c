#include "common.h"
#include "score.h"

    //função q aloca o tempo em q foi iniciada a primeira fase - CHAMAR QND INICIAR O JOGO
void captura_tempo_inicio(int *horas,int *minutos,int *segundos) {
    time_t agora;
    time(&agora);
    struct tm *tempo_local = localtime(&agora);
    *horas = tempo_local->tm_hour;
    *minutos = tempo_local->tm_min;
    *segundos = tempo_local->tm_sec;
}
    //função q vai pegar o tempo final e subtrair com o inicial - CHAMAR QND ENCERRAR O JOGO 
void captura_tempo_final_e_calcula(int *horas, int *minutos, int *segundos) {
   
    time_t agora;
    time(&agora);
    struct tm *tempo_local = localtime(&agora);
    int hora2 = tempo_local->tm_hour;
    int minuto2 = tempo_local->tm_min;
    int segundo2 = tempo_local->tm_sec;
    *horas = *horas - hora2; 
    *minutos = *minutos - minuto2;
    *segundos = *segundos - segundo2;
}

int principal() {

    //inicializa os ponteiros q vão guardar os valores iniciais e dps o valor da diferença
    //PRECISA TER INICIALIZADO ELES ANTES DE CHAMAR AS FUNÇÕES
    int *segundos = (int*)malloc(sizeof(int));
    int *horas = (int*)malloc(sizeof(int));
    int *minutos = (int*)malloc(sizeof(int));
    //função q aloca o tempo em q foi iniciada a primeira fase - CHAMAR QND INICIAR O JOGO
    captura_tempo_inicio(horas,minutos,segundos); 
    //função q vai pegar o tempo final e subtrair com o inicial - CHAMAR QND ENCERRAR O JOGO 
    captura_tempo_final_e_calcula(horas,minutos,segundos);
    printf("Horas decorridas: %02d, Minutos decorridos: %02d, Segundos decorridos: %02d\n", *horas, *minutos, *segundos);
    return 0;
}