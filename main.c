#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 2048
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

char **mapa = NULL;
int R = 0, C = 0;
int D_init = 0, D_dec = 0, A_add = 0;

bool **visitado = NULL;
bool **peca_coletada = NULL;
Step *path_buf = NULL;
Step *sol_path = NULL;
int path_len = 0;
int sol_len = 0;
bool solution_found = false;

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
    if (dr == -1 && dc == 0) dir = 0;        // UP
    else if (dr == 0 && dc == 1) dir = 1;    // RIGHT
    else if (dr == 1 && dc == 0) dir = 2;    // DOWN
    else if (dr == 0 && dc == -1) dir = 3;   // LEFT
    else return false;

    int op = (dir + 2) % 4;
    return permite_direcao(mapa[r][c], dir) && permite_direcao(mapa[nr][nc], op);
}

void push_step(int r, int c, int D, int pecas_rest) {
    if (!path_buf) path_buf = malloc(sizeof(Step) * R * C * 10);
    if (path_len < R * C * 10) {
        path_buf[path_len].linha = r + 1;
        path_buf[path_len].coluna = c + 1;
        path_buf[path_len].durabilidade = D;
        path_buf[path_len].pecas_restantes = pecas_rest;
        path_len++;
    }
}

void pop_step() { if (path_len > 0) path_len--; }

void salvar_solucao() {
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
    if (solution_found) return;
    if (dur < 0) return;
    if (visitado[r][c]) return;

    visitado[r][c] = true;

    if (depth <= 20)
        printf("Depth %d: (%d,%d)='%c' dur=%d pecas=%d\n", depth, r, c, mapa[r][c], dur, pecas);

    int faltam = REQUIRED_PIECES - pecas;
    push_step(r, c, dur, faltam);

    if (mapa[r][c] == 'F') {
        salvar_solucao();
        pop_step();
        visitado[r][c] = false;
        return;
    }

    const int drs[4] = {-1, 0, 1, 0};
    const int dcs[4] = {0, 1, 0, -1};

    for (int k = 0; k < 4 && !solution_found; k++) {
        int nr = r + drs[k];
        int nc = c + dcs[k];

        if (!dentro(nr, nc) || visitado[nr][nc] || !ha_conexao(r, c, nr, nc))
            continue;

        int newD = dur - D_dec;
        if (newD < 0) continue;   // ✅ ALTERAÇÃO AQUI

        bool pegou = false;
        if (mapa[nr][nc] == 'P' && !peca_coletada[nr][nc]) {
            newD += A_add;
            pegou = true;
            peca_coletada[nr][nc] = true;
            if (depth <= 15)
                printf("  -> Peca coletada em (%d,%d)! Durabilidade: %d -> %d\n",
                       nr, nc, dur - D_dec, newD);
        }

        int newP = pecas + (pegou ? 1 : 0);
        if (newP > REQUIRED_PIECES) newP = REQUIRED_PIECES;

        movimentar(nr, nc, newD, newP, depth + 1);

        if (pegou) peca_coletada[nr][nc] = false;
    }

    pop_step();
    visitado[r][c] = false;
}

void libera_estruturas() {
    if (mapa) { for (int i = 0; i < R; i++) free(mapa[i]); free(mapa); }
    if (visitado) { for (int i = 0; i < R; i++) free(visitado[i]); free(visitado); }
    if (peca_coletada) { for (int i = 0; i < R; i++) free(peca_coletada[i]); free(peca_coletada); }
    free(path_buf); free(sol_path);
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

bool ler_arquivo(const char *fname, int *sr, int *sc) {
    FILE *f = fopen(fname, "r");
    if (!f) { printf("Erro: Nao foi possivel abrir '%s'\n", fname); return false; }

    char line[MAX_LINE];
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

void imprimir_solucao() {
    if (!solution_found) {
        printf("\nApesar da bravura a tripulacao falhou em sua jornada\n");
#ifdef ANALISE
        printf("\n--- MODO ANALISE ---\nChamadas recursivas: %lld\nMaior profundidade: %lld\n", rec_calls, max_rec_depth);
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
    printf("\n--- MODO ANALISE ---\nChamadas recursivas: %lld\nMaior profundidade: %lld\n", rec_calls, max_rec_depth);
#endif
}

int main(void) {
    const char *fname = "entrada.txt";
    int sr = -1, sc = -1;

    printf("=== EXPRESSO INTERESTELAR ===\n");
    if (!ler_arquivo(fname, &sr, &sc)) return 1;

    debug_mapa(sr, sc);
    debug_conexoes(sr, sc);

#ifdef ANALISE
    rec_calls = 0; max_rec_depth = 0;
#endif

    printf("Buscando solucao...\n");
    movimentar(sr, sc, D_init, 0, 1);

    imprimir_solucao();
    libera_estruturas();
    return 0;
}
