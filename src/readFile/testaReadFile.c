#include "readFile.h"

int main(){
    printf("Testing Read File Function\n");
    MapData* map = readFile("./Files/In/map1.txt");
    //Map need to be allocated before initialization for some reason


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