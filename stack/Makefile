# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: stack

clean:
	rm stack

stack: stack.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@