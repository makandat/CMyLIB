TARGET=bin/mylib.so
SRC=my_object.c my_console.c my_convert.c my_object.h my_console.h my_convert.h
OPT = -g -Wall -fpic -shared -std=c11 -o $@
$(TARGET):$(SRC)
	gcc $(OPT) $(SRC)
