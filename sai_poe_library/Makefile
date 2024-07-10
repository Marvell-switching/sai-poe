# Specify the compiler
CC := /swtools/devtools/gnueabi/arm_le/arm-none-linux-gnueabi-versions/gcc-arm-10.1-2020.6-x86_64-aarch64-marvell-linux/bin/aarch64-marvell-linux-gnu-gcc
#CC := gcc

# Compiler flags
CFLAGS = -g -O0 -I. -I./PDLIB -I./h -I./PDLIB/h/ -I./SAI -I./SAI/inc -I./SAI/experimental -I./SAI/meta -fPIC

# Directory for object files
OBJ_DIR := build

# Sources to exclude
EXCLUDE_DIR := ./SAI/meta

# Find all .c files in SRC_DIR but exclude those in EXCLUDE_DIR
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c' -not -path '$(EXCLUDE_DIR)/*')


# List of source files
# SRCS := $(shell find . -type f -name '*.c')

# List of object files (one for each source file)
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Linker flags

# PATHS = /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/common/libs/COMMON.a \
    # /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/mainPpDrv/libs/MAINPPDRV.a \
	# /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/mainExtUtils/libs/MAINEXTUTILS.a \
    # /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/cpssEnabler/libs/CPSSENABLER.a \
	# /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/referenceCode/libs/REFERENCECODE.a \
	# /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/mainLuaWrapper/libs/MAINLUAWRAPPER.a \

# PATHS = \
	# /local/store/sai_cpss/dist/armv8/libXdkCpss.a \
	# /local/store/sai_cpss/dist/armv8/libCpssEnablerNoMain.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/common/libs//COMMON.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/mainPpDrv/libs//MAINPPDRV.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/mainExtUtils/libs//MAINEXTUTILS.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/embeddedCommands/libs//EMBEDDEDCOMMANDS.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/simulation/libs/SIMULATION.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/mainTmDrv/libs//MAINTMDRV.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/mainGaltisWrapper/libs//MAINGALTISWRAPPER.a \
	# /local/store/sai_cpss/cpss/compilation_root/HEAD/sim64_DX/mainLuaWrapper/libs//MAINLUAWRAPPER.a \

PATHS = \
	#/local/store/sai_cpss/dist/native/libXdkXps.so \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/libcpss.so \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/libhelper.so \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/GTOS.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/GTSTACK.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/common/libs/COMMON.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/mainPpDrv/libs/MAINPPDRV.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/MAINEXTDRV.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/MAINEXTDRVSHARED.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/GTUTIL.a \
	/local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX_SHARED/cpssEnabler/libs/SHRMEMINTRACPSSDATA.a \
	
	
LDFLAGS := -shared -lpthread $(PATHS)
#LDFLAGS := -shared -lpthread  /local/store/cpss_4.3/compilation_root/cpss_4.3/armv8_DX/common/libs/COMMON.a 
#LDFLAGS := -shared -lpthread /local/store/sai-poe/sai-poe/usr/lib/libXdkCpss.a /local/store/sai-poe/sai-poe/usr/lib/CPSSENABLER.a /local/store/sai-poe/sai-poe/usr/lib/MAINPPDRV.a /local/store/sai-poe/sai-poe/usr/lib/COMMON.a
#LDFLAGS := -shared -lpthread /local/store/sai-poe/sai-poe/usr/lib/libcpss.so /local/store/sai-poe/sai-poe/usr/lib/libhelper.so
#LDFLAGS := -shared -lpthread /local/store/sai-poe/sai-poe/usr/lib/CPSSENABLER.a /local/store/sai-poe/sai-poe/usr/lib/MAINPPDRV.a

# Target for the shared library
TARGET := libsai.so

# Default target
all: $(TARGET)

# Rule to build the shared library
$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -Wl,-e$(ENTRY_POINT) -o $@

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
