#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFile.h"
#include "pathfinder.h"
#include "map.h"

void limparTela() {
#ifdef _WIN32
    system("cls");
    system("chcp 65001 > nul");
#else
    system("clear");
#endif
}

void titulo(const char *texto) {
    printf("\033[1;36m╔══════════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║ %-52s ║\033[0m\n", texto);
    printf("\033[1;36m╚══════════════════════════════════════════════════════╝\033[0m\n");
}

int main(void) {
    char arquivo[256];
    int sr = -1, sc = -1;
    int ativarAnalise = 0;
    char resp;

    limparTela();
    titulo("EXPRESSO INTERESTELAR 🚀");
    printf("\033[1;33mBem-vindo, comandante!\033[0m\n\n");
    printf("Prepare-se para guiar o expresso através do mapa intergaláctico.\n");
    printf("Certifique-se de que o arquivo de entrada está na pasta Files/In.\n\n");

    printf("\033[1;37mDigite o caminho do arquivo de entrada(Exemplo: Files/In/entradacerta.txt):\033[0m\n> ");
    fgets(arquivo, sizeof(arquivo), stdin);
    arquivo[strcspn(arquivo, "\n")] = '\0'; 

    if (strlen(arquivo) == 0) {
        printf("\033[1;31mErro: nome de arquivo não informado.\033[0m\n");
        return 1;
    }

    limparTela();
    titulo("CARREGANDO MAPA...");
    printf("Tentando abrir arquivo: \033[1;34m%s\033[0m\n", arquivo);

    if (!ler_arquivo(arquivo, &sr, &sc)) {
        printf("\n\033[1;31mFalha ao carregar o mapa. Encerrando.\033[0m\n");
        return 1;
    }

    printf("\n\033[1;32mMapa carregado com sucesso!\033[0m\n\n");
    printf("Dimensões: \033[1;36m%d x %d\033[0m\n", R, C);
    printf("Durabilidade inicial: \033[1;33m%d\033[0m | Perda: \033[1;31m%d\033[0m | Ganho: \033[1;32m%d\033[0m\n",
           D_init, D_dec, A_add);
    printf("Ponto inicial: (\033[1;36m%d,%d\033[0m)\n", sr + 1, sc + 1);

    printf("\nDeseja visualizar o mapa completo? (\033[1;32ms\033[0m/\033[1;31mn\033[0m): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        limparTela();
        titulo("VISUALIZAÇÃO DO MAPA");
        debug_mapa(sr, sc);
    }

    printf("\nAtivar modo de análise? (\033[1;32ms\033[0m/\033[1;31mn\033[0m): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        ativarAnalise = 1;
    }

    limparTela();
    titulo("INICIANDO A MISSÃO 🚀");
    printf("\033[1;37mCalculando rota e verificando conexões...\033[0m\n\n");

#ifdef ANALISE
    rec_calls = 0;
    max_rec_depth = 0;
#endif

    movimentar(sr, sc, D_init, 0, 1);
    imprimir_solucao();

    if (ativarAnalise) {
#ifdef ANALISE
        printf("\n\033[1;34m--- RELATÓRIO DE ANÁLISE ---\033[0m\n");
        printf("Chamadas recursivas: \033[1;33m%lld\033[0m\n", rec_calls);
        printf("Profundidade máxima: \033[1;33m%lld\033[0m\n", max_rec_depth);
#endif
    }

    printf("\n\033[1;37mMissão encerrada.\033[0m\n");
    printf("\033[1;36mObrigado por jogar o Expresso Interestelar!\033[0m\n\n");
    return 0;
}
