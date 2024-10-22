# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable name
TARGET = main.out

# Source and Object Files
SRCS = HashTable.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target to build the program
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid filename conflicts
.PHONY: all clean
