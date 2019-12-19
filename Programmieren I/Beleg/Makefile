CC = gcc
CFLAGS = -Wall -ansi -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

TARGET ?= phonebook

SRCS := $(wildcard *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
