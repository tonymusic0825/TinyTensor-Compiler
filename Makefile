CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic

OBJS = test.o lexer.o
TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule for building object files with header dependencies
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include generated dependency files
-include $(OBJS:.o=.d)

clean:
	rm -f *.o *.d $(TARGET)