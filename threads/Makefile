# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: posix threads

clean:
	-rm posix
	-rm posix.o
	-rm -rf posix.dSYM
	-rm threads
	-rm threads.o
	-rm -rf threads.dSYM

lint: posix.cpp threads.cpp
	$(LINT) $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -c

posix: posix.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

threads: threads.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
