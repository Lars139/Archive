TARGET=ECE472_writeup_sawaspar

default: pdf

dvi: ${TARGET}.tex
	latex ${TARGET}.tex

ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

pdf: ps
	ps2pdf ${TARGET}.ps
	make clean_almost

clean_almost:
	rm ${TARGET}.dvi ${TARGET}.log ${TARGET}.aux ${TARGET}.out *.ps 

