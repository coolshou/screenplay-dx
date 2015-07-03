##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# matrixssl makefile fragments 
##############################################################################

#
# Defines
#

MATRIXSSL             := matrixssl-$(CONF_MATRIXSSL_VERSION)#
MATRIXSSL_SERVER_URL  := $(TOP_LIBS_URL)/matrixssl/$(MATRIXSSL)
MATRIXSSL_DIR         := $(TOP_LIBS_DIR)#
MATRIXSSL_SOURCE      := $(MATRIXSSL_DIR)/$(MATRIXSSL)
MATRIXSSL_CONFIG      := 

ifeq (x$(ENABLE_SHLIB), xyes)
MATRIXSSL_TARGET	:= libmatrixssl.so
else
MATRIXSSL_TARGET	:= libmatrixssl.a
endif

#
# Download  the source 
#
.PHONY: matrixssl-downloaded

matrixssl-downloaded: $(MATRIXSSL_DIR)/.matrixssl_downloaded

$(MATRIXSSL_DIR)/.matrixssl_downloaded:
	@echo "Downloading $(MATRIXSSL) from $(MATRIXSSL_SERVER_URL) ..."
	@if [ ! -d "$(MATRIXSSL_SOURCE)" ]; then \
		cd $(MATRIXSSL_DIR); \
		$(TOP_DOWNLOAD) $(MATRIXSSL_SERVER_URL); \
	fi
	@echo "Downloading $(MATRIXSSL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: matrixssl-unpacked

matrixssl-unpacked: $(MATRIXSSL_DIR)/.matrixssl_unpacked

$(MATRIXSSL_DIR)/.matrixssl_unpacked: $(MATRIXSSL_DIR)/.matrixssl_downloaded $(wildcard $(MATRIXSSL_SOURCE)/*.tar.gz) $(wildcard $(MATRIXSSL_SOURCE)/*.patch)
	@echo "Unpacking $(MATRIXSSL) ..."
	if [ -d "$(MATRIXSSL_SOURCE)/$(MATRIXSSL)" ]; then \
		rm -fr $(MATRIXSSL_SOURCE)/$(MATRIXSSL); \
	fi
	cd $(MATRIXSSL_SOURCE); tar xzvf $(MATRIXSSL).tar.gz
	@echo "Unpacking $(MATRIXSSL) done"
	@touch $@


#
# Patch the source
#
.PHONY: matrixssl-patched

matrixssl-patched: $(MATRIXSSL_DIR)/.matrixssl_patched

$(MATRIXSSL_DIR)/.matrixssl_patched: $(MATRIXSSL_DIR)/.matrixssl_unpacked
	@echo "Patching $(MATRIXSSL) ..."
	cd $(MATRIXSSL_SOURCE);patch -p0 < matrixssl.patch
	@echo "Patching $(MATRIXSSL) done"
	@touch $@

#
# config
#
.PHONY: matrixssl-config

matrixssl-config: 

#
# Configuration
#
.PHONY: matrixssl-configured

matrixssl-configured:  matrixssl-config $(MATRIXSSL_DIR)/.matrixssl_configured

$(MATRIXSSL_DIR)/.matrixssl_configured: $(MATRIXSSL_DIR)/.matrixssl_patched $(MATRIXSSL_CONFIG) $(TOP_CURRENT_SET)
	@touch $@

#
# Compile
#
.PHONY: matrixssl-compile

matrixssl-compile: $(MATRIXSSL_DIR)/.matrixssl_compiled

$(MATRIXSSL_DIR)/.matrixssl_compiled: $(MATRIXSSL_DIR)/.matrixssl_configured
	@echo "Compiling $(MATRIXSSL) ..."
	cd $(MATRIXSSL_SOURCE)/matrixssl/src; make CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip $(MATRIXSSL_TARGET)
	cp -rf $(MATRIXSSL_SOURCE)/matrixssl/src/libmatrixssl.* $(LIBS_INSTALL_PATH)/lib
	cp -rf $(MATRIXSSL_SOURCE)/matrixssl/src/*.h $(LIBS_INSTALL_PATH)/include
	cp -rf $(MATRIXSSL_SOURCE)/matrixssl/*.h $(LIBS_INSTALL_PATH)/include
	@echo "Compiling $(MATRIXSSL) done"
	@touch $@

#
# Update
#
.PHONY: matrixssl-update

matrixssl-update:
	@echo "Updating $(MATRIXSSL) ..."
	@if [ -d "$(MATRIXSSL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MATRIXSSL_SOURCE); \
	fi
	@echo "Updating $(MATRIXSSL) done"

#
# Status
#
.PHONY: matrixssl-status

matrixssl-status:
	@echo "Statusing $(MATRIXSSL) ..."
	@if [ -d "$(MATRIXSSL_SOURCE)" ]; then\
		$(TOP_STATUS) $(MATRIXSSL_SOURCE); \
	fi
	@echo "Statusing $(MATRIXSSL) done"

#
# Clean
#
.PHONY: matrixssl-clean

matrixssl-clean:
	@rm -f $(MATRIXSSL_DIR)/.matrixssl_configured
	@if [ -d "$(MATRIXSSL_SOURCE)" ]; then\
		make -C $(MATRIXSSL_SOURCE)/matrixssl/src clean; \
	fi

#
# Dist clean
#
.PHONY: matrixssl-distclean

matrixssl-distclean:
	@rm -f $(MATRIXSSL_DIR)/.matrixssl*

#
# Install
#
.PHONY: matrixssl-install

matrixssl-install:
