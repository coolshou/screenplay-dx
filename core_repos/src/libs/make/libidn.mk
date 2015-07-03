##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# libidn makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBIDN_VERSION 
CONF_LIBIDN_VERSION := 1.19# 
endif

LIBIDN             := libidn-$(CONF_LIBIDN_VERSION)#
LIBIDN_SERVER_URL  := $(TOP_LIBS_URL)/libidn/$(LIBIDN)
LIBIDN_DIR         := $(TOP_LIBS_DIR)#
LIBIDN_SOURCE      := $(LIBIDN_DIR)/libidn-$(CONF_LIBIDN_VERSION)
LIBIDN_CONFIG      := 

#
# Download  the source 
#
.PHONY: libidn-downloaded

libidn-downloaded: $(LIBIDN_DIR)/.libidn_downloaded

$(LIBIDN_DIR)/.libidn_downloaded:
	@echo "Downloading $(LIBIDN) from $(LIBIDN_SERVER_URL) ..."
	@if [ ! -d "$(LIBIDN_SOURCE)" ]; then \
		cd $(LIBIDN_DIR); \
		$(TOP_DOWNLOAD) $(LIBIDN_SERVER_URL); \
	fi
	@echo "Downloading $(LIBIDN) from $(LIBIDN_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libidn-unpacked

libidn-unpacked: $(LIBIDN_DIR)/.libidn_unpacked

$(LIBIDN_DIR)/.libidn_unpacked: $(LIBIDN_DIR)/.libidn_downloaded $(LIBIDN_SOURCE)/$(LIBIDN).tar.gz
	@echo "Unpacking $(LIBIDN) ..."
	if [ -d "$(LIBIDN_SOURCE)/$(LIBIDN)" ]; then \
		rm -fr $(LIBIDN_SOURCE)/$(LIBIDN); \
	fi
	cd $(LIBIDN_SOURCE); tar xzvf $(LIBIDN).tar.gz
	@echo "Unpacking $(LIBIDN) done"
	@touch $@


#
# Patch the source
#
.PHONY: libidn-patched

libidn-patched: $(LIBIDN_DIR)/.libidn_patched

$(LIBIDN_DIR)/.libidn_patched: $(LIBIDN_DIR)/.libidn_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libidn-config

libidn-config: 

#
# Configuration
#
.PHONY: libidn-configured

libidn-configured:  libidn-config $(LIBIDN_DIR)/.libidn_configured

$(LIBIDN_DIR)/.libidn_configured: $(LIBIDN_DIR)/.libidn_patched $(LIBIDN_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBIDN) ..."
	cd $(LIBIDN_SOURCE)/$(LIBIDN);./configure --prefix=$(LIBS_INSTALL_PATH)   --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)
	@echo "Configuring $(LIBIDN) done"
	@touch $@

#
# Compile
#
.PHONY: libidn-compile

libidn-compile: $(LIBIDN_DIR)/.libidn_compiled

$(LIBIDN_DIR)/.libidn_compiled: $(LIBIDN_DIR)/.libidn_configured
	@echo "Compiling $(LIBIDN) ..."
	make -C $(LIBIDN_SOURCE)/$(LIBIDN) 
	make -C $(LIBIDN_SOURCE)/$(LIBIDN)  install
	@echo "Compiling $(LIBIDN) done"
	@touch $@

#
# Update
#
.PHONY: libidn-update

libidn-update:
	@echo "Updating $(LIBIDN) ..."
	@if [ -d "$(LIBIDN_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBIDN_SOURCE); \
	fi
	@echo "Updating $(LIBIDN) done"

#
# Status
#
.PHONY: libidn-status

libidn-status:
	@echo "Statusing $(LIBIDN) ..."
	@if [ -d "$(LIBIDN_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBIDN_SOURCE); \
	fi
	@echo "Statusing $(LIBIDN) done"

#
# Clean
#
.PHONY: libidn-clean

libidn-clean:
	@rm -f $(LIBIDN_DIR)/.libidn_configured
	@if [ -d "$(LIBIDN_SOURCE)" ]; then\
		make -C $(LIBIDN_SOURCE)/$(LIBIDN) clean; \
	fi

#
# Dist clean
#
.PHONY: libidn-distclean

libidn-distclean:
	@rm -f $(LIBIDN_DIR)/.libidn_*

#
# Install
#
.PHONY: libidn-install

libidn-install:
