##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# tinyxml makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_TINYXML_VERSION 
CONF_TINYXML_VERSION := 2.5.3
endif

TINYXML             := tinyxml_$(CONF_TINYXML_VERSION)#
TINYXML_SERVER_URL  := $(TOP_LIBS_URL)/tinyxml/$(TINYXML)
TINYXML_DIR         := $(TOP_LIBS_DIR)#
TINYXML_SOURCE      := $(TINYXML_DIR)/$(TINYXML)
TINYXML_CONFIG      := 

ifeq (x$(ENABLE_SHLIB),xyes)
	TINYXML_SHARED_FLAGS      := --enable-shared
endif


#
# Download  the source 
#
.PHONY: tinyxml-downloaded

tinyxml-downloaded: $(TINYXML_DIR)/.tinyxml_downloaded

$(TINYXML_DIR)/.tinyxml_downloaded:
	@echo "Downloading $(TINYXML) from $(TINYXML_SERVER_URL) ..."
	@if [ ! -d "$(TINYXML_SOURCE)" ]; then \
		cd $(TINYXML_DIR); \
		$(TOP_DOWNLOAD) $(TINYXML_SERVER_URL); \
	fi
	@echo "Downloading $(TINYXML) done"
	@touch $@

#
# Unpack the source
#
.PHONY: tinyxml-unpacked

tinyxml-unpacked: $(TINYXML_DIR)/.tinyxml_unpacked

$(TINYXML_DIR)/.tinyxml_unpacked: $(TINYXML_DIR)/.tinyxml_downloaded $(wildcard $(TINYXML_SOURCE)/*.tar.gz) $(wildcard $(TINYXML_SOURCE)/$(TINYXML)*.patch)
	@echo "Unpacking $(TINYXML) ..."
	if [ -d "$(TINYXML_SOURCE)/$(TINYXML)" ]; then \
		rm -fr $(TINYXML_SOURCE)/$(TINYXML); \
	fi
	cd $(TINYXML_SOURCE); tar zxvf $(TINYXML).tar.gz; mv tinyxml $(TINYXML)
	@echo "Unpacking $(TINYXML) done"
	@touch $@


#
# Patch the source
#
.PHONY: tinyxml-patched

tinyxml-patched: $(TINYXML_DIR)/.tinyxml_patched

$(TINYXML_DIR)/.tinyxml_patched: $(TINYXML_DIR)/.tinyxml_unpacked 
	@echo "Patching $(TINYXML) ..."
	cd $(TINYXML_SOURCE);patch -p0 < tinyxml-Makefile.patch
	@echo "Patching $(TINYXML) done"
	@touch $@

#
# config
#
.PHONY: tinyxml-config

tinyxml-config: 

#
# Configuration
#
.PHONY: tinyxml-configured

tinyxml-configured:  tinyxml-config $(TINYXML_DIR)/.tinyxml_configured

$(TINYXML_DIR)/.tinyxml_configured: $(TINYXML_DIR)/.tinyxml_patched 

#
# Compile
#
.PHONY: tinyxml-compile

tinyxml-compile: $(TINYXML_DIR)/.tinyxml_compiled

$(TINYXML_DIR)/.tinyxml_compiled: $(TINYXML_DIR)/.tinyxml_configured 
	@echo "Compiling $(TINYXML) ..."
	make -C $(TINYXML_SOURCE)/$(TINYXML) 
	(cd $(TINYXML_SOURCE)/$(TINYXML);cp tinyxml.h  $(LIBS_INSTALL_PATH)/include/;cp tinystr.h $(LIBS_INSTALL_PATH)/include/;find . -name *.so* -exec cp {} $(LIBS_INSTALL_PATH)/lib/ \;;)
	@echo "Compiling $(TINYXML) done"
	@touch $@

#
# Update
#
.PHONY: tinyxml-update

tinyxml-update:
	@echo "Updating $(TINYXML) done"

#
# Status
#
.PHONY: tinyxml-status

tinyxml-status:
	@echo "Statusing $(TINYXML) done"

#
# Clean
#
.PHONY: tinyxml-clean

tinyxml-clean:
	@if [ -d "$(TINYXML_SOURCE)" ]; then\
		make -C $(TINYXML_SOURCE)/$(TINYXML) clean; \
	fi

#
# Dist clean
#
.PHONY: tinyxml-distclean

tinyxml-distclean:
	@rm -f $(TINYXML_DIR)/.tinyxml_*

#
# Install
#
.PHONY: tinyxml-install

tinyxml-install:
