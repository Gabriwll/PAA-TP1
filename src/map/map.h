#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct MapData MapData;
typedef struct Coordinate Coordinate;
typedef enum TileType TileType;


typedef struct Coordinate{
    int x;
    int y;
}Coordinate;

typedef struct MapData{
    int durability;          // Maximum durability
    int durabilityLoss;      // Durability loss per tile
    int repairKitEfficiency; // Repair kit efficiency

    // Map dimensions
    int height;
    int width;

    Coordinate start;
    Coordinate end;
    TileType** field; // 2D array representing the map
}MapData;

typedef enum TileType{
    Start, 
    End,
    Empty, 
    Way,
    Intersection,
    RepairKit

}TileType;

void initializeMap(MapData *map, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency);

int setStartCoord(MapData *map, Coordinate start);
int setEndCoord(MapData *map, Coordinate end);

void printMap(MapData map);

void freeMap(MapData *map);

#endif // MAP_H