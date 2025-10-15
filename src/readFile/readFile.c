#include "readFile.h"

void initializeData(Data *data){
    data = (Data*)malloc(sizeof(Data));
}

void readFile(const char *fileName, Data *data, TileType **map){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    

    fclose(file);
}

void freeData(Data *data){
    for(int i = 0; i < data->height; i++){
        free(data->map[i]);
    }
    free(data->map);
    free(data);
}