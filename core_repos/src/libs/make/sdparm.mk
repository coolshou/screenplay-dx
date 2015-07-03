##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# SDPARM makefile fragments 
##############################################################################

#
# Defines
#
ifndef  SDPARM_VERSION 
SDPARM_VERSION := 1.03
endif

SDPARM             := sdparm#
SDPARM_SERVER_URL  := $(TOP_LIBS_URL)/$(SDPARM)/
SDPARM_DIR         := $(TOP_LIBS_DIR)#
SDPARM_SOURCE      := $(TOP_LIBS_DIR)/$(SDPARM)/$(SDPARM)-$(SDPARM_VERSION)
SDPARM_CONFIG      := 


#
# Download  the source 
#
.PHONY: sdparm-downloaded

sdparm-downloaded: $(SDPARM_DIR)/.sdparm_downloaded

$(SDPARM_DIR)/.sdparm_downloaded:
	touch $@

#
# Unpack the source
#
.PHONY: sdparm-unpacked

sdparm-unpacked: $(SDPARM_DIR)/.sdparm_unpacked

$(SDPARM_DIR)/.sdparm_unpacked: $(SDPARM_DIR)/.sdparm_downloaded
	@if [ ! -d "$(SDPARM_SOURCE)" ]; then \
		cd $(TOP_LIBS_DIR)/$(SDPARM); \
		tar -zxvf $(SDPARM_SOURCE).tgz;	\
	fi
	@touch $@


#
# Patch the source
#
.PHONY: sdparm-patched

sdparm-patched: $(SDPARM_DIR)/.sdparm_patched

$(SDPARM_DIR)/.sdparm_patched: $(SDPARM_DIR)/.sdparm_unpacked
	touch $@


#
# config
#
.PHONY: sdparm-config

sdparm-config: 

#
# Configuration
#
.PHONY: sdparm-configured

sdparm-configured:$(SDPARM_DIR)/.sdparm_configured

$(SDPARM_DIR)/.sdparm_configured: $(SDPARM_DIR)/.sdparm_patched
	@echo "Configured $(SDPARM) ..."
	cd $(SDPARM_SOURCE);\
	./configure --prefix=$(LIBS_INSTALL_PATH) --target=$(BUILD_TARGET)  --host=$(BUILD_TARGET) --build=$(BUILD_HOST) CC=$(CC) CFLAGS=" $(CFLAGS) -g -Os -pipe"  LDFLAGS="-g "
	@echo "Configured $(SDPARM) done"
	@touch $@

#
# Compile
#
.PHONY: sdparm-compile

sdparm-compile: sdparm-configured $(SDPARM_DIR)/.sdparm_compiled

$(SDPARM_DIR)/.sdparm_compiled:
	@echo "Compiling $(SDPARM) ..."
	make -C $(SDPARM_SOURCE)
	make -C $(SDPARM_SOURCE) install
	@echo "Compiling $(SDPARM) done"
	@touch $@

#
# Update
#
.PHONY: sdparm-update

sdparm-update:
	@echo "Updating $(SDPARM) done"

#
# Status
#
.PHONY: sdparm-status

ftpd-status:
	@echo "Statusing $(SDPARM) done"

#
# Clean
#
.PHONY: sdparm-clean

sdparm-clean:
	@if [ -d "$(SDPARM_SOURCE)" ]; then\
		make -C $(SDPARM_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: sdparm-distclean

sdparm-distclean:
	rm -f $(TOP_LIBS_DIR)/.sdparm*

#
# Install
#
.PHONY: sdparm-install

sdparm-install:
	cp -f $(SDPARM_SOURCE)/src/sdparm $(TOP_INSTALL_ROOTFS_DIR)/bin 
	$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/bin/sdparm


