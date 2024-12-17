# Specify the compiler
CCC ?= aarch64-linux-gnu-gcc

# Compiler flags
CFLAGS = -g -O0 -I. -I./PDLIB -I./h -I./PDLIB/h/ -I./SAI -I./SAI/inc -I./SAI/experimental -I./SAI/meta -fPIC

# Directory for object files
OBJ_DIR := build

# Sources to exclude
EXCLUDE_DIR := ./SAI/meta

# Find all .c files in SRC_DIR but exclude those in EXCLUDE_DIR
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '$(EXCLUDE_DIR)/*')

# List of object files (one for each source file)
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# List of libraries
PATHS ?= ../poelibsai-debian/usr/lib/libapp_scpu.a

# Linker flags
LDFLAGS := -shared -lpthread $(PATHS)

# Target for the shared library
TARGET := libsai.so

# Default target
all: $(TARGET)

# Rule to build the shared library
$(TARGET): $(OBJS)
	$(CCC) $^ $(LDFLAGS) -o $@

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CCC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Phony target to clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
