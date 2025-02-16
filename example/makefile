# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../include/common -I../include/shapes -I../include/external -fopenmp -O2 -MMD -MP
LDFLAGS = -fopenmp
SOURCES = $(wildcard *.cpp) $(wildcard ../src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = example

# Main target
all: $(EXECUTABLE)

# Linking the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

# Compiling source files with dependencies
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Include dependencies
-include $(OBJECTS:.o=.d)
