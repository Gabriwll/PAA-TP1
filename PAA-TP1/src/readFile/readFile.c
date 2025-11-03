#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../map/map.h"

bool ler_arquivo(const char *fname, int *sr, int *sc) {
    FILE *f = fopen(fname, "r");
    if (!f) { printf("Erro: Nao foi possivel abrir '%s'\n", fname); return false; }

    char line[2048];
    if (!fgets(line, sizeof(line), f) || sscanf(line, "%d %d %d", &D_init, &D_dec, &A_add) != 3)
        return fclose(f), printf("Erro na primeira linha\n"), false;

    if (!fgets(line, sizeof(line), f) || sscanf(line, "%d %d", &R, &C) != 2)
        return fclose(f), printf("Erro nas dimensoes\n"), false;

    mapa = malloc(sizeof(char*) * R);
    visitado = malloc(sizeof(bool*) * R);
    peca_coletada = malloc(sizeof(bool*) * R);
    for (int i = 0; i < R; i++) {
        mapa[i] = malloc(C + 1);
        visitado[i] = calloc(C, sizeof(bool));
        peca_coletada[i] = calloc(C, sizeof(bool));
    }

    int start_r = -1, start_c = -1;
    for (int i = 0; i < R; i++) {
        fgets(line, sizeof(line), f);
        int len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) line[--len] = '\0';
        for (int j = 0; j < C; j++) {
            mapa[i][j] = (j < len) ? line[j] : '.';
            if (mapa[i][j] == 'X') { start_r = i; start_c = j; }
        }
        mapa[i][C] = '\0';
    }
    fclose(f);
    if (start_r == -1) return printf("Erro: 'X' nao encontrado\n"), false;
    *sr = start_r; *sc = start_c; return true;
}
