CC = gcc
SRC_DIR = src
MAP_DIR = $(SRC_DIR)/map
READ_DIR = $(SRC_DIR)/readFile
PATH_DIR = $(SRC_DIR)/backtracking
SRC = main.c \
      $(MAP_DIR)/map.c \
      $(READ_DIR)/readFile.c \
      $(PATH_DIR)/pathfinder.c
INCLUDES = -I$(MAP_DIR) -I$(READ_DIR) -I$(PATH_DIR)
CFLAGS = -Wall -Wextra -std=c11 $(INCLUDES)
TARGET = pathfinder

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compilando Expresso Interestelar..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Compilação concluída com sucesso!"

analise:
	@echo "Compilando com MODO DE ANÁLISE ativado..."
	$(CC) $(CFLAGS) -DANALISE $(SRC) -o $(TARGET)
	@echo "Compilação concluída (modo análise)."

run:
	@echo "Executando Expresso Interestelar..."
	./$(TARGET)

run-analise:
	@echo "Executando Expresso Interestelar (modo análise)..."
	./$(TARGET)

clean:
	@echo "Removendo arquivos compilados..."
	rm -f $(TARGET)
	@echo "Limpeza concluída!"
