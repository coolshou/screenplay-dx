##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# c-ares makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_C-ARES_VERSION 
CONF_C-ARES_VERSION := 1.7.4# 
endif

C-ARES             := c-ares-$(CONF_C-ARES_VERSION)#
C-ARES_SERVER_URL  := $(TOP_LIBS_URL)/c-ares/$(C-ARES)
C-ARES_DIR         := $(TOP_LIBS_DIR)#
C-ARES_SOURCE      := $(C-ARES_DIR)/c-ares-$(CONF_C-ARES_VERSION)
C-ARES_CONFIG      := 

#
# Download  the source 
#
.PHONY: c-ares-downloaded

c-ares-downloaded: $(C-ARES_DIR)/.c-ares_downloaded

$(C-ARES_DIR)/.c-ares_downloaded:
	@echo "Downloading $(C-ARES) from $(C-ARES_SERVER_URL) ..."
	@if [ ! -d "$(C-ARES_SOURCE)" ]; then \
		cd $(C-ARES_DIR); \
		$(TOP_DOWNLOAD) $(C-ARES_SERVER_URL); \
	fi
	@echo "Downloading $(C-ARES) from $(C-ARES_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: c-ares-unpacked

c-ares-unpacked: $(C-ARES_DIR)/.c-ares_unpacked

$(C-ARES_DIR)/.c-ares_unpacked: $(C-ARES_DIR)/.c-ares_downloaded $(C-ARES_SOURCE)/$(C-ARES).tar.gz
	@echo "Unpacking $(C-ARES) ..."
	if [ -d "$(C-ARES_SOURCE)/$(C-ARES)" ]; then \
		rm -fr $(C-ARES_SOURCE)/$(C-ARES); \
	fi
	cd $(C-ARES_SOURCE); tar xzvf $(C-ARES).tar.gz
	@echo "Unpacking $(C-ARES) done"
	@touch $@


#
# Patch the source
#
.PHONY: c-ares-patched

c-ares-patched: $(C-ARES_DIR)/.c-ares_patched

$(C-ARES_DIR)/.c-ares_patched: $(C-ARES_DIR)/.c-ares_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: c-ares-config

c-ares-config: 

#
# Configuration
#
.PHONY: c-ares-configured

c-ares-configured:  c-ares-config $(C-ARES_DIR)/.c-ares_configured

$(C-ARES_DIR)/.c-ares_configured: $(C-ARES_DIR)/.c-ares_patched $(C-ARES_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(C-ARES) ..."
	cd $(C-ARES_SOURCE)/$(C-ARES);./configure --prefix=$(LIBS_INSTALL_PATH)   --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)
	@echo "Configuring $(C-ARES) done"
	@touch $@

#
# Compile
#
.PHONY: c-ares-compile

c-ares-compile: $(C-ARES_DIR)/.c-ares_compiled

$(C-ARES_DIR)/.c-ares_compiled: $(C-ARES_DIR)/.c-ares_configured
	@echo "Compiling $(C-ARES) ..."
	make -C $(C-ARES_SOURCE)/$(C-ARES) 
	make -C $(C-ARES_SOURCE)/$(C-ARES)  install
	@echo "Compiling $(C-ARES) done"
	@touch $@

#
# Update
#
.PHONY: c-ares-update

c-ares-update:
	@echo "Updating $(C-ARES) ..."
	@if [ -d "$(C-ARES_SOURCE)" ]; then\
		$(TOP_UPDATE) $(C-ARES_SOURCE); \
	fi
	@echo "Updating $(C-ARES) done"

#
# Status
#
.PHONY: c-ares-status

c-ares-status:
	@echo "Statusing $(C-ARES) ..."
	@if [ -d "$(C-ARES_SOURCE)" ]; then\
		$(TOP_STATUS) $(C-ARES_SOURCE); \
	fi
	@echo "Statusing $(C-ARES) done"

#
# Clean
#
.PHONY: c-ares-clean

c-ares-clean:
	@rm -f $(C-ARES_DIR)/.c-ares_configured
	@if [ -d "$(C-ARES_SOURCE)" ]; then\
		make -C $(C-ARES_SOURCE)/$(C-ARES) clean; \
	fi

#
# Dist clean
#
.PHONY: c-ares-distclean

c-ares-distclean:
	@rm -f $(C-ARES_DIR)/.c-ares_*
#@rm -fr $(C-ARES_SOURCE)

#
# Install
#
.PHONY: c-ares-install

c-ares-install:
