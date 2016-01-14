# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: matrix_multiply

clean:
	rm matrix_multiply

matrix_multiply: matrix_multiply.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@