# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

CFLAGS+=-std=c++11 -g -Wall -Wextra -Wpedantic -pedantic-errors
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: $(target)

clean:
	-rm $(target)
	-rm -rf $(target).dSYM

lint: $(sources)
	$(LINT) $(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $(target)

$(target): $(sources)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
