#include <stdio.h>
#include <stdlib.h>
#include "map.h"

char **mapa = NULL;
bool **visitado = NULL;
bool **peca_coletada = NULL;
int R = 0, C = 0;
int D_init = 0, D_dec = 0, A_add = 0;

bool dentro(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

bool permite_direcao(char ch, int dir) {
    if (ch == '+') return true;
    if (ch == 'P' || ch == 'X' || ch == 'F') return true;
    if (dir == 1 || dir == 3) return (ch == '-');
    else return (ch == '|');
}

bool ha_conexao(int r, int c, int nr, int nc) {
    if (!dentro(nr, nc)) return false;
    if (mapa[nr][nc] == '.' || mapa[r][c] == '.') return false;

    int dr = nr - r, dc = nc - c, dir = -1;
    if (dr == -1 && dc == 0) dir = 0;
    else if (dr == 0 && dc == 1) dir = 1;
    else if (dr == 1 && dc == 0) dir = 2;
    else if (dr == 0 && dc == -1) dir = 3;
    else return false;

    int op = (dir + 2) % 4;
    return permite_direcao(mapa[r][c], dir) && permite_direcao(mapa[nr][nc], op);
}

void libera_estruturas() {
    if (mapa) { for (int i = 0; i < R; i++) free(mapa[i]); free(mapa); mapa = NULL; }
    if (visitado) { for (int i = 0; i < R; i++) free(visitado[i]); free(visitado); visitado = NULL; }
    if (peca_coletada) { for (int i = 0; i < R; i++) free(peca_coletada[i]); free(peca_coletada); peca_coletada = NULL; }
}

void debug_mapa(int sr, int sc) {
    printf("=== DEBUG MAPA ===\n");
    printf("Dimensoes: %d x %d\n", R, C);
    printf("Start: (%d,%d) - '%c'\n", sr, sc, mapa[sr][sc]);
    printf("Destino F: ");
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (mapa[i][j] == 'F') printf("(%d,%d) ", i, j);
    printf("\nD_init: %d, D_dec: %d, A_add: %d\nMapa:\n", D_init, D_dec, A_add);
    for (int i = 0; i < R; i++) printf("%s\n", mapa[i]);
    printf("==================\n\n");
}

void debug_conexoes(int sr, int sc) {
    printf("=== DEBUG CONEXOES from (%d,%d)='%c' ===\n", sr, sc, mapa[sr][sc]);
    const int drs[4] = {-1, 0, 1, 0};
    const int dcs[4] = {0, 1, 0, -1};
    const char *dirs[4] = {"UP", "RIGHT", "DOWN", "LEFT"};
    for (int k = 0; k < 4; k++) {
        int nr = sr + drs[k], nc = sc + dcs[k];
        if (dentro(nr, nc))
            printf("  %s: to (%d,%d)='%c' -> %s\n", dirs[k], nr, nc, mapa[nr][nc],
                   ha_conexao(sr, sc, nr, nc) ? "CONECTADO" : "BLOQUEADO");
        else
            printf("  %s: FORA DO MAPA\n", dirs[k]);
    }
    printf("================================\n\n");
}
