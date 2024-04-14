# New Makefile for Ros Over linux WM
#

VC_CROSS_COMPILE = x86_64-w64-mingw32-
CL = $(VC_CROSS_COMPILE)gcc
LINK = $(VC_CROSS_COMPILE)gcc
LIB = $(VC_CROSS_COMPILE)ar

CC = $(CL)
LD = $(LINK)
AR = $(LIB)

GNU_CROSS_COMPILE = x86_64-w64-mingw32-
GNU_CC = $(GNU_CROSS_COMPILE)gcc
GNU_LD = $(GNU_CROSS_COMPILE)gcc
GNU_AR = $(GNU_CROSS_COMPILE)ar

ECHO = echo
MKDIR = mkdir -p
CP = cp -f
RM = rm -rf
MV = mv

# Name of makefile to include in each sub-module
MAKEFILE := Makefile

###############################################################################

MODULES := \
	src

ifdef ADD_PREFIX_TO_CODE
PDLPREFIX_FLAG=-D"PDLIBPREFIX"=$(ADD_PREFIX_TO_CODE)
endif

GNU_DEBUG_CFLAGS = -g -O0
GNU_BASE_CFLAGS	= $(DEBUG_CFLAGS) -Wall -Wno-comment -Wno-pointer-sign -Wno-format -Werror $(PDLPREFIX_FLAG)
GNU_CFLAGS = $(GNU_BASE_CFLAGS) -Wno-pointer-sign -Wunused-variable
BASE_CFLAGS = -g

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
	@ echo MD $<
@# create dependency file
	@$(ECHO) $(GNU_CC) -MM -c $1 $< -o $2/$*.$(DEP_EXTENSION)
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
	@ $(ECHO) $(CL) -c $1 $< -o $@
	@ $(CL) -c $1 $< -o $@
endef

define make_lib
	@ $(MKDIR) $(dir $@)
	@ $(ECHO) AR $@
	@ $(AR) -crs $@ $^
endef

define make_lib_from_obj_list
	@ $(MKDIR) $(dir $@)
	@ $(ECHO) AR $@
	@ $(AR) -crUus $@ $1
endef

PDL_SRC :=
DEP :=
include $(patsubst %,%/$(MAKEFILE),$(MODULES))

GNU_CFLAGS += $(filter -D%,$(CFLAGS))
GNU_CFLAGS += $(filter -I%,$(CFLAGS))
VC_CFLAGS += $(filter -D%,$(CFLAGS))
VC_CFLAGS += $(filter -I%,$(CFLAGS))
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
