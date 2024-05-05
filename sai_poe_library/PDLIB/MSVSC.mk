# New Makefile for Ros Over linux WM
#
export WINEARCH='win32'
export WINEPREFIX ?= $(HOME)/.wine
export WINEDEBUG=-all
export WINEPATH="c:\\windows;c:\\windows\\system32"
WINE := wine

VC_CROSS_COMPILE = /local/store/wine/i686-w64-wine32-vc-
CL = $(VC_CROSS_COMPILE)cl
LINK = $(VC_CROSS_COMPILE)link
LIB = $(VC_CROSS_COMPILE)lib

CC = $(CL)
LD = $(LINK)
AR = $(LIB)

#GNU_CROSS_COMPILE = i686-w64-mingw32-
# used only in order to make dependecies
GNU_CC = $(GNU_CROSS_COMPILE)gcc

ECHO = echo
MKDIR = mkdir -p
CP = cp -f
RM = rm -rf

# Name of makefile to include in each sub-module
MAKEFILE := Makefile

###############################################################################

MODULES := \
	src

ifdef ADD_PREFIX_TO_CODE
PDLPREFIX_FLAG=/D "PDLIBPREFIX"=$(ADD_PREFIX_TO_CODE)
endif

GNU_DEBUG_CFLAGS = -g -O0
GNU_BASE_CFLAGS	= $(DEBUG_CFLAGS) -Wall -Wno-comment -Wno-pointer-sign -Wno-format -Werror $(PDLPREFIX_FLAG)
GNU_CFLAGS = $(GNU_BASE_CFLAGS) -Wno-pointer-sign -Wunused-variable
BASE_CFLAGS = /nologo /W3 /wd4819 /EHsc /Z7 /Od /MTd /c /Zm1000 /D "_WIN32" /D "_VISUALC"

override CFLAGS += $(BASE_CFLAGS)
override CFLAGS += -Ih 

# Function compile(flags, output_folder)
#
# Compile a .c file into .o file using the defined toolchain, including dependecy .d file.
# Object and dependency files will be located together in output_folder,
# under the relative path to the source.
#
# Example: $(call compile $(CFLAGS),/local/objects)
# Source file: foo/bar/baz.c
# Targets: /local/objects/foo/bar/baz.o
#          /local/objects/foo/bar/baz.d

define make_depend
@# Create output folder
	@ $(MKDIR) $(dir $@)
@# print make_depend command
	@ $(ECHO) MD $<
@# create dependency file
	@ $(ECHO) $(GNU_CC) -MM -c $1 $< -o $2/$*.$(DEP_EXTENSION)
	@ $(GNU_CC) -MM -c $1 $< -o $2/$*.$(DEP_EXTENSION)
@# Duplicate it
	@ $(CP) $2/$*.$(DEP_EXTENSION) $2/$*.tmp
@# Create empty rule per file in dependency rule to avoid "No rule to make target ..." Errors
	@ sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/d' -e 's/$$/ :/' < $2/$*.$(DEP_EXTENSION) >> $2/$*.tmp
@# Change object filename to include full path
	@ sed -e 's/$(subst .,\.,$(notdir $*.o))/$(subst /,\/,$2/$*.$(OBJ_EXTENSION))/'  < $2/$*.tmp > $2/$*.$(DEP_EXTENSION)
@# Remove temporary file
	@ $(RM) $2/$*.tmp
endef

define compile
@# Create output folder
	@ $(MKDIR) $(dir $@)
@# print compilation msg
	@ $(ECHO) CL $<
@# compile
	@ $(ECHO) $(CL) $1 /Fd"$(dir $@)" /Fo"$@" $<
	@ $(CL) $1 /Fd"$(dir $@)" /Fo"$@" $<
endef

define make_lib
	@ $(MKDIR) $(dir $@)
	@ $(ECHO) AR $@
	@ $(AR) /OUT:$@ $^
endef

define make_lib_from_obj_list
	@ $(MKDIR) $(dir $@)
	@ $(ECHO) AR $@
	@ $(AR) /OUT:$@ $1
endef

PDL_SRC :=
DEP :=
include $(patsubst %,%/$(MAKEFILE),$(MODULES))

GNU_CFLAGS += $(filter -D%,$(CFLAGS))
GNU_CFLAGS += $(filter -I%,$(CFLAGS))
GNU_CFLAGS += $(patsubst /D"%",-D%,$(filter /D"%",$(CFLAGS)))
GNU_CFLAGS += $(patsubst /I"%",-I%,$(filter /I"%",$(CFLAGS)))

VC_CFLAGS += $(patsubst -D%,/D"%",$(filter -D%,$(CFLAGS)))
VC_CFLAGS += $(patsubst -I%,/I"%",$(filter -I%,$(CFLAGS)))
CFLAGS := $(VC_CFLAGS)

PDLIB_OBJ := $(patsubst %.c,$(OBJ_OUT_DIR)/%.$(OBJ_EXTENSION),$(PDL_SRC))
DEP += $(patsubst %.$(OBJ_EXTENSION),%.$(DEP_EXTENSION),$(PDLIB_OBJ))
###############################################################################
#
# %.obj - compile .c files to objects

$(OBJ_OUT_DIR)/%.$(DEP_EXTENSION): %.c
	$(call make_depend,$(GNU_CFLAGS),$(OBJ_OUT_DIR))

$(OBJ_OUT_DIR)/%.$(OBJ_EXTENSION):  %.c
	$(call make_depend,$(GNU_CFLAGS),$(OBJ_OUT_DIR))
	$(call compile,$(CFLAGS),$(OBJ_OUT_DIR))

###############################################################################
# targets

$(PDLIB_LIB): $(PDLIB_OBJ)
	$(call make_lib)

.PHONY: all
all: $(PDLIB_LIB)

pdlib: $(PDLIB_LIB) 

clean:
	$(RM) $(OUT_DIR)

#######################################################
ifeq ( $(filter $(IGNORED_TARGETS),$(MAKECMDGOALS)),)
-include $(DEP)
endif
print-%  : ; $(ECHO) $* = $($*)
