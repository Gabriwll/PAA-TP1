#include <stdio.h>
#include "src/readFile/readFile.h"

int main(int argc, char *argv[]) {
    // Read the file and get the data
    printf("Reading file...\n");
    Data* data = readFile("./Files/In/map1.txt");
    if (data == NULL) {
        printf("Failed to read file\n");
        return 1;
    }
    printf("File read successfully!\n");

    // Print the map dimensions
    printf("Map dimensions: %d x %d\n", data->height, data->width);
    printf("Durability: %d\n", data->durability);
    printf("Durability Loss: %d\n", data->durabilityLoss);
    printf("Repair Kit Efficiency: %d\n", data->repairKitEfficiency);

    // Print the map
    printf("\nMap:\n");
    for (int i = 0; i < data->height; i++) {
        for (int j = 0; j < data->width; j++) {
            switch (data->map[i][j]) {
                case Start:     printf("X"); break;
                case End:       printf("F"); break;
                case Empty:     printf("."); break;
                case Way:       printf("-"); break;
                case RepairKit: printf("P"); break;
            }
        }
        printf("\n");
    }

    // Free allocated memory
    freeData(data);

    return 0;
}