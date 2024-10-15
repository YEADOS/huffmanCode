# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -pthread

# Google Test linking flags
GTEST_FLAGS = -lgtest -lgtest_main

# Executable name
TEST_TARGET = tests

# Source files
SOURCES = huffman.cpp main.cpp

# Build the test executable
$(TEST_TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TEST_TARGET) $(GTEST_FLAGS)

# Clean compiled files
clean:
	rm -f $(TEST_TARGET)

# Phony targets to avoid conflicts with files of the same name
.PHONY: clean
