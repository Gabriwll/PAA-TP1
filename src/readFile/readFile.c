#include "readFile.h"

MapData* readFile(const char *fileName){
    MapData *map = (MapData*)malloc(sizeof(MapData));

    int height, width;
    int durability, durabilityLoss, repairKitEfficiency;

    printf("Reading map from file: %s\n", fileName);

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fscanf(file, "%d %d %d\n", &durability, &durabilityLoss, &repairKitEfficiency); //Read first line
    fscanf(file, "%d %d\n", &height, &width); //Read second line

    initializeMap(map, height, width, durability, durabilityLoss, repairKitEfficiency);

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
                freeMap(map);
                fclose(file);
                return NULL;
            }

            if(tile == 'X'){
                Coordinate startCoord;
                startCoord.x = j;
                startCoord.y = i;

                map->field[i][j] = Start;

                setStartCoord(map, startCoord);
            }
            else if(tile == 'F'){
                Coordinate endCoord;
                endCoord.x = j;
                endCoord.y = i;

                map->field[i][j] = End;

                setEndCoord(map, endCoord);
            }
            else if(tile == '.'){
                map->field[i][j] = Empty;
            }
            else if(tile == '-' || tile == '|'){
                map->field[i][j] = Way;
            }
            else if(tile == '+'){
                map->field[i][j] = Intersection;
            }
            else if(tile == 'P'){
                map->field[i][j] = RepairKit;
            }
            else{
                printf("Unknown tile character '%c' at (%d, %d)\n", tile, i, j);
                freeMap(map);
                fclose(file);
                return NULL;
            }
        }
        if(flagEOF){ // In case the file ends before filling the map
            break;
        }
    }

    fclose(file);

    return map;
}