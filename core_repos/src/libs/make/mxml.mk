##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# mxml makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_MXML_VERSION 
CONF_MXML_VERSION := 2.2
endif

MXML             := mxml-$(CONF_MXML_VERSION)#
MXML_SERVER_URL  := $(TOP_LIBS_URL)/mxml/$(MXML)
MXML_DIR         := $(TOP_LIBS_DIR)#
MXML_SOURCE      := $(MXML_DIR)/$(MXML)
MXML_CONFIG      := 

ifeq (x$(ENABLE_SHLIB),xyes)
	MXML_SHARED_FLAGS      := --enable-shared
endif


#
# Download  the source 
#
.PHONY: mxml-downloaded

mxml-downloaded: $(MXML_DIR)/.mxml_downloaded

$(MXML_DIR)/.mxml_downloaded:
	@echo "Downloading $(MXML) from $(MXML_SERVER_URL) ..."
	@if [ ! -d "$(MXML_SOURCE)" ]; then \
		cd $(MXML_DIR); \
		$(TOP_DOWNLOAD) $(MXML_SERVER_URL); \
	fi
	@echo "Downloading $(MXML) done"
	@touch $@

#
# Unpack the source
#
.PHONY: mxml-unpacked

mxml-unpacked: $(MXML_DIR)/.mxml_unpacked

$(MXML_DIR)/.mxml_unpacked: $(MXML_DIR)/.mxml_downloaded $(wildcard $(MXML_SOURCE)/*.tar.gz) $(wildcard $(MXML_SOURCE)/$(MXML)*.patch)
	@echo "Unpacking $(MXML) ..."
	if [ -d "$(MXML_SOURCE)/$(MXML)" ]; then \
		rm -fr $(MXML_SOURCE)/$(MXML); \
	fi
	cd $(MXML_SOURCE); tar zxvf $(MXML).tar.gz
	@echo "Unpacking $(MXML) done"
	@touch $@


#
# Patch the source
#
.PHONY: mxml-patched

mxml-patched: $(MXML_DIR)/.mxml_patched

$(MXML_DIR)/.mxml_patched: $(MXML_DIR)/.mxml_unpacked 
	@echo "Patching $(MXML) ..."
	cd $(MXML_SOURCE);./patch.sh
	@echo "Patching $(MXML) done"
	@touch $@

#
# config
#
.PHONY: mxml-config

mxml-config: 

#
# Configuration
#
.PHONY: mxml-configured

mxml-configured:  mxml-config $(MXML_DIR)/.mxml_configured

$(MXML_DIR)/.mxml_configured: $(MXML_DIR)/.mxml_patched $(MXML_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(MXML) ..."
	cd $(MXML_SOURCE)/$(MXML);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_ROOT) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) $(MXML_SHARED_FLAGS) 
	@echo "Configuring $(MXML) done"
	@touch $@

#
# Compile
#
.PHONY: mxml-compile

mxml-compile: $(MXML_DIR)/.mxml_compiled

$(MXML_DIR)/.mxml_compiled: $(MXML_DIR)/.mxml_configured 
	@echo "Compiling $(MXML) ..."
	make -C $(MXML_SOURCE)/$(MXML) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(MXML_SOURCE)/$(MXML) install
	@echo "Compiling $(MXML) done"
	@touch $@

#
# Update
#
.PHONY: mxml-update

mxml-update:
	@echo "Updating $(MXML) ..."
	@if [ -d "$(MXML_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MXML_SOURCE); \
	fi
	@echo "Updating $(MXML) done"

#
# Status
#
.PHONY: mxml-status

mxml-status:
	@echo "Statusing $(MXML) ..."
	@if [ -d "$(MXML_SOURCE)" ]; then\
		$(TOP_STATUS) $(MXML_SOURCE); \
	fi
	@echo "Statusing $(MXML) done"

#
# Clean
#
.PHONY: mxml-clean

mxml-clean:
	@rm -f $(MXML_DIR)/.mxml_configured
	@if [ -d "$(MXML_SOURCE)" ]; then\
		make -C $(MXML_SOURCE)/$(MXML) clean; \
	fi

#
# Dist clean
#
.PHONY: mxml-distclean

mxml-distclean:
	@rm -f $(MXML_DIR)/.mxml_*

#
# Install
#
.PHONY: mxml-install

mxml-install:
