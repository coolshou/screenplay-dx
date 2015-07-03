##############################################################################
# Copyright (C) alphanetworks 2008-- 
# All Rights Reserved -- Company Confidential
# Author:  ken_zhao@alphanetworks.com
# transmission makefile fragments 
##############################################################################

#
# These library is scratched from openssl
#

ifndef CONF_OPENSSL_VERSION 
CONF_OPENSSL_VERSION := 0.9.8k
endif

OPENSSL             := openssl-$(CONF_OPENSSL_VERSION)#
OPENSSL_SERVER_URL  := $(TOP_LIBS_URL)/openssl/$(OPENSSL)
OPENSSL_DIR         := $(TOP_LIBS_DIR)#
OPENSSL_SOURCE      := $(OPENSSL_DIR)/$(OPENSSL)
OPENSSL_CONFIG      := 

ifeq (x$(CONF_PLATFORM_X86), xy)
OPENSSL_CONFIGURE := ./config --prefix=$(LIBS_INSTALL_PATH) shared
else
OPENSSL_CONFIGURE := ./Configure linux-$(ARCH) --prefix=$(LIBS_INSTALL_PATH) shared
endif

export OPENSSL
#
# Download  the source 
#
.PHONY: openssl-downloaded

openssl-downloaded: $(OPENSSL_DIR)/.openssl_downloaded

$(OPENSSL_DIR)/.openssl_downloaded:
	@echo "Downloading $(OPENSSL) from $(OPENSSL_SERVER_URL) ..."
	@if [ ! -d "$(OPENSSL_SOURCE)" ]; then \
		cd $(OPENSSL_DIR); \
		$(TOP_DOWNLOAD) $(OPENSSL_SERVER_URL); \
	fi
	@echo "Downloading $(OPENSSL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: openssl-unpacked

openssl-unpacked: $(OPENSSL_DIR)/.openssl_unpacked

$(OPENSSL_DIR)/.openssl_unpacked: $(OPENSSL_DIR)/.openssl_downloaded $(wildcard $(OPENSSL_SOURCE)/*.tar.gz) $(wildcard $(OPENSSL_SOURCE)/*.patch)
	@echo "Unpacking $(OPENSSL) ..."
	if [ -d "$(OPENSSL_SOURCE)/$(OPENSSL)" ]; then \
		rm -fr $(OPENSSL_SOURCE)/$(OPENSSL); \
	fi
	cd $(OPENSSL_SOURCE);tar xvzf  $(OPENSSL).tar.gz
	@echo "Unpacking $(OPENSSL) done"
	@touch $@


#
# Patch the source
#
.PHONY: openssl-patched

openssl-patched: $(OPENSSL_DIR)/.openssl_patched

$(OPENSSL_DIR)/.openssl_patched: $(OPENSSL_DIR)/.openssl_unpacked
	@echo "Patching $(OPENSSL) ..."
	cd $(OPENSSL_SOURCE);patch -p0 <$(OPENSSL).patch
	@echo "Patching $(OPENSSL) done"
	@touch $@

#
# config
#
.PHONY: openssl-config

openssl-config: 

#
# Configuration
#
.PHONY: openssl-configured

openssl-configured:  openssl-config $(OPENSSL_DIR)/.openssl_configured

$(OPENSSL_DIR)/.openssl_configured: $(OPENSSL_DIR)/.openssl_patched $(OPENSSL_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(OPENSSL) ..." 
	(declare +x CROSS_COMPILE;cd $(OPENSSL_SOURCE)/$(OPENSSL); $(OPENSSL_CONFIGURE))
	@echo "Configuring $(OPENSSL) done"
	@touch $@

#
# Compile
#
.PHONY: openssl-compile

openssl-compile: $(OPENSSL_DIR)/.openssl_compiled

$(OPENSSL_DIR)/.openssl_compiled: $(OPENSSL_DIR)/.openssl_configured
	@echo "Compiling $(OPENSSL) ..."
	make -C $(OPENSSL_SOURCE)/$(OPENSSL)
	make -C $(OPENSSL_SOURCE)/$(OPENSSL) install
	# chmod to 777 for strip 
	chmod 777 $(LIBS_INSTALL_PATH)/lib/libssl.so.* 
	chmod 777 $(LIBS_INSTALL_PATH)/lib/libcrypto.so.* 
	@echo "Compiling $(OPENSSL) done"
	@touch $@

#
# Update
#
.PHONY: openssl-update

openssl-update:
	@echo "Updating $(OPENSSL) ..."
	@if [ -d "$(OPENSSL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(OPENSSL_SOURCE); \
	fi
	@echo "Updating $(OPENSSL) done"

#
# Status
#
.PHONY: openssl-status

openssl-status:
	@echo "Statusing $(OPENSSL) ..."
	@if [ -d "$(OPENSSL_SOURCE)" ]; then\
		$(TOP_STATUS) $(OPENSSL_SOURCE); \
	fi
	@echo "Statusing $(OPENSSL) done"

#
# Clean
#
.PHONY: openssl-clean

openssl-clean:
	@rm -f $(OPENSSL_DIR)/.openssl_configured
	@if [ -d "$(OPENSSL_SOURCE)" ]; then\
		make -C $(OPENSSL_SOURCE)/$(OPENSSL) clean; \
	fi

#
# Dist clean
#
.PHONY: openssl-distclean

openssl-distclean:
	@rm -f $(OPENSSL_DIR)/.openssl_*

#
# Install
#
.PHONY: openssl-install

openssl-install:
	cp -f $(LIBS_INSTALL_PATH)/bin/openssl $(TOP_INSTALL_ROOTFS_DIR)/bin
