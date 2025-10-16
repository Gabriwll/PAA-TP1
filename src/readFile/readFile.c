#include "readFile.h"

void initializeData(Data *data, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency){
    data->map = (TileType**)malloc(height * sizeof(TileType*));
    
    for(int i = 0; i < height; i++){
        data->map[i] = (TileType*)malloc(width * sizeof(TileType));
    }

    data->height = height;
    data->width = width;

    data->durability = durability;
    data->durabilityLoss = durabilityLoss;
    data->repairKitEfficiency = repairKitEfficiency;
}

Data* readFile(const char *fileName){
    Data *data = (Data*)malloc(sizeof(Data));

    int height, width;
    int durability, durabilityLoss, repairKitEfficiency;

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fscanf(file, "%d %d %d\n", &durability, &durabilityLoss, &repairKitEfficiency); //Read first line
    fscanf(file, "%d %d\n", &height, &width); //Read second line

    initializeData(data, height, width, durability, durabilityLoss, repairKitEfficiency);

    for(int i = 0; i < height; i++){
        int flagEOF = 0;

        for(int j = 0; j < width; j++){
            char tile;
            
            if(tile == '\n'){ // In case there's a newline character, skip it
                break;
            }
            else if(tile == EOF){
                flagEOF = 1;
                break;
            }
            
            if(fscanf(file, " %c", &tile) != 1){
                printf("Error reading map data at (%d, %d)\n", i, j);
                freeData(data);
                fclose(file);
                return NULL;
            }

            if(tile == 'X'){
                data->map[i][j] = Start;
            }
            else if(tile == 'F'){
                data->map[i][j] = End;
            }
            else if(tile == '.'){
                data->map[i][j] = Empty;
            }
            else if(tile == '-' || tile == '|' || tile == '+'){
                data->map[i][j] = Way;
            }
            else if(tile == 'P'){
                data->map[i][j] = RepairKit;
            }
            else{
                printf("Unknown tile character '%c' at (%d, %d)\n", tile, i, j);
                freeData(data);
                fclose(file);
                return NULL;
            }
        }
        if(flagEOF){ // In case the file ends before filling the map
            break;
        }
    }

    fclose(file);

    return data;
}

void freeData(Data *data){
    for(int i = 0; i < data->height; i++){
        free(data->map[i]);
    }

    free(data->map);
    free(data);
}