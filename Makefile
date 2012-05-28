.PHONY: all run-test
COPTS=-Wall -O2

all: run-test

run-test: swtest
	./swtest

swtest: stopwatch_test.o stopwatch_mach.o
	cc -o $@ stopwatch_test.o stopwatch_mach.o -lm
