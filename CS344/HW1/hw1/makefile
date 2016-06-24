CC=gcc
CFLAGS=-c -Wall -std=c99
OFLAGS=-lm -g
OUT=sieve
PDF=hw1_write_up
PROG=prime

all: prog pdf

#this is for the pdf file
pdf: 
	latex ${PDF}.tex
	latex ${PDF}.tex
	#.dvi to .ps
	dvips -R -Poutline -t letter ${PDF}.dvi -o ${PDF}.ps
	#.ps to .pdf
	ps2pdf ${PDF}.ps
	#remove the voodoo magic script
	rm -f ${PDF}.aux
	rm -f ${PDF}.log
	rm -f ${PDF}.out

#for the C -prime program
prog: prime.o
	${CC} ${PROG}.o ${OFLAGS} -o ${OUT}

prime.o: prime.c 
	${CC} ${CFLAGS} ${PROG}.c 

#witchcraft is no more
clean:
	rm -f ${PDF}.aux ${PDF}.log ${PDF}.out ${PDF}.dvi ${PDF}.ps ${PDF}.pdf 
	rm -f *.o sieve
