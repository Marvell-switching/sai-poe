# Main Makefile for Ros Over linux (BM + WM)

SHELL := /bin/bash

.PHONY: all
all: wm bm gm

.PHONY: clean
clean: wm_clean bm_clean gm_clean

gm:
	$(MAKE) -f Makefile_bm GREY_MODE=yes

wm_clean:
	$(MAKE) -f Makefile_wm clean

bm_clean:
	$(MAKE) -f Makefile_bm clean

gm_clean:
	$(MAKE) -f Makefile_bm GREY_MODE=yes clean

.PHONY: no_targets__ list
no_targets__:
list:
	@sh -c "make -p no_targets__ | awk -F':' '/^[a-zA-Z0-9][^\$$#\/\\t=]*:([^=]|$$)/ {split(\$$1,A,/ /);for(i in A)print A[i]}' | egrep -v '__\$$|Makefile|make|\%' | sort"

############################################################
bm::
	$(MAKE) -f Makefile_bm all
	
wm::
	$(MAKE) -f Makefile_wm all
############################################################

