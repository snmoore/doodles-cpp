# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: reverse

clean:
	rm reverse

reverse: reverse.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@