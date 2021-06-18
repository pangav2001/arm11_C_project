#Makefile

CC = gcc
CFLAGS = -Wall -g -Werror -pedantic
BUILD = priority_test

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)

priority_test: priority_test.o testutils.o ../priority_queue.o

testutils.o: testutils.h
../priority_queue.o : ../priority_queue.h


clean:
	rm -f $(wildcard *.o)
	rm -f ../priority_queue.o
	rm -f priority_test