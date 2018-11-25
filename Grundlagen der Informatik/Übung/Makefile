CC = gcc
CFLAGS = -Wall

BINARY = $(wildcard *.class) $(wildcard *.out)

.PHONY: all

all: aufgabe-22

%.class: %.java
	javac $^

%.out: %.c
	$(CC) -o $@ $^ $(CFLAGS)

cleanall: $(BINARY)
	rm $^

clean:

aufgabe-22: Aufgabe-22.class Aufgabe-22.out
