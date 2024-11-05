# Define as variáveis
CC = gcc
CFLAGS = -g -Iinclude -Llib -lglfw3dll
SRC = src/main.c lib/glad.c
OBJ = obj/main.o obj/glad.o
TARGET = bin/main.exe

# Criação dos diretórios de saída
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Regra para compilar os arquivos .c em .o
obj/%.o: src/%.c
	@if not exist obj mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@

# Regra específica para glad.c
obj/glad.o: lib/glad.c
	@if not exist obj mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos temporários
clean:
	@if exist obj\*.o del /q obj\*.o
	@if exist bin\main.exe del /q bin\main.exe

.PHONY: all clean