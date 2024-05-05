# Specify the compiler
CC := gcc

# Compiler flags
CFLAGS := -g -I. -I./PDLIB -I./h -I./PDLIB/h/

# Linker flags
LDFLAGS := -pthread

# Directory for object files
OBJ_DIR := obj

# List of source files
SRCS := $(shell find . -type f -name '*.c')

# List of object files (one for each source file)
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Target for the executable
TARGET := my_program

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Phony target to clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
