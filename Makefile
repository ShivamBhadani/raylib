CC = gcc
LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm -lm

SRC ?= main.c
OBJ =
OUT ?= main.exe

$(OUT): $(SRC)
	$(CC) $(SRC) $(OBJ) -o $(OUT) $(CFLAGS) $(LDFLAGS)
