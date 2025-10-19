#include <stdio.h>
#include "src/map/map.h"
#include "src/readFile/readFile.h"
#include "src/backtracking/pathfinder.h"

int main(int argc, char *argv[]) {
    const char *fname = (argc > 1) ? argv[1] : "entrada.txt";  // usa argumento se houver
    int sr = -1, sc = -1;

    printf("=== EXPRESSO INTERESTELAR ===\n");
    if (!ler_arquivo(fname, &sr, &sc)) return 1;

    debug_mapa(sr, sc);
    debug_conexoes(sr, sc);

    printf("Buscando solucao...\n");
    movimentar(sr, sc, D_init, 0, 1);
    imprimir_solucao();
    libera_estruturas();
    return 0;
}