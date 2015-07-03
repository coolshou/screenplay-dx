##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author: 
# cpulimit makefile fragments 
##############################################################################

#
# Defines
#



CPULIMIT_DIR	:= $(TOP_LIBS_DIR)/cpulimit
CPULIMIT_SOURCE	:= cpulimit
CPULIMIT_SOURCE_DIR	:= $(CPULIMIT_DIR)/cpulimit
CPULIMIT_SERVER_URL  := $(TOP_LIBS_URL)/cpulimit


#To be compatible with the arm toolchain which renamed the arm-elf-cpp with cpp, 
# add following code to support cross platform

#
# Download  the source 
#
.PHONY: cpulimit-downloaded

cpulimit-downloaded: $(TOP_LIBS_DIR)/.cpulimit_downloaded

$(TOP_LIBS_DIR)/.cpulimit_downloaded:
	@echo "Downloading $(CPULIMIT_SOURCE).tar.gz from $(TOP_LIBS_URL)/cpulimit ..."
	@if [ ! -d "$(CPULIMIT_DIR)" ]; then \
		$(TOP_DOWNLOAD) $(CPULIMIT_SERVER_URL); \
	fi
	@echo "Downloading $(CPULIMIT_SOURCE).tar.gz done"
	@touch $@

#
# Unpack the source
#
.PHONY: cpulimit-unpacked

cpulimit-unpacked: $(TOP_LIBS_DIR)/.cpulimit_unpacked

$(TOP_LIBS_DIR)/.cpulimit_unpacked: $(TOP_LIBS_DIR)/.cpulimit_downloaded $(wildcard $(CPULIMIT_DIR)/*.gz)
	@echo "Unpacking $(CPULIMIT_SOURCE) ..."
	cd $(CPULIMIT_DIR);tar jvxf $(CPULIMIT_SOURCE).tar.gz
	@echo "Unpacking $(CPULIMIT_SOURCE) done"
	@touch $@


#
# Patch the source
#
.PHONY: cpulimit-patched

cpulimit-patched: $(TOP_LIBS_DIR)/.cpulimit_patched

$(TOP_LIBS_DIR)/.cpulimit_patched:
	# Patching...
	@touch $@

#
# config
#
.PHONY: cpulimit-config

cpulimit-config: 

#
# Configuration
#
.PHONY: cpulimit-configured

cpulimit-configured:

$(TOP_LIBS_DIR)/.cpulimit_configured:
	@touch $@

#
# Compile
#
.PHONY: cpulimit-compile


cpulimit-compile: $(TOP_LIBS_DIR)/.cpulimit_compiled

$(TOP_LIBS_DIR)/.cpulimit_compiled: $(TOP_LIBS_DIR)/.cpulimit_unpacked
	@echo "Compiling cpulimit ..."
	make -C $(CPULIMIT_SOURCE_DIR)
	@echo "Compiling cpulimit done"
	@touch $@

#
# Update
#
.PHONY: cpulimit-update

cpulimit-update:

#
# Status
#
.PHONY: cpulimit-status

cpulimit-status:

#
# Clean
#
.PHONY: cpulimit-clean

cpulimit-clean:
	@rm -f $(CPULIMIT_SOURCE_DIR)/*.o
	@rm -f $(CPULIMIT_SOURCE_DIR)cpulimit
	@rm -f $(TOP_LIBS_DIR)/.cpulimit_*

#
# Dist clean
#
.PHONY: cpulimit-distclean

cpulimit-distclean:
	#@rm -rf $(CPULIMIT_DIR)/
	@rm -f $(TOP_LIBS_DIR)/.cpulimit_*

#
# Install
#
.PHONY: cpulimit-install

cpulimit-install:
	cp -f $(CPULIMIT_SOURCE_DIR)/cpulimit $(TOP_INSTALL_ROOTFS_DIR)/bin
	chmod +x $(TOP_INSTALL_ROOTFS_DIR)/bin/cpulimit
