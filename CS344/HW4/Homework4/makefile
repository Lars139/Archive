CC=gcc
CFLAGS=-c -Wall -std=c99
OFLAGS=-lm -g
TFLAGS= -Wall -std=c99 -lm -g -D_XOPEN_SOURCE=600 -lpthread
OUT= sieve 
PROG= main

all: main1 main2 

#for the C -myar program
prog: myar.o
	${CC} ${PROG}.o ${OFLAGS} -o ${OUT}

myar.o: myar.c 
	${CC} ${CFLAGS} ${PROG}.c 

main1: main.c
	${CC} ${TFLAGS} ${PROG}.c -o ${OUT}
main2: shared.c
	${CC} -std=c99 -g -D_XOPEN_SOURCE=600 -lrt shared.c -o shared_memory

#witchcraft is no more
clean:
	rm -f *.o sieve shared_memory
