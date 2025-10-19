#include "map.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    MapData *map = (MapData*)malloc(sizeof(MapData));
    //Map need to be allocated before initialization for some reason

    printf("Testing Map Initialization and Coordinate Setting\n");
    initializeMap(map, 5, 5, 100, 1, 20);

    Coordinate start = {0, 0};
    Coordinate end = {4, 4};

    setStartCoord(map, start);
    setEndCoord(map, end);

    map->field[0][0] = Start;
    map->field[4][4] = End;

    for(int i = 1; i < map->height - 1; i++){
        map->field[i][i] = Way;
        for(int j = i + 1; j < map->width; j++){
            map->field[i][j] = Empty;
            map->field[j][i] = Empty;
        }
    }

    // Print map details
    printf("Map dimensions: %dx%d\n", map->height, map->width);
    printf("Start Coordinate: (%d, %d)\n", map->start.x, map->start.y);
    printf("End Coordinate: (%d, %d)\n", map->end.x, map->end.y);

    // Print the map
    printMap(*map);

    // Free allocated memory
    freeMap(map);

    return 0;
}