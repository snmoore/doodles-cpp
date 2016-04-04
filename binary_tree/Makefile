# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: binary_tree stl template

clean:
	-rm binary_tree
	-rm binary_tree.o
	-rm -rf binary_tree.dSYM
	-rm stl
	-rm stl.o
	-rm -rf stl.dSYM
	-rm template
	-rm template.o
	-rm -rf template.dSYM

lint: binary_tree.cpp stl.cpp template.cpp
	$(LINT) $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -c

binary_tree: binary_tree.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

stl: stl.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
	
template: template.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
