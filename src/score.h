#ifndef SCORE_H
#define SCORE_H

extern int horas;
extern int minutos;
extern int segundos;

extern int capturouTempo;

typedef struct {
    int horas;
    int minutos;
    int segundos;
} Tempo;

int compararTempos(const void *a, const void *b);
void captura_tempo_inicio(int *horas,int *minutos,int *segundos);
void captura_tempo_final_e_calcula(int *horas, int *minutos, int *segundos);
void inicializa_ponteiros_tempo();

void escreverArquivoScore(int horas, int minutos, int segundos);
void lerArquivoScore();
void limparArquivoScore();

#endif