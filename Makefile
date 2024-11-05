# Define as variáveis
CC = gcc
CFLAGS = -g -Iinclude -Llib -lglfw3dll
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin
SRC = $(SRC_DIR)/main.c $(LIB_DIR)/glad.c
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/glad.o
TARGET = $(BIN_DIR)/main.exe

.PHONY: all clean run libs

# Criação dos diretórios de saída
all: dirs libs

dirs:
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Regra única para compilar arquivos de biblioteca e gerar o executável
libs:
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/glad.o -c $(LIB_DIR)/glad.c
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/main.o -c $(SRC_DIR)/main.c
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

# Limpar arquivos temporários
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)

run: all
	$(TARGET)