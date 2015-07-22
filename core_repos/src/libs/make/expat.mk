##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# expat makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_EXPAT_VERSION 
CONF_EXPAT_VERSION := 2.1.0
endif

EXPAT             := expat-$(CONF_EXPAT_VERSION)#
EXPAT_SERVER_URL  := $(TOP_LIBS_URL)/expat/$(EXPAT)#
EXPAT_DIR         := $(TOP_LIBS_DIR)#
EXPAT_SOURCE      := $(EXPAT_DIR)/$(EXPAT)#
EXPAT_CONFIG      := 


# Download  the source 
#
.PHONY: expat-downloaded

expat-downloaded: $(EXPAT_DIR)/.expat_downloaded

$(EXPAT_DIR)/.expat_downloaded:
	@echo "Downloading $(EXPAT) from $(EXPAT_SERVER_URL) ..."
	@if [ ! -d "$(EXPAT_SOURCE)" ]; then \
		$(TOP_DOWNLOAD) $(EXPAT_SERVER_URL); \
	fi
	@echo "Downloading $(EXPAT) done"
	@touch $@

#
# Unpack the source
#
.PHONY: expat-unpacked

expat-unpacked: $(EXPAT_DIR)/.expat_unpacked

$(EXPAT_DIR)/.expat_unpacked: $(EXPAT_DIR)/.expat_downloaded $(EXPAT_SOURCE)/$(EXPAT).tar.gz 
	@echo "Unpacking $(EXPAT) ..."
	if [ -d "$(EXPAT_SOURCE)/$(EXPAT)" ]; then \
		rm -fr $(EXPAT_SOURCE)/$(EXPAT); \
	fi
	(cd $(EXPAT_SOURCE); tar xvf $(EXPAT).tar.gz)
	@echo "Unpacking $(EXPAT) done"
	@touch $@


#
# Patch the source
#
.PHONY: expat-patched

expat-patched: $(EXPAT_DIR)/.expat_patched

$(EXPAT_DIR)/.expat_patched: $(EXPAT_DIR)/.expat_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: expat-config

expat-config: 

#
# Configuration
#
.PHONY: expat-configured

expat-configured:  expat-config $(EXPAT_DIR)/.expat_configured

$(EXPAT_DIR)/.expat_configured: $(EXPAT_DIR)/.expat_patched $(EXPAT_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(EXPAT) ..."
	cd $(EXPAT_SOURCE)/$(EXPAT); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --target=$(BUILD_TARGET) --host=$(BUILD_TARGET) --enable-shared
	@echo "Configuring $(EXPAT) done"
	@touch $@

#
# Compile
#
.PHONY: expat-compile

expat-compile: $(EXPAT_DIR)/.expat_compiled

$(EXPAT_DIR)/.expat_compiled: $(EXPAT_DIR)/.expat_configured
	@echo "Compiling $(EXPAT) ..."
	make -C $(EXPAT_SOURCE)/$(EXPAT)
	make -C $(EXPAT_SOURCE)/$(EXPAT) install
	@echo "Compiling $(EXPAT) done"
	@touch $@

#
# Update
#
.PHONY: expat-update

expat-update:
	@echo "Updating $(EXPAT) ..."
	@if [ -d "$(EXPAT_SOURCE)" ]; then\
		$(TOP_UPDATE) $(EXPAT_SOURCE); \
	fi
	@echo "Updating $(EXPAT) done"

#
# Status
#
.PHONY: expat-status

expat-status:
	@echo "Statusing $(EXPAT) ..."
	@if [ -d "$(EXPAT_SOURCE)" ]; then\
		$(TOP_STATUS) $(EXPAT_SOURCE); \
	fi
	@echo "Statusing $(EXPAT) done"

#
# Clean
#
.PHONY: expat-clean

expat-clean:
	@rm -f $(EXPAT_DIR)/.expat_configured
	@if [ -d "$(EXPAT_SOURCE)" ]; then\
		make -C $(EXPAT_SOURCE)/$(EXPAT) clean; \
	fi

#
# Dist clean
#
.PHONY: expat-distclean

expat-distclean:
	@rm -f $(EXPAT_DIR)/.expat*

#
# Install
#
.PHONY: expat-install

expat-install:
