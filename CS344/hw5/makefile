CC=gcc
CFLAGS=-c -Wall -std=c99
OFLAGS=-lm -g
TFLAGS= -Wall -std=c99 -lm -g -D_XOPEN_SOURCE=600 -lpthread
OUT= thread_p 
OUT1= server
OUT2= client
PROG= pthread
PROG1= server
PROG2= client

all: main1 main2 main3 main4

main1: pthread.c
	${CC} ${TFLAGS} ${PROG}.c -o ${OUT}
main2: server.c
	${CC} ${TFLAGS} ud_ucase.h ${PROG1}.c -o ${OUT1}
main3: client.c
	${CC} ${TFLAGS} ${PROG2}.c -o player1
main4: client1.c
	${CC} ${TFLAGS} client1.c -o player2 

#witchcraft is no more
clean:
	rm -f *.o player1 player2 server hw5_sock_* thread_p
