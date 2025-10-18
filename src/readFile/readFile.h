#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum TileType TileType;

typedef struct Data{
    int durability;          
    int durabilityLoss;      
    int repairKitEfficiency; 
    int height;
    int width;
    int startX;
    int startY;
    TileType** map; 
    bool** visited; //Matriz das posições visitadas
}Data;

typedef enum TileType{
    Start, 
    End,
    Empty,      //'.'
    WayVertical, //'|'
    WayHorizontal, //'-'
    WayCross,   //'+'
    RepairKit   //'P'
}TileType;

void initializeData(Data *data, int height, int width, int durability, int durabilityLoss, int repairKitEfficiency);
Data* readFile(const char *fileName);
void freeData(Data *data);

#endif // READ_FILE_H