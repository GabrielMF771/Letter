# Variáveis
CC = gcc
BIN = bin
OBJ_DIR = obj
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)  # Todos os arquivos .c em src
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Objetos gerados na pasta obj
CFLAGS = -Wall -I $(SRC_DIR)  # Flags de compilação

.PHONY: all clean

all: dirs game

dirs:
	mkdir $(BIN)
	mkdir $(OBJ_DIR)

game: $(OBJ)
	$(CC) -o $(BIN)/game.exe $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	if exist $(BIN) rmdir /s /q $(BIN)
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

run: all
	$(BIN)/game.exe