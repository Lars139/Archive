TARGET=ECE472_sawaspar_final_paper

annot.pdf: ${TARGET}.tex ${TARGET}.bib
	pdflatex ${TARGET}
	pygmentize -f latex -o ha.c.tex ha.c
	bibtex ${TARGET}
	pdflatex ${TARGET}
	pdflatex ${TARGET}

clean:
	rm -rf ${TARGET}.{log,pdf,blg,bbl,aux}
