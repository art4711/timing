OSNAME ?= $(shell uname -s)
OSNAME := $(shell echo $(OSNAME) | tr A-Z a-z)
COPTS=-Wall -O2

all: run-test

.c.o:
	cc $(COPTS) -c $<

run-test: swtest sttest
	./swtest
	./sttest

include Makefile.$(OSNAME)

clean:
	rm -rf *.o swtest sttest *.core

.PHONY: all run-test
