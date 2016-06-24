CC=gcc
CFLAGS=-c -Wall -std=c99
OFLAGS=-lm -g
TFLAGS= -Wall -std=c99 -lm -g -D_XOPEN_SOURCE=600
OUT= myShell
PROG= main

all: test

#for the C -myar program
prog: myar.o
	${CC} ${PROG}.o ${OFLAGS} -o ${OUT}

myar.o: myar.c 
	${CC} ${CFLAGS} ${PROG}.c 

test: main.c
	${CC} ${TFLAGS} ${PROG}.c -o ${OUT}

#witchcraft is no more
clean:
	rm -f *.o myShell 
