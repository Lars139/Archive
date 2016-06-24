CC=gcc
CFLAGS=-c -Wall -std=c99
OFLAGS=-lm -g
TFLAGS= -Wall -std=c99 -lm -g -D_XOPEN_SOURCE=600
OUT= myar
PROG= myar

all: test

#for the C -myar program
prog: myar.o
	${CC} ${PROG}.o ${OFLAGS} -o ${OUT}

myar.o: myar.c 
	${CC} ${CFLAGS} ${PROG}.c 

test: myar.c
	${CC} ${TFLAGS} ${PROG}.c -o ${OUT}

#witchcraft is no more
clean:
	rm -f *.o myar ?
	rm -f tempfile*
