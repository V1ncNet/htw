FILENAME=Grundlagen-der-Informatik-Vorlesung
SHELL=/bin/bash

.PHONY: $(FILENAME).pdf all clean


all: $(FILENAME).pdf


%.tex: %.raw
	./raw2tex $< > $@

%.tex: %.dat
	./dat2tex $< > $@


$(FILENAME).pdf: $(FILENAME).tex
	latexmk -pdf -pdflatex="pdflatex -interactive=nonstopmode" -use-make $<

cleanall:
	latexmk -C

clean:
	latexmk -c

watch:
	while true; do                      \
		make all --silent;              \
		inotifywait -qre close_write .; \
		done
