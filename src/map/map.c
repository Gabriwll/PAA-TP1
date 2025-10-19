#include "map.h"
#include <stdlib.h>

void initializeMap(MapData *map, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency){
    map->field = (TileType**)malloc(height * sizeof(TileType*));
    
    for(int i = 0; i < height; i++){
        map->field[i] = (TileType*)malloc(width * sizeof(TileType));
    }

    map->height = height;
    map->width = width;

    map->durability = durability;
    map->durabilityLoss = durabilityLoss;
    map->repairKitEfficiency = repairKitEfficiency;
}

int setStartCoord(MapData *map, Coordinate start){
    if(start.x < 0 || start.x >= map->width || start.y < 0 || start.y >= map->height){
        printf("Invalid 'start' coordinate\n");
        return 1; // Invalid start coordinate
    }

    map->start = start;

    return 0; // Success
}

int setEndCoord(MapData *map, Coordinate end){
    if(end.x < 0 || end.x >= map->width || end.y < 0 || end.y >= map->height){
        printf("Invalid 'end' coordinate\n");
        return 1; // Invalid end coordinate
    }

    map->end = end;

    return 0; // Success
}

void printMap(MapData map){
    for(int i = 0; i < map.height; i++){
        for(int j = 0; j < map.width; j++){
            switch(map.field[i][j]){
                case Start:
                    printf("X");
                    break;
                case End:
                    printf("F");
                    break;
                case Empty:
                    printf(".");
                    break;
                case Way:
                    printf("-");
                    break;
                case Intersection:
                    printf("+");
                    break;
                case RepairKit:
                    printf("P");
                    break;
            }
        }
        printf("\n");
    }
}

void freeMap(MapData *map){
    for(int i = 0; i < map->height; i++){
        free(map->field[i]);
    }
    free(map->field);

    free(map);
}