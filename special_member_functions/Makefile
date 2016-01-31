# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: explicit \
     default_constructor \
     copy_constructor \
     copy_assignment_operator \
     move_constructor \
     move_assignment_operator

clean:
	-rm explicit
	-rm default_constructor
	-rm copy_constructor
	-rm copy_assignment_operator
	-rm move_constructor
	-rm move_assignment_operator

explicit: explicit.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
	
default_constructor: default_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
	
copy_constructor: copy_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@

copy_assignment_operator: copy_assignment_operator.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
	
move_constructor: move_constructor.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
	
move_assignment_operator: move_assignment_operator.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@