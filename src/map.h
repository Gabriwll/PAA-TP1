#ifndef MAP_H
#define MAP_H
#include <stdbool.h>

extern char **mapa;
extern bool **visitado;
extern bool **peca_coletada;
extern int R, C;
extern int D_init, D_dec, A_add;

bool dentro(int r, int c);
bool permite_direcao(char ch, int dir);
bool ha_conexao(int r, int c, int nr, int nc);
void libera_estruturas(void);
void debug_mapa(int sr, int sc);
void debug_conexoes(int sr, int sc);

#endif
