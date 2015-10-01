#using gcc compiler
CC = gcc

#output path and filename
BINARY = ./build/miniGoogle

#sources directory
SRC = src/google.c src/input.c src/menu.c src/minigoogle.c

#includes directory
INCLUDES = ./includes

#libraries and flags
LIBS = -lm
FLAGS = -Wall -g

all: compile run

compile:
	$(CC) -o $(BINARY) -I$(INCLUDES) $(SRC) $(LIBS)

run:
	$(BINARY)

clean:
	rm *.o