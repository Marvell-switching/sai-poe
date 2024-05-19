# Specify the compiler
CC := /swtools/devtools/gnueabi/arm_le/arm-none-linux-gnueabi-versions/gcc-arm-10.1-2020.6-x86_64-aarch64-marvell-linux/bin/aarch64-marvell-linux-gnu-gcc
LD := /swtools/devtools/gnueabi/arm_le/arm-none-linux-gnueabi-versions/gcc-arm-10.1-2020.6-x86_64-aarch64-marvell-linux/bin/aarch64-marvell-linux-gnu-gcc

# Compiler flags
CFLAGS := -g -I. -I./PDLIB -I./h -I./PDLIB/h/ -fPIE

# Directory for object files
OBJ_DIR := obj

# List of source files
SRCS := $(shell find . -type f -name '*.c')

# List of object files (one for each source file)
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Linker flags
LDFLAGS := -lpthread -Xlinker --whole-archive /local/store/sai-poe/sai_poe_library/COMMON.a /local/store/sai-poe/sai_poe_library/MAINPPDRV.a /local/store/sai-poe/sai_poe_library/MAINEXTUTILS.a /local/store/sai-poe/sai_poe_library/MAINLUAWRAPPER.a /local/store/sai-poe/sai_poe_library/REFERENCECODE.a /local/store/sai-poe/sai_poe_library/CPSSENABLER.a -Xlinker --no-whole-archive -ldl -lc -lm -lrt -lssp

# Target for the executable
TARGET := my_program

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(LD) $^ $(LDFLAGS) --entry main_menu -o $@

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	echo "$(CC) $(CFLAGS) -c $< -o $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Phony target to clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
