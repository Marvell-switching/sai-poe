MODULES := \
 pdlib

FILES := 

CWD := $(dir $(lastword $(MAKEFILE_LIST)))
PDL_SRC += $(patsubst %,$(CWD)%,$(FILES))
include $(patsubst %,$(CWD)%/$(MAKEFILE),$(MODULES))

