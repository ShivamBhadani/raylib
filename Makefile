CC = gcc
LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm

SRC ?= main.c
OUT = main.exe

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)
