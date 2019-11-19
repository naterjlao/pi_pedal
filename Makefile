INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
CC=gcc
CFLAGS=-I$(INC_DIR)
RFLAGS=-rvf

all: main.x

main.x: $(SRC_DIR)/main.c $(OBJ_DIR)/gpio.o
	$(CC) $(SRC_DIR)/main.c $(OBJ_DIR)/gpio.o $(CFLAGS) -o main.x

$(OBJ_DIR)/gpio.o: $(SRC_DIR)/gpio_setup.c
	$(CC) $(SRC_DIR)/gpio.c -c $(CFLAGS) -o $(OBJ_DIR)/gpio.o

clean:
	rm $(RFLAGS) *.x $(OBJ_DIR)/*

