# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: copy_assignment_operator \
     copy_constructor \
     default_constructor \
     explicit \
     move_assignment_operator \
     move_constructor

clean:
	-rm copy_assignment_operator
	-rm copy_assignment_operator.o
	-rm -rf copy_assignment_operator.dSYM
	-rm copy_constructor
	-rm copy_constructor.o
	-rm -rf copy_constructor.dSYM
	-rm default_constructor
	-rm default_constructor.o
	-rm -rf default_constructor.dSYM
	-rm explicit
	-rm explicit.o
	-rm -rf explicit.dSYM	
	-rm move_assignment_operator
	-rm move_assignment_operator.o
	-rm -rf move_assignment_operator.dSYM
	-rm move_constructor
	-rm move_constructor.o
	-rm -rf move_constructor.dSYM	

lint: copy_assignment_operator.cpp \
      copy_constructor.cpp \
      default_constructor.cpp \
      explicit.cpp \
      move_assignment_operator.cpp \
      move_constructor.cpp
	$(LINT) $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -c

copy_assignment_operator: copy_assignment_operator.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

copy_constructor: copy_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

default_constructor: default_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

explicit: explicit.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
	
move_assignment_operator: move_assignment_operator.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@

move_constructor: move_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
