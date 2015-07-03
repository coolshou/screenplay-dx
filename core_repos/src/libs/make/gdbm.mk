##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# gdbm makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_GDBM_VERSION 
CONF_GDBM_VERSION := 1.8.3
endif

GDBM             := gdbm-$(CONF_GDBM_VERSION)#
GDBM_SERVER_URL  := $(TOP_LIBS_URL)/gdbm/$(GDBM)#
GDBM_DIR         := $(TOP_LIBS_DIR)#
GDBM_SOURCE      := $(GDBM_DIR)/$(GDBM)#
GDBM_CONFIG      := 

#
# Download  the source 
#
.PHONY: gdbm-downloaded

gdbm-downloaded: $(GDBM_DIR)/.gdbm_downloaded

$(GDBM_DIR)/.gdbm_downloaded:
	@echo "Downloading $(GDBM) from $(GDBM_SERVER_URL) ..."
	@if [ ! -d "$(GDBM_SOURCE)" ]; then \
		cd $(GDBM_DIR); \
		$(TOP_DOWNLOAD) $(GDBM_SERVER_URL); \
	fi
	@echo "Downloading $(GDBM) done"
	@touch $@

#
# Unpack the source
#
.PHONY: gdbm-unpacked

gdbm-unpacked: $(GDBM_DIR)/.gdbm_unpacked

$(GDBM_DIR)/.gdbm_unpacked: $(GDBM_DIR)/.gdbm_downloaded $(wildcard $(GDBM_SOURCE)/*.tar.gz)
	@echo "Unpacking $(GDBM) ..."
	if [ -d "$(GDBM_SOURCE)/$(GDBM)" ]; then \
		rm -fr $(GDBM_SOURCE)/$(GDBM); \
	fi
	(cd $(GDBM_SOURCE); tar xvzf $(GDBM).tar.gz)
	@echo "Unpacking $(GDBM) done"
	@touch $@


#
# Patch the source
#
.PHONY: gdbm-patched

gdbm-patched: $(GDBM_DIR)/.gdbm_patched

$(GDBM_DIR)/.gdbm_patched: $(GDBM_DIR)/.gdbm_unpacked
	@echo "Patching $(GDBM) ..."
	cd $(GDBM_SOURCE);patch -p0 <$(GDBM).patch
	@echo "Patching $(GDBM) done"
	@touch $@

#
# config
#
.PHONY: gdbm-config

gdbm-config: 

#
# Configuration
#
.PHONY: gdbm-configured

gdbm-configured:  gdbm-config $(GDBM_DIR)/.gdbm_configured

$(GDBM_DIR)/.gdbm_configured: $(GDBM_DIR)/.gdbm_patched $(GDBM_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(GDBM) ..."
	cd $(GDBM_SOURCE)/$(GDBM); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET)
	@echo "Configuring $(GDBM) done"
	@touch $@

#
# Compile
#
.PHONY: gdbm-compile

gdbm-compile: $(GDBM_DIR)/.gdbm_compiled

$(GDBM_DIR)/.gdbm_compiled: $(GDBM_DIR)/.gdbm_configured
	@echo "Compiling $(GDBM) ..."
	make -C $(GDBM_SOURCE)/$(GDBM)
	make -C $(GDBM_SOURCE)/$(GDBM) install
	@echo "Compiling $(GDBM) done"
	@touch $@

#
# Update
#
.PHONY: gdbm-update

gdbm-update:
	@echo "Updating $(GDBM) ..."
	@if [ -d "$(GDBM_SOURCE)" ]; then\
		$(TOP_UPDATE) $(GDBM_SOURCE); \
	fi
	@echo "Updating $(GDBM) done"

#
# Status
#
.PHONY: gdbm-status

gdbm-status:
	@echo "Statusing $(GDBM) ..."
	@if [ -d "$(GDBM_SOURCE)" ]; then\
		$(TOP_STATUS) $(GDBM_SOURCE); \
	fi
	@echo "Statusing $(GDBM) done"

#
# Clean
#
.PHONY: gdbm-clean

gdbm-clean:
	@rm -f $(GDBM_DIR)/.gdbm_configured
	@if [ -d "$(GDBM_SOURCE)" ]; then\
		make -C $(GDBM_SOURCE)/$(GDBM) clean; \
	fi

#
# Dist clean
#
.PHONY: gdbm-distclean

gdbm-distclean:
	@rm -f $(GDBM_DIR)/.gdbm*

#
# Install
#
.PHONY: gdbm-install

gdbm-install:
