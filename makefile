# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Target executable
TARGET = program

# Source files
SRCS = Main.cpp UI.cpp changeItem.cpp controlModule.cpp changeRequest.cpp User.cpp Product.cpp Release.cpp

# Object files (automatically generated from the source files)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files and .dat files
clean:
	rm -f $(OBJS) $(TARGET) *.dat

# Additional clean target to remove .dat files only
clean-dat:
	rm -f *.dat

# Phony targets (targets that don't correspond to actual files)
.PHONY: all clean clean-dat
