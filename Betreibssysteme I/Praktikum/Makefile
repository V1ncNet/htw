CC = gcc
CFLAGS = -Wall

BINARY = $(wildcard *.class) $(wildcard *.out)

.PHONY: all

all: praktikum-06

%.class: %.java
	javac $^

%.out: %.c
	$(CC) -o $@ $^ $(CFLAGS)

cleanall: $(BINARY)
	rm $^

clean:

praktikum-06: 062-fibonacci.class 062-fibonacci_alt.class 062-fibonacci.out
