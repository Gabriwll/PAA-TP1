#include "src/readFile/readFile.h" 
#include <string.h> 

void initializeData(Data *data, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency){
    data->map = (TileType**)malloc(height * sizeof(TileType*));
    data->visited = (bool**)malloc(height * sizeof(bool*)); 
    
    for(int i = 0; i < height; i++){
        data->map[i] = (TileType*)malloc(width * sizeof(TileType));
        data->visited[i] = (bool*)malloc(width * sizeof(bool)); 
        memset(data->visited[i], 0, width * sizeof(bool)); 
    }
    data->height = height;
    data->width = width;
    data->startX = -1; 
    data->startY = -1;
    data->durability = durability;
    data->durabilityLoss = durabilityLoss;
    data->repairKitEfficiency = repairKitEfficiency;
}

Data* readFile(const char *fileName){
    Data *data = (Data*)malloc(sizeof(Data));
    int height, width, durability, durabilityLoss, repairKitEfficiency;
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        free(data);
        return NULL;
    }

    if (fscanf(file, "%d %d %d\n", &durability, &durabilityLoss, &repairKitEfficiency) != 3) { //
        printf("Erro ao ler os metadados (D, D', A)\n");
        fclose(file); free(data); return NULL;
    }
    if (fscanf(file, "%d %d\n", &height, &width) != 2) { //
        printf("Erro ao ler as dimensões (Altura, Largura)\n");
        fclose(file); free(data); return NULL;
    }

    initializeData(data, height, width, durability, durabilityLoss, repairKitEfficiency);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            char tile;
            
            if(fscanf(file, " %c", &tile) != 1){
                printf("Erro lendo o mapa em (%d, %d)\n", i, j);
                freeData(data);
                fclose(file);
                return NULL;
            }
            
            if(tile == 'X'){ data->map[i][j] = Start; data->startX = i; data->startY = j; }
            else if(tile == 'F'){ data->map[i][j] = End; }
            else if(tile == '.'){ data->map[i][j] = Empty; }
            else if(tile == '|'){ data->map[i][j] = WayVertical; }
            else if(tile == '-'){ data->map[i][j] = WayHorizontal; }
            else if(tile == '+'){ data->map[i][j] = WayCross; }
            else if(tile == 'P'){ data->map[i][j] = RepairKit; }
            else{
                printf("Caractere desconhecido '%c' em (%d, %d)\n", tile, i, j);
                freeData(data); fclose(file); return NULL;
            }
        }
    }
    fclose(file);

    if (data->startX == -1 || data->startY == -1) {
        printf("Erro: Posição inicial 'X' não encontrada no mapa.\n");
        freeData(data);
        return NULL;
    }
    return data;
}

void freeData(Data *data){
    for(int i = 0; i < data->height; i++){
        free(data->map[i]);
        free(data->visited[i]); 
    }
    free(data->map);
    free(data->visited);
    free(data);
}