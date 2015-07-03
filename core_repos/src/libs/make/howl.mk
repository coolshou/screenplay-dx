##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# howl makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_HOWL_VERSION 
HOWL_VERSION := 1.0.0
else
HOWL_VERSION := $(CONF_HOWL_VERSION)
endif

HOWL             := howl-$(HOWL_VERSION)#
HOWL_SERVER_URL  := $(TOP_LIBS_URL)/howl/$(HOWL)#b
HOWL_DIR         := $(TOP_LIBS_DIR)#
HOWL_SOURCE      := $(HOWL_DIR)/$(HOWL)
HOWL_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        HOWL_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: howl-downloaded

howl-downloaded: $(HOWL_DIR)/.howl_downloaded

$(HOWL_DIR)/.howl_downloaded:
	@echo "Downloading $(HOWL) from $(HOWL_SERVER_URL) ..."
	@if [ ! -d "$(HOWL_SOURCE)" ]; then \
		cd $(HOWL_DIR); \
		$(TOP_DOWNLOAD) $(HOWL_SERVER_URL); \
	fi
	@echo "Downloading $(HOWL) from $(HOWL_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: howl-unpacked

howl-unpacked: $(HOWL_DIR)/.howl_unpacked

$(HOWL_DIR)/.howl_unpacked: $(HOWL_DIR)/.howl_downloaded $(HOWL_SOURCE)/$(HOWL).tar.gz
	@echo "Unpacking $(HOWL) ..."
	if [ -d "$(HOWL_SOURCE)/$(HOWL)" ]; then \
		rm -fr $(HOWL_SOURCE)/$(HOWL); \
	fi
	cd $(HOWL_SOURCE); tar zxvf  $(HOWL).tar.gz
	@echo "Unpacking $(HOWL) done"
	@touch $@


#
# Patch the source
#
.PHONY: howl-patched

howl-patched: $(HOWL_DIR)/.howl_patched

$(HOWL_DIR)/.howl_patched: $(HOWL_DIR)/.howl_unpacked
	# Patching...
# Patching... 	
	cd $(HOWL_SOURCE)/$(HOWL); patch -p1 < ../$(HOWL).patch
	@touch $@

#
# config
#
.PHONY: howl-config

howl-config: 

#
# Configuration
#
.PHONY: howl-configured

howl-configured:  howl-config $(HOWL_DIR)/.howl_configured

$(HOWL_DIR)/.howl_configured: $(HOWL_DIR)/.howl_patched $(HOWL_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(HOWL) ..."
	cd $(HOWL_SOURCE)/$(HOWL);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) $(HOWL_SHARED_FLAGS)
	@echo "Configuring $(HOWL) done"
	@touch $@

#
# Compile
#
.PHONY: howl-compile

howl-compile: $(HOWL_DIR)/.howl_compiled

$(HOWL_DIR)/.howl_compiled: $(HOWL_DIR)/.howl_configured
	@echo "Compiling $(HOWL) ..."
	make -C $(HOWL_SOURCE)/$(HOWL)
	make -C $(HOWL_SOURCE)/$(HOWL) install
	@echo "Compiling $(HOWL) done"
	@touch $@

#
# Update
#
.PHONY: howl-update

howl-update:
	@echo "Updating $(HOWL) ..."
	@if [ -d "$(HOWL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(HOWL_SOURCE); \
	fi
	@echo "Updating $(HOWL) done"

#
# Status
#
.PHONY: howl-status

howl-status:
	@echo "Statusing $(HOWL) ..."
	@if [ -d "$(HOWL_SOURCE)" ]; then\
		$(TOP_STATUS) $(HOWL_SOURCE); \
	fi
	@echo "Statusing $(HOWL) done"

#
# Clean
#
.PHONY: howl-clean

howl-clean:
	@rm -f $(HOWL_DIR)/.howl_configured
	@if [ -d "$(HOWL_SOURCE)" ]; then\
		make -C $(HOWL_SOURCE)/$(HOWL)/build_unix clean; \
	fi

#
# Dist clean
#
.PHONY: howl-distclean

howl-distclean:
	@rm -f $(HOWL_DIR)/.howl_*

#
# Install
#
.PHONY: howl-install

howl-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/lib
ifeq ($ENABLE_SHLIB,yes)
	cp -f $(LIBS_INSTALL_PATH)/lib/libmDNSResponder.so* $(TOP_INSTALL_ROOTFS_DIR)/lib
	cp -f $(LIBS_INSTALL_PATH)/lib/libhowl.so* $(TOP_INSTALL_ROOTFS_DIR)/lib
endif
	cp -f $(LIBS_INSTALL_PATH)/bin/mDNSResponder $(TOP_INSTALL_ROOTFS_DIR)/bin
	cp -f $(LIBS_INSTALL_PATH)/bin/autoipd $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) $(TOP_INSTALL_ROOTFS_DIR)/bin/mDNSResponder
	$(STRIP) $(TOP_INSTALL_ROOTFS_DIR)/bin/autoipd
