# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o

CFLAGS +=-std=c++11 -Wall -Wextra -Wpedantic

all: linked_list

clean:
	rm linked_list

linked_list: linked_list.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@