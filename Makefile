# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic

all: main

main: lexer.cpp
	$(CXX) $(CXXFLAGS) -o main lexer.cpp

clean:
	rm -f main