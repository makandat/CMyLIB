#!/bin/bash

gcc -g -std=c11 -o ./bin/$1 $1.c ./bin/mylib.so

