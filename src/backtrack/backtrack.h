#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "src/readFile/readFile.h"
#include <stdbool.h>

typedef struct {
    unsigned long totalRecursiveCalls;
    int maxRecursionDepth;
} AnalysisData;

bool movimentar(Data* data, 
                AnalysisData* analysis, 
                int r, 
                int c, 
                int currentDur, 
                int piecesLeft, 
                int currentDepth);

#endif // BACKTRACK_H