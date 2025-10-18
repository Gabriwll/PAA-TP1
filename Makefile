# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g -std=c99 -I.

# Arquivos-fonte (.c)
SOURCES = main.c src/readFile/readFile.c src/backtrack/backtrack.c

# Arquivos objeto (.o) - TODOS NA RAIZ
OBJECTS = main.o readFile.o backtrack.o

# Nome do executável (COM .exe PARA WINDOWS)
EXECUTABLE = expresso_interestelar.exe
ANALYSIS_EXECUTABLE = expresso_interestelar_analysis.exe

# --- REGRAS ---

all: $(EXECUTABLE)

analysis: $(ANALYSIS_EXECUTABLE)

# Regra para o executável normal (usa os .o)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Regra para o executável de análise (compila tudo junto para a flag)
$(ANALYSIS_EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -DANALYSIS_MODE -o $(ANALYSIS_EXECUTABLE) $(SOURCES)

# --- REGRAS PARA CRIAR OS .o ---

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

readFile.o: src/readFile/readFile.c src/readFile/readFile.h
	$(CC) $(CFLAGS) -c src/readFile/readFile.c -o readFile.o
	
backtrack.o: src/backtrack/backtrack.c src/backtrack/backtrack.h
	$(CC) $(CFLAGS) -c src/backtrack/backtrack.c -o backtrack.o

# Regra 'clean' (VERSÃO WINDOWS - CORRIGIDA)
clean:
	-del *.o 2>NUL
	-del $(EXECUTABLE) 2>NUL
	-del $(ANALYSIS_EXECUTABLE) 2>NUL

.PHONY: all analysis clean