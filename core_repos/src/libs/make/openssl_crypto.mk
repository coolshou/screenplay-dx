##############################################################################
# Copyright (C) alphanetworks 2008-- 
# All Rights Reserved -- Company Confidential
# Author:  ken_zhao@alphanetworks.com
# transmission makefile fragments 
##############################################################################

#
# These library is scratched from openssl
#

ifndef  OPENSSL_CRYPTO_VERSION 
OPENSSL_CRYPTO_VERSION := 0.9.8g
endif

OPENSSL_CRYPTO             := openssl_crypto-$(OPENSSL_CRYPTO_VERSION)#
OPENSSL_CRYPTO_SERVER_URL  := $(TOP_LIBS_URL)/openssl_crypto/$(OPENSSL_CRYPTO)
OPENSSL_CRYPTO_DIR         := $(TOP_LIBS_DIR)#
OPENSSL_CRYPTO_SOURCE      := $(OPENSSL_CRYPTO_DIR)/$(OPENSSL_CRYPTO)
OPENSSL_CRYPTO_CONFIG      := 

export OPENSSL_CRYPTO
#
# Download  the source 
#
.PHONY: openssl_crypto-downloaded

openssl_crypto-downloaded: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_downloaded

$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_downloaded:
	@echo "Downloading $(OPENSSL_CRYPTO) from $(OPENSSL_CRYPTO_SERVER_URL) ..."
	@if [ ! -d "$(OPENSSL_CRYPTO_SOURCE)" ]; then \
		cd $(OPENSSL_CRYPTO_DIR); \
		$(TOP_DOWNLOAD) $(OPENSSL_CRYPTO_SERVER_URL); \
	fi
	@echo "Downloading $(OPENSSL_CRYPTO) done"
	@touch $@

#
# Unpack the source
#
.PHONY: openssl_crypto-unpacked

openssl_crypto-unpacked: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_unpacked

$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_unpacked: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_downloaded $(wildcard $(OPENSSL_CRYPTO_SOURCE)/*.tgz)
	@echo "Unpacking $(OPENSSL_CRYPTO) ..."
	if [ -d "$(OPENSSL_CRYPTO_SOURCE)/$(OPENSSL_CRYPTO)" ]; then \
		rm -fr $(OPENSSL_CRYPTO_SOURCE)/$(OPENSSL_CRYPTO); \
	fi
	cd $(OPENSSL_CRYPTO_SOURCE);tar xvzf  $(OPENSSL_CRYPTO).tar.gz
	@echo "Unpacking $(OPENSSL_CRYPTO) done"
	@touch $@


#
# Patch the source
#
.PHONY: openssl_crypto-patched

openssl_crypto-patched: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_patched

$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_patched: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_unpacked
# Patching...
	@touch $@

#
# config
#
.PHONY: openssl_crypto-config

openssl_crypto-config: 

#
# Configuration
#
.PHONY: openssl_crypto-configured

openssl_crypto-configured:  openssl_crypto-config $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_configured

$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_configured: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_patched $(OPENSSL_CRYPTO_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(OPENSSL_CRYPTO) ..."

	@echo "Configuring $(OPENSSL_CRYPTO) done"
	@touch $@

#
# Compile
#
.PHONY: openssl_crypto-compile

openssl_crypto-compile: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_compiled

#$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_compiled: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_configured
$(OPENSSL_CRYPTO_DIR)/.openssl_crypto_compiled: $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_configured
	@echo "Compiling $(OPENSSL_CRYPTO) ..."
	make -C $(OPENSSL_CRYPTO_SOURCE) 
	make -C $(OPENSSL_CRYPTO_SOURCE) install
	@echo "Compiling $(OPENSSL_CRYPTO) done"
	@touch $@

#
# Update
#
.PHONY: openssl_crypto-update

openssl_crypto-update:
	@echo "Updating $(OPENSSL_CRYPTO) ..."
	@if [ -d "$(OPENSSL_CRYPTO_SOURCE)" ]; then\
		$(TOP_UPDATE) $(OPENSSL_CRYPTO_SOURCE); \
	fi
	@echo "Updating $(OPENSSL_CRYPTO) done"

#
# Status
#
.PHONY: openssl_crypto-status

openssl_crypto-status:
	@echo "Statusing $(OPENSSL_CRYPTO) ..."
	@if [ -d "$(OPENSSL_CRYPTO_SOURCE)" ]; then\
		$(TOP_STATUS) $(OPENSSL_CRYPTO_SOURCE); \
	fi
	@echo "Statusing $(OPENSSL_CRYPTO) done"

#
# Clean
#
.PHONY: openssl_crypto-clean

openssl_crypto-clean:
	@rm -f $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_configured
	@if [ -d "$(OPENSSL_CRYPTO_SOURCE)" ]; then\
		make -C $(OPENSSL_CRYPTO_SOURCE)/$(OPENSSL_CRYPTO) clean; \
	fi

#
# Dist clean
#
.PHONY: openssl_crypto-distclean

openssl_crypto-distclean:
	@rm -f $(OPENSSL_CRYPTO_DIR)/.openssl_crypto_*

#
# Install
#
.PHONY: openssl_crypto-install

openssl_crypto-install:
