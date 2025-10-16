#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum TileType TileType;

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
    End,
    Empty, 
    Way, 
    RepairKit

}TileType;

void initializeData(Data *data, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency);
Data* readFile(const char *fileName);
void freeData(Data *data);

#endif // READ_FILE_H