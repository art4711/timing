.PHONY: all run-test
COPTS=-Wall -O2

all: run-test

.c.o:
	cc $(COPTS) -c $<

run-test: swtest sttest
	./swtest
	./sttest

swtest: stopwatch_test.o stopwatch_mach.o
	cc -o $@ stopwatch_test.o stopwatch_mach.o -lm

sttest: state_timer_test.o stopwatch_mach.o
	cc -o $@ state_timer_test.o stopwatch_mach.o -lm
