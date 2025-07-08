# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
TARGET = $(BIN_DIR)/app

# Default target
all: dirs $(TARGET)

# Create necessary directories
dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean dirs

# Show help
help:
	@echo "Available targets:"
	@echo "  all    : Build the project (default)"
	@echo "  clean  : Remove build files"
	@echo "  help   : Show this help message"
