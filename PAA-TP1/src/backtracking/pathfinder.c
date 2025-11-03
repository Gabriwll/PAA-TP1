#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../map/map.h"

#define REQUIRED_PIECES 4

#ifdef ANALISE
long long rec_calls = 0;
long long max_rec_depth = 0;
#endif

typedef struct {
    int linha, coluna;
    int durabilidade;
    int pecas_restantes;
} Step;

static Step *path_buf = NULL;
static Step *sol_path = NULL;
static int path_len = 0, sol_len = 0;
static bool solution_found = false;

static void push_step(int r, int c, int D, int faltam) {
    if (!path_buf) path_buf = malloc(sizeof(Step) * R * C * 10);
    path_buf[path_len++] = (Step){r + 1, c + 1, D, faltam};
}

static void pop_step(void) { if (path_len > 0) path_len--; }

static void salvar_solucao(void) {
    sol_len = path_len;
    sol_path = realloc(sol_path, sizeof(Step) * sol_len);
    for (int i = 0; i < sol_len; i++) sol_path[i] = path_buf[i];
    solution_found = true;
    printf("\n*** SOLUCAO ENCONTRADA! Comprimento: %d ***\n", sol_len);
}

void movimentar(int r, int c, int dur, int pecas, int depth) {
#ifdef ANALISE
    rec_calls++;
    if (depth > max_rec_depth) max_rec_depth = depth;
#endif
    if (solution_found || dur < 0 || visitado[r][c]) return;

    visitado[r][c] = true;
    int faltam = REQUIRED_PIECES - pecas;
    push_step(r, c, dur, faltam);

    if (mapa[r][c] == 'F') { salvar_solucao(); pop_step(); visitado[r][c] = false; return; }

    const int drs[4] = {-1, 0, 1, 0};
    const int dcs[4] = {0, 1, 0, -1};

    for (int k = 0; k < 4 && !solution_found; k++) {
        int nr = r + drs[k], nc = c + dcs[k];
        if (!dentro(nr, nc) || visitado[nr][nc] || !ha_conexao(r, c, nr, nc)) continue;

        int newD = dur - D_dec;
        if (newD < 0) continue;

        bool pegou = false;
        if (mapa[nr][nc] == 'P' && !peca_coletada[nr][nc]) {
            newD += A_add;
            pegou = true;
            peca_coletada[nr][nc] = true;
        }

        int newP = pecas + (pegou ? 1 : 0);
        if (newP > REQUIRED_PIECES) newP = REQUIRED_PIECES;

        movimentar(nr, nc, newD, newP, depth + 1);
        if (pegou) peca_coletada[nr][nc] = false;
    }

    pop_step();
    visitado[r][c] = false;
}

void imprimir_solucao(void) {
    if (!solution_found) {
        printf("\nApesar da bravura a tripulacao falhou em sua jornada\n");
#ifdef ANALISE
        printf("\n--- MODO ANALISE ---\nChamadas recursivas: %lld\nMaior profundidade: %lld\n",
               rec_calls, max_rec_depth);
#endif
        return;
    }
    printf("\n=== PERCURSO ENCONTRADO ===\n");
    for (int i = 0; i < sol_len; i++)
        printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n",
               sol_path[i].linha, sol_path[i].coluna, sol_path[i].durabilidade, sol_path[i].pecas_restantes);

    Step last = sol_path[sol_len - 1];
    printf("\n#MENSAGEM FINAL\n\n");
    if (last.pecas_restantes == 0)
        printf("A jornada sera finalizada sem mais desafios\n");
    else
        printf("A tripulacao finalizou sua jornada\n");

#ifdef ANALISE
    printf("\n--- MODO ANALISE ---\nChamadas recursivas: %lld\nMaior profundidade: %lld\n",
           rec_calls, max_rec_depth);
#endif
}
