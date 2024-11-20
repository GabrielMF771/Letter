#ifndef SCORE_H
#define SCORE_H

void captura_tempo_inicio(int *horas,int *minutos,int *segundos);
void captura_tempo_final_e_calcula(int *horas, int *minutos, int *segundos);
void inicializa_ponteiros_tempo();

extern int horas;
extern int minutos;
extern int segundos;

extern int capturouTempo;

#endif