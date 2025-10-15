#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Data{
    int durability;          // Maximum durability
    int durabilityLoss;      // Durability loss per tile
    int repairKitEfficiency; // Repair kit efficiency

    // Map dimensions
    int height;
    int width;

    TileType** map; // 2D array representing the map
}Data;

typedef enum TileType{
    Start, 
    Empty, 
    Way, 
    RepairKit

}TileType;

void initializeData(Data *data);
void readFile(const char *fileName, Data *data, TileType **map);

#endif // READ_FILE_H