TARGET=bin/cmylib.so
SRC=my_object.c my_console.c my_convert.c my_string.c my_collections.c my_filesystem.c my_misc.c my_object.h my_console.h my_convert.h my_string.h my_collections.h my_filesystem.h my_misc.h
OPT = -g -Wall -fpic -shared -std=c11 -o $@
$(TARGET):$(SRC)
	gcc $(OPT) $(SRC)
