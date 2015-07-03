##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libogg makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBOGG_VERSION 
LIBOGG_VERSION := 1.0
endif

LIBOGG             := libogg-$(LIBOGG_VERSION)#
LIBOGG_SERVER_URL  := $(TOP_LIBS_URL)/libogg/$(LIBOGG)#
LIBOGG_DIR         := $(TOP_LIBS_DIR)#
LIBOGG_SOURCE      := $(LIBOGG_DIR)/$(LIBOGG)#
LIBOGG_CONFIG      := 


#
# Download  the source 
#
.PHONY: libogg-downloaded

libogg-downloaded: $(LIBOGG_DIR)/.libogg_downloaded

$(LIBOGG_DIR)/.libogg_downloaded:
	@echo "Downloading $(LIBOGG) from $(LIBOGG_SERVER_URL) ..."
	@if [ ! -d "$(LIBOGG_SOURCE)" ]; then \
		cd $(LIBOGG_DIR); \
		$(TOP_DOWNLOAD) $(LIBOGG_SERVER_URL); \
	fi
	@echo "Downloading $(LIBOGG) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libogg-unpacked

libogg-unpacked: $(LIBOGG_DIR)/.libogg_unpacked

$(LIBOGG_DIR)/.libogg_unpacked: $(LIBOGG_DIR)/.libogg_downloaded
	@echo "Unpacking $(LIBOGG) ..."
	if [ -d "$(LIBOGG_SOURCE)/$(LIBOGG)" ]; then \
		rm -fr $(LIBOGG_SOURCE)/$(LIBOGG);\
	fi
	cd $(LIBOGG_SOURCE); tar zxvf $(LIBOGG).tgz
	@echo "Unpacking $(LIBOGG) done"
	@touch $@


#
# Patch the source
#
.PHONY: libogg-patched

libogg-patched: $(LIBOGG_DIR)/.libogg_patched

$(LIBOGG_DIR)/.libogg_patched: $(LIBOGG_DIR)/.libogg_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libogg-config

libogg-config: 

#
# Configuration
#
.PHONY: libogg-configured

libogg-configured:  libogg-config $(LIBOGG_DIR)/.libogg_configured

$(LIBOGG_DIR)/.libogg_configured: $(LIBOGG_DIR)/.libogg_patched $(LIBOGG_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBOGG) ..."
	cd $(LIBOGG_SOURCE)/$(LIBOGG); ./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB)
	@echo "Configuring $(LIBOGG) done"
	@touch $@

#
# Compile
#
.PHONY: libogg-compile

libogg-compile: $(LIBOGG_DIR)/.libogg_compiled

$(LIBOGG_DIR)/.libogg_compiled: $(LIBOGG_DIR)/.libogg_configured
	@echo "Compiling $(LIBOGG) ..."
	make -C $(LIBOGG_SOURCE)/$(LIBOGG) 
	make -C $(LIBOGG_SOURCE)/$(LIBOGG) install
	@echo "Compiling $(LIBOGG) done"
	@touch $@

#
# Update
#
.PHONY: libogg-update

libogg-update:
	@echo "Updating $(LIBOGG) ..."
	@if [ -d "$(LIBOGG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBOGG_SOURCE); \
	fi
	@echo "Updating $(LIBOGG) done"

#
# Status
#
.PHONY: libogg-status

libogg-status:
	@echo "Statusing $(LIBOGG) ..."
	@if [ -d "$(LIBOGG_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBOGG_SOURCE); \
	fi
	@echo "Statusing $(LIBOGG) done"

#
# Clean
#
.PHONY: libogg-clean

libogg-clean:
	@rm -f $(LIBOGG_DIR)/.libogg_configured
	@if [ -d "$(LIBOGG_SOURCE)" ]; then\
		make -C $(LIBOGG_SOURCE)/$(LIBOGG) clean; \
	fi

#
# Dist clean
#
.PHONY: libogg-distclean

libogg-distclean:
	@rm -f $(LIBOGG_DIR)/.libogg_*

#
# Install
#
.PHONY: libogg-install

libogg-install:
