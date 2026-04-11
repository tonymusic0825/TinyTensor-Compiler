CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic

main: test.o lexer.o
	$(CXX) $(CXXFLAGS) -o main test.o lexer.o

test.o: test.cpp lexer.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

lexer.o: lexer.cpp lexer.h
	$(CXX) $(CXXFLAGS) -c lexer.cpp -o lexer.o

clean:
	rm -f *.o main