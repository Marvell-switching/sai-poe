MODULES := 

FILES := \
 pdlibLib.c \
 pdlLibLinkedList.c \
 pdlLibArray.c \
 pdlLibMd5.c

CWD := $(dir $(lastword $(MAKEFILE_LIST)))
PDL_SRC += $(patsubst %,$(CWD)%,$(FILES))
include $(patsubst %,$(CWD)%/$(MAKEFILE),$(MODULES))

