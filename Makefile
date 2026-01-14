CC = gcc
CFLAGS = -Wall -Wextra -Ilib
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o) build/main.o
TARGET = build/emulador

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(TARGET)
