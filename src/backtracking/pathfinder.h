#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../map/map.h"

#include <stdlib.h>

typedef struct Path Path;
typedef struct Position Position;
typedef enum Direction Direction;

typedef struct Path{
    Coordinate start;
    Path *next;

    Direction pathDirection;
}Path;

typedef enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
}Direction;

void findPath(MapData *map, Path *pathHead);

int moveTillObstacle(MapData *map, Coordinate* currentPos, Direction dir);
int walkUp(Coordinate* currentPos);
int walkDown(Coordinate* currentPos, int mapHeight);
int walkLeft(Coordinate* currentPos);
int walkRight(Coordinate* currentPos, int mapWidth);

int repairDurability(int *currentDurability, int repairKitEfficiency);
int loseDurability(int *currentDurability, int durabilityLoss);

void printPath(Path path);

void initializePath(Path **pathHead);
void freePath(Path* path);

#endif // PATHFINDER_H