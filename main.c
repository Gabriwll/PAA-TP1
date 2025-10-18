#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "src/readFile/readFile.h"
#include "src/backtrack/backtrack.h"

void clean_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    char filename[256];
    bool firstRun = true;

    while (true) { //
        if (firstRun && argc > 1) {
            strncpy(filename, argv[1], 255);
            filename[255] = '\0';
            printf("Arquivo de entrada (via argumento): %s\n", filename);
        } else {
            if (!firstRun) {
                printf("\nDigite o caminho do arquivo de mapa (ou 'sair' para fechar): ");
                if (fgets(filename, 255, stdin) == NULL) break;
                filename[strcspn(filename, "\n")] = 0;
            } else {
                printf("Digite o caminho do arquivo de mapa (ou 'sair' para fechar): ");
                if (scanf("%255s", filename) != 1) break;
                clean_stdin(); 
            }
        }
        firstRun = false;

        if (strcmp(filename, "sair") == 0) break;

        Data* data = readFile(filename);
        if (data == NULL) {
            printf("Não foi possível carregar o arquivo: %s\n", filename);
            continue; 
        }

        printf("Arquivo lido com sucesso! Mapa %d x %d\n", data->height, data->width);
        printf("Iniciando jornada na Linha %d, Coluna %d\n", data->startX + 1, data->startY + 1);
        printf("----------------------------------------\n");

        AnalysisData analysis = {0, 0};
        
        bool solutionFound = movimentar(data, 
                                        &analysis, 
                                        data->startX, 
                                        data->startY, 
                                        data->durability, 
                                        4,
                                        0);

        printf("----------------------------------------\n");

        if (!solutionFound) {
            printf("Apesar da bravura a tripulação falhou em sua jornada\n"); //
        }

        #ifdef ANALYSIS_MODE
        printf("\n--- MODO DE ANÁLISE ---\n");
        printf("Total de chamadas recursivas: %lu\n", analysis->totalRecursiveCalls);
        printf("Nível máximo de recursão: %d\n", analysis.maxRecursionDepth);
        #endif

        freeData(data);
    }

    printf("Encerrando o programa.\n");
    return 0;
}