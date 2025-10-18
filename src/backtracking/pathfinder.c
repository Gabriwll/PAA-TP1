#include "pathfinder.h"

void findPath(MapData *map, Path *pathHead){
    Coordinate currentPos = pathHead->start;

    if(map->field[currentPos.y - 1][currentPos.x] != Empty){      //can we go up?
        walkUp(&currentPos);
    }
    else if(map->field[currentPos.y + 1][currentPos.x] != Empty){ //can we go down?
        walkDown(&currentPos, map->height);
    }
    else if(map->field[currentPos.y][currentPos.x + 1] != Empty){ //can we go left?
        walkLeft(&currentPos);
    }
    else if(map->field[currentPos.y][currentPos.x - 1] != Empty){ //can we go right?
        walkRight(&currentPos, map->width);
    }

    
}

int moveTillObstacle(MapData *map, Coordinate* currentPos, Direction dir){
    int status = 0;
    switch(dir){
        case UP:
            while(map->field[currentPos->y][currentPos->x] != Intersection){
                status = walkUp(currentPos);
                if(status != 0) return status;
            }
            break;
        case DOWN:
            while(map->field[currentPos->y][currentPos->x] != Intersection){
                status = walkDown(currentPos, map->height);
                if(status != 0) return status;
            }
            break;
        case LEFT:
            while(map->field[currentPos->y][currentPos->x] != Intersection){
                status = walkLeft(currentPos);
                if(status != 0) return status;
            }
            break;
        case RIGHT:
            while(map->field[currentPos->y][currentPos->x] != Intersection){
                status = walkRight(currentPos, map->width);
                if(status != 0) return status;
            }
            break;
    }
    return 0; // Success
}

int walkUp(Coordinate* currentPos){
    if(currentPos->y - 1 < 0){
        return 1; // Invalid move
    }
    currentPos->y -= 1;
    return 0; // Success
}

int walkDown(Coordinate* currentPos, int mapHeight){
    if(currentPos->y + 1 >= mapHeight){
        return 1; // Invalid move
    }
    currentPos->y += 1;
    return 0; // Success
}

int walkLeft(Coordinate* currentPos){
    if(currentPos->x - 1 < 0){
        return 1; // Invalid move
    }
    currentPos->x -= 1;
    return 0; // Success

}

int walkRight(Coordinate* currentPos, int mapWidth){
    if(currentPos->x + 1 >= mapWidth){
        return 1; // Invalid move
    }
    currentPos->x += 1;
    return 0; // Success
}

int repairDurability(int *currentDurability, int repairKitEfficiency){
    *currentDurability += repairKitEfficiency;
    return *currentDurability; // Return new durability
}

int loseDurability(int *currentDurability, int durabilityLoss){
    *currentDurability -= durabilityLoss;
    if(*currentDurability < 0){
        *currentDurability = 0;
    }
    return *currentDurability; // Return new durability
}

void printPath(Path path){

}

void initializePath(Path **pathHead){
    *pathHead = NULL;
}

void freePath(Path* path){
    Path *current = path;
    Path *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}