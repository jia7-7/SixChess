
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = bin/chess.exe
SRC_DIR = src
OBJ_DIR = obj


SRC = $(SRC_DIR)/main.c $(SRC_DIR)/logic.c $(SRC_DIR)/ui.c $(SRC_DIR)/file.c
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/logic.o $(OBJ_DIR)/ui.o $(OBJ_DIR)/file.o
HEADER = $(SRC_DIR)/head.h


all: create_dirs $(TARGET)


create_dirs:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "bin" mkdir "bin"


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo : $(TARGET)


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/logic.o: $(SRC_DIR)/logic.c $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/logic.c -o $(OBJ_DIR)/logic.o

$(OBJ_DIR)/ui.o: $(SRC_DIR)/ui.c $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui.c -o $(OBJ_DIR)/ui.o

$(OBJ_DIR)/file.o: $(SRC_DIR)/file.c $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/file.c -o $(OBJ_DIR)/file.o


clean:
	@echo 
	@if exist "$(OBJ_DIR)" rmdir /S /Q "$(OBJ_DIR)" 2>nul
	@if exist "bin" rmdir /S /Q "bin" 2>nul
	@echo 


run: $(TARGET)
	$(TARGET)


rebuild: clean all


help:
	@echo :
	@echo   mingw32-make        
	@echo   mingw32-make clean  
	@echo   mingw32-make run    
	@echo   mingw32-make rebuild 
	@echo   mingw32-make help   

.PHONY: all clean run rebuild help create_dirs