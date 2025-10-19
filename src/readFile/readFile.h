#ifndef READ_FILE_H
#define READ_FILE_H

#include "../map/map.h"

#include <stdio.h>
#include <stdlib.h>

//TODO: Implementar vrificações mais robustas de integridade dos metadados fornecidos na entrada. Não confiar no usuário.
MapData* readFile(const char *fileName);

#endif // READ_FILE_H