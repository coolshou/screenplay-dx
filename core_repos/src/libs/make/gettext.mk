##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# gettext makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_GETTEXT_VERSION 
CONF_GETTEXT_VERSION := 0.14.3
endif

GETTEXT             := gettext-$(CONF_GETTEXT_VERSION)#
GETTEXT_SERVER_URL  := $(TOP_LIBS_URL)/gettext/$(GETTEXT)
GETTEXT_DIR         := $(TOP_LIBS_DIR)#
GETTEXT_SOURCE      := $(GETTEXT_DIR)/$(GETTEXT)
GETTEXT_CONFIG      := 

#
# Download  the source 
#
.PHONY: gettext-downloaded

gettext-downloaded: $(GETTEXT_DIR)/.gettext_downloaded

$(GETTEXT_DIR)/.gettext_downloaded:
	@echo "Downloading $(GETTEXT) from $(GETTEXT_SERVER_URL) ..."
	@if [ ! -d "$(GETTEXT_SOURCE)" ]; then \
		cd $(GETTEXT_DIR); \
		$(TOP_DOWNLOAD) $(GETTEXT_SERVER_URL); \
	fi
	@echo "Downloading $(GETTEXT) from $(GETTEXT_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: gettext-unpacked

gettext-unpacked: $(GETTEXT_DIR)/.gettext_unpacked

$(GETTEXT_DIR)/.gettext_unpacked: $(GETTEXT_DIR)/.gettext_downloaded $(GETTEXT_SOURCE)/$(GETTEXT).tar.gz
	@echo "Unpacking $(GETTEXT) ..."
	if [ -d "$(GETTEXT_SOURCE)/$(GETTEXT)" ]; then \
		rm -fr $(GETTEXT_SOURCE)/$(GETTEXT); \
	fi
	cd $(GETTEXT_SOURCE); tar zxvf $(GETTEXT).tar.gz
	@echo "Unpacking $(GETTEXT) done"
	@touch $@


#
# Patch the source
#
.PHONY: gettext-patched

gettext-patched: $(GETTEXT_DIR)/.gettext_patched

$(GETTEXT_DIR)/.gettext_patched: $(GETTEXT_DIR)/.gettext_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: gettext-config

gettext-config: 

#
# Configuration
#
.PHONY: gettext-configured

gettext-configured:  gettext-config $(GETTEXT_DIR)/.gettext_configured

$(GETTEXT_DIR)/.gettext_configured: $(GETTEXT_DIR)/.gettext_patched $(GETTEXT_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(GETTEXT) ..."
	cd $(GETTEXT_SOURCE)/$(GETTEXT);./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=no 
	cd $(GETTEXT_SOURCE)/; patch -p0 < gettext_config.patch
	@echo "Configuring $(GETTEXT) done"
	@touch $@

#
# Compile
#
.PHONY: gettext-compile

gettext-compile: $(GETTEXT_DIR)/.gettext_compiled

$(GETTEXT_DIR)/.gettext_compiled: $(GETTEXT_DIR)/.gettext_configured
	@echo "Compiling $(GETTEXT) ..."
	#make -C $(GETTEXT_SOURCE)/$(GETTEXT) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(GETTEXT_SOURCE)/$(GETTEXT) 
	make -C $(GETTEXT_SOURCE)/$(GETTEXT)  install
	@echo "Compiling $(GETTEXT) done"
	@touch $@

#
# Update
#
.PHONY: gettext-update

gettext-update:
	@echo "Updating $(GETTEXT) ..."
	@if [ -d "$(GETTEXT_SOURCE)" ]; then\
		$(TOP_UPDATE) $(GETTEXT_SOURCE); \
	fi
	@echo "Updating $(GETTEXT) done"

#
# Status
#
.PHONY: gettext-status

gettext-status:
	@echo "Statusing $(GETTEXT) ..."
	@if [ -d "$(GETTEXT_SOURCE)" ]; then\
		$(TOP_STATUS) $(GETTEXT_SOURCE); \
	fi
	@echo "Statusing $(GETTEXT) done"

#
# Clean
#
.PHONY: gettext-clean

gettext-clean:
	@rm -f $(GETTEXT_DIR)/.gettext_configured
	@if [ -d "$(GETTEXT_SOURCE)" ]; then\
		make -C $(GETTEXT_SOURCE)/$(GETTEXT) clean; \
	fi

#
# Dist clean
#
.PHONY: gettext-distclean

gettext-distclean:
	@rm -f $(GETTEXT_DIR)/.gettext_*

#
# Install
#
.PHONY: gettext-install

gettext-install:
