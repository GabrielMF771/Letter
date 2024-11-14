CC = gcc
CFLAGS = -g -Iinclude -Ilib/SOIL -Llib/SOIL -Llib -lglfw3dll -lSOIL -lopengl32
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin
SRC = $(wildcard $(SRC_DIR)/*.c) $(LIB_DIR)/glad.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/main.exe
GLFW_DLL = $(LIB_DIR)/glfw3.dll

.PHONY: all clean run libs copy_dlls

all: clean dirs copy_dll libs 
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

dirs:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

copy_dll:
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@xcopy /y $(LIB_DIR)\glfw3.dll $(BIN_DIR)\ 

libs:
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/glad.o -c $(LIB_DIR)/glad.c
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/screen.o -c $(SRC_DIR)/screen.c
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/main.o -c $(SRC_DIR)/main.c
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)

run: all
	$(TARGET)