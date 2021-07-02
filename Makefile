# -*- MakeFile -*-

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g # -DNDEBUG
INC = 
EXEC = prog

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)

PRINT = echo
CREATE_FOLDER = mkdir -p
DELETE_FOLDER = rm -rf

lib: $(OBJ)
	ar rcs bin/libdats.a $^

debug: sandbox/main.c src/dats.h lib
	$(CC) $< -L/home/radam/repos/dats/bin -ldats -o bin/$@ $(CFLAGS)
	./bin/$@

obj/%.o: src/%.c folders
	$(CC) -c $< -o $@ $(CFLAGS)

val: debug
	valgrind --leak-check=full --track-origins=yes ./bin/debug
 
test: lib 
	cmake -S test/ -B test/build
	cmake --build test/build
	ctest --test-dir test/build/ --output-on-failure

.PHONY: clean folders help

help:
	@$(PRINT) "make debug : building the lib and execute and debug program for experimenting."
	@$(PRINT) "make lib     : creating a lib .a from sources."
	@$(PRINT) "make clean   : deleting all non-source files."
	@$(PRINT) "make folders : creating the necessary folders."
	@$(PRINT) "make help    : get help for the commands."

folders:
	$(CREATE_FOLDER) bin
	$(CREATE_FOLDER) obj

clean:
	$(DELETE_FOLDER) bin
	$(DELETE_FOLDER) obj
	$(DELETE_FOLDER) test/build

# $(EXEC): $(OBJ)
# 	$(CC) $^ -o bin/$@ $(CFLAGS)

# lib: $(OBJ)
# 	$(CC) $(CFLAGS) -fPIC -shared -o bin/libents.so $(OBJ) -lc
