##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# espial makefile fragments 
##############################################################################

#
# Defines
#

ifndef CONF_ESPIAL_SDK_VERSION
CONF_ESPIAL_SDK_VERSION := 20101007
endif

ESPIAL_SDK := ESPIAL_SDK_SIGMA_$(CONF_ESPIAL_SDK_VERSION)
ESPIAL_SDK_DIR := $(TOP_LIBS_DIR)/espial_browser/
ESPIAL_SDK_SOURCE := $(ESPIAL_SDK_DIR)/ESPIAL_SDK_SIGMA387_$(CONF_ESPIAL_SDK_VERSION)
ESPIAL_SERVER_URL  := $(TOP_LIBS_URL)/espial_browser


#To be compatible with the arm toolchain which renamed the arm-elf-cpp with cpp, 
# add following code to support cross platform

#
# Download  the source 
#
.PHONY: espial-downloaded

espial-downloaded: $(TOP_LIBS_DIR)/.espial_downloaded

$(TOP_LIBS_DIR)/.espial_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: espial-unpacked

espial-unpacked: $(TOP_LIBS_DIR)/.espial_unpacked

$(TOP_LIBS_DIR)/.espial_unpacked: $(TOP_LIBS_DIR)/.espial_downloaded $(wildcard $(ESPIAL_SDK_SOURCE)/*.bz2)
	@touch $@

#
# Patch the source
#
.PHONY: espial-patched

espial-patched: $(TOP_LIBS_DIR)/.espial_patched

$(TOP_LIBS_DIR)/.espial_patched: $(TOP_LIBS_DIR)/.espial_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: espial-config


#
# Configuration
#
.PHONY: espial-configured


#
# Compile
#
.PHONY: espial-compile


espial-compile: $(TOP_LIBS_DIR)/.espial_compiled

$(TOP_LIBS_DIR)/.espial_compiled: $(TOP_LIBS_DIR)/.espial_patched
	@touch $@

#
# Update
#
.PHONY: espial-update

espial-update:
	@echo "Updating espial_browser ..."
	@if [ -d "$(ESPIAL_SDK_DIR)" ]; then\
		$(TOP_UPDATE) $(ESPIAL_SDK_DIR); \
	fi
	@echo "Updating espial_browser done"

#
# Status
#
.PHONY: espial-status


#
# Clean
#
.PHONY: espial-clean


#
# Dist clean
#
.PHONY: espial-distclean

espial-distclean:
	@rm -f $(TOP_LIBS_DIR)/.espial_*

#
# Install
#
.PHONY: espial-install

espial-install:

