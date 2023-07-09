TARGET=bin/mylib.so
SRC=my_object.c my_console.c
OPT = -g -Wall -fpic -shared -std=c11 -o $@
$(TARGET):$(SRC)
	gcc $(OPT) $(SRC)
