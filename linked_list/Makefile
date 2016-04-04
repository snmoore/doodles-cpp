# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: double single stl template 

clean:
	-rm double
	-rm double.o
	-rm -rf double.dSYM
	-rm single
	-rm single.o
	-rm -rf single.dSYM	
	-rm stl
	-rm stl.o
	-rm -rf stl.dSYM
	-rm template
	-rm template.o
	-rm -rf template.dSYM

lint: double.cpp single.cpp stl.cpp template.cpp
	$(LINT) $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -c

double: double.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

single: single.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

stl: stl.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
	
template: template.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
