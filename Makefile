# Compiler
CXX := clang++

# Determine the operating system
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -Werror

# Source files
SOURCES := $(wildcard src/*.cpp src/**/*.cpp)

# Header files
HEADERS := $(wildcard src/*.h src/**/*.h include/*.h)

# Object files
OBJECTS := $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE := tscompiler

# Output directory
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin

# Default target
all: $(BIN_DIR)/$(EXECUTABLE)

# Determine platform-specific flags
ifeq ($(UNAME_S),Darwin)
    # macOS
    CXXFLAGS += -mmacosx-version-min=10.9
    ifeq ($(UNAME_M),arm64)
        CXXFLAGS += -arch arm64
    else
        CXXFLAGS += -arch x86_64
    endif
else ifeq ($(UNAME_S),Linux)
    # Linux
    ifeq ($(UNAME_M),aarch64)
        CXXFLAGS += -march=armv8-a
    else
        CXXFLAGS += -march=x86-64
    endif
else ifeq ($(OS),Windows_NT)
    # Windows (assuming MSYS2 or similar environment)
    ifeq ($(UNAME_M),aarch64)
        CXXFLAGS += -march=armv8-a
    else
        CXXFLAGS += -march=x86-64
    endif
    EXECUTABLE := $(EXECUTABLE).exe
endif

# Link the executable
$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(OBJECTS) $(SOURCES:.cpp=.d)

# Phony targets
.PHONY: all clean test install

# Help target
help:
	@echo "Available targets:"
	@echo "  all        : Build the executable (default target)"
	@echo "  clean      : Remove object files and executable"
	@echo "  test       : Run tests"
	@echo "  install    : Install the executable"
	@echo "  help       : Display this help message"

# Run target
run: $(BIN_DIR)/$(EXECUTABLE)
	$(BIN_DIR)/$(EXECUTABLE)

# Debug target
debug: CXXFLAGS += -g
debug: clean all

# Test target
test: $(BIN_DIR)/$(EXECUTABLE)
	@echo "Running tests..."
	@$(BIN_DIR)/$(EXECUTABLE) --test

# Install target
install: $(BIN_DIR)/$(EXECUTABLE)
	@echo "Installing to /usr/local/bin..."
	@sudo cp $(BIN_DIR)/$(EXECUTABLE) /usr/local/bin/

# Include dependencies
-include $(OBJECTS:.o=.d)

# Generate dependency files
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) -MM -MT $(@:.d=.o) $< > $@
