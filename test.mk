bin/test : test.c bin/mylib.so
	gcc -g -std=c11 -o bin/test test.c bin/mylib.so

