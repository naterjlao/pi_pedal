INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
CC=gcc
CFLAGS=-I$(INC_DIR)
RFLAGS=-rvf

all: main.x

main.x: $(SRC_DIR)/main.c $(OBJ_DIR)/gpio_setup.o
	$(CC) $(SRC_DIR)/main.c $(OBJ_DIR)/gpio_setup.o $(CFLAGS) -o main.x

$(OBJ_DIR)/gpio_setup.o: $(SRC_DIR)/gpio_setup.c
	$(CC) $(SRC_DIR)/gpio_setup.c -c $(CFLAGS) -o $(OBJ_DIR)/gpio_setup.o

clean:
	rm $(RFLAGS) *.x $(OBJ_DIR)/*
