# See https://www.gnu.org/prep/standards/html_node/Makefile-Basics.html#Makefile-Basics
SHELL = /bin/sh

SOURCES=matrix_multiply.cpp
TARGET=matrix_multiply
CFLAGS+=-std=c++11 -Wall -Wextra -Wpedantic -g
LINT=scan-build -v

.SUFFIXES:
.SUFFIXES: .cpp .o

.PHONY: all clean lint

all: $(TARGET)

clean:
	-rm $(TARGET)
	-rm -rf $(TARGET).dSYM

lint: $(SOURCES)
	$(LINT) $(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@
