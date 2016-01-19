# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: binary_tree template

clean:
	rm binary_tree
	rm template

binary_tree: binary_tree.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
	
template: template.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@