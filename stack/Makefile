# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: stack stl template

clean:
	-rm stack
	-rm stack.o
	-rm -rf stack.dSYM
	-rm stl
	-rm stl.o
	-rm -rf stl.dSYM
	-rm template
	-rm template.o
	-rm -rf template.dSYM

lint: stack.cpp stl.cpp template.cpp
	$(LINT) $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -c

stack: stack.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

stl: stl.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
	
template: template.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
