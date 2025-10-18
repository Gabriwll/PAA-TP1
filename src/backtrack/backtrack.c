#include "src/backtrack/backtrack.h"
#include <stdio.h>

void printStep(int r, int c, int dur, int pieces) {
    printf("Linha: %d, Coluna: %d;\n", r + 1, c + 1); //
    printf("D: %d, peças restantes: %d\n", dur, pieces); //
}

bool movimentar(Data* data, 
                AnalysisData* analysis, 
                int r, 
                int c, 
                int currentDur, 
                int piecesLeft, 
                int currentDepth) 
{
    #ifdef ANALYSIS_MODE
    analysis->totalRecursiveCalls++;
    if (currentDepth > analysis->maxRecursionDepth) {
        analysis->maxRecursionDepth = currentDepth;
    }
    #endif

    //Verifica apenas limites, paredes e visitados
    if (r < 0 || r >= data->height || c < 0 || c >= data->width) return false;
    if (data->map[r][c] == Empty || data->visited[r][c] == true) return false;

    //Olha posição atual
    //Garante que a durabilidade é adicionada antes de verificar se tem durabilidade
    TileType originalTile = data->map[r][c];
    bool collectedPiece = false;

    if (originalTile == RepairKit) {
        currentDur += data->repairKitEfficiency; //
        piecesLeft--; 
        collectedPiece = true;
        data->map[r][c] = WayCross; 
    }

    //Verifica a durabilidade
    if (currentDur <= 0 && originalTile != Start) return false;

    int piecesToPrint = (piecesLeft < 0) ? 0 : piecesLeft;
    printStep(r, c, currentDur, piecesToPrint);

    //Deu certo
    if (originalTile == End) {
        if (piecesLeft <= 0) printf("\nA jornada será finalizada sem mais desafios\n"); //
        else printf("\n\n"); //
        if (collectedPiece) data->map[r][c] = RepairKit; 
        return true; 
    }

    //Explorar e maracar
    data->visited[r][c] = true;
    int loss = (piecesLeft <= 0) ? 0 : data->durabilityLoss; //
    int nextDur = currentDur - loss;

    int dr[] = {-1, 1, 0, 0}; //Cima, Baixo
    int dc[] = {0, 0, -1, 1}; //Esquerda, Direita

    for (int i = 0; i < 4; i++) {
        bool moveAllowed = false;
        
        //Regras de movimento
        if (originalTile == Start || originalTile == End || 
            originalTile == WayCross || originalTile == RepairKit) { 
            moveAllowed = true;
        } 
        else if (originalTile == WayVertical) { // '|'
            if (i == 0 || i == 1) moveAllowed = true;
        } 
        else if (originalTile == WayHorizontal) { // '-'
            if (i == 2 || i == 3) moveAllowed = true;
        }

        if (moveAllowed) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            if (movimentar(data, analysis, nextR, nextC, nextDur, piecesLeft, currentDepth + 1)) {
                if (collectedPiece) data->map[r][c] = RepairKit;
                return true;
            }
        }
    }

    //Desfazer
    data->visited[r][c] = false;
    if (collectedPiece) {
        data->map[r][c] = RepairKit; //Reset do mapa
    }
    return false; 
}