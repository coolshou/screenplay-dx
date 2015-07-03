##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libmcrypt makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBMCRYPT_VERSION 
CONF_LIBMCRYPT_VERSION := 2.5.8
endif

LIBMCRYPT             := libmcrypt-$(CONF_LIBMCRYPT_VERSION)#
LIBMCRYPT_SERVER_URL  := $(TOP_LIBS_URL)/libmcrypt/$(LIBMCRYPT)
LIBMCRYPT_DIR         := $(TOP_LIBS_DIR)#
LIBMCRYP_SOURCE      := $(LIBMCRYPT_DIR)/$(LIBMCRYPT)
LIBMCRYPT_CONFIG      := 


#
# Download  the source 
#
.PHONY: libmcrypt-downloaded

libmcrypt-downloaded: $(LIBMCRYPT_DIR)/.libmcrypt_downloaded

$(LIBMCRYPT_DIR)/.libmcrypt_downloaded:
	@echo "Downloading $(LIBMCRYPT) from $(LIBMCRYPT_SERVER_URL) ..."
	@if [ ! -d "$(LIBMCRYP_SOURCE)" ]; then \
		cd $(LIBMCRYPT_DIR); \
		$(TOP_DOWNLOAD) $(LIBMCRYPT_SERVER_URL); \
	fi
	@echo "Downloading $(LIBMCRYPT) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libmcrypt-unpacked

libmcrypt-unpacked: $(LIBMCRYPT_DIR)/.libmcrypt_unpacked

$(LIBMCRYPT_DIR)/.libmcrypt_unpacked: $(LIBMCRYPT_DIR)/.libmcrypt_downloaded $(LIBMCRYP_SOURCE)/$(LIBMCRYPT).tar.bz2
	@echo "Unpacking $(LIBMCRYPT) ..."
	if [ -d "$(LIBMCRYP_SOURCE)/$(LIBMCRYPT)" ]; then \
		rm -fr  $(LIBMCRYP_SOURCE)/$(LIBMCRYPT); \
	fi
	cd $(LIBMCRYP_SOURCE); tar jxvf $(LIBMCRYPT).tar.bz2
	@echo "Unpacking $(LIBMCRYPT) done"
	@touch $@


#
# Patch the source
#
.PHONY: libmcrypt-patched

libmcrypt-patched: $(LIBMCRYPT_DIR)/.libmcrypt_patched

$(LIBMCRYPT_DIR)/.libmcrypt_patched: $(LIBMCRYPT_DIR)/.libmcrypt_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libmcrypt-config

libmcrypt-config: 

#
# Configuration
#
.PHONY: libmcrypt-configured

libmcrypt-configured:  libmcrypt-config $(LIBMCRYPT_DIR)/.libmcrypt_configured

$(LIBMCRYPT_DIR)/.libmcrypt_configured: $(LIBMCRYPT_DIR)/.libmcrypt_patched $(LIBMCRYPT_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configring  $(LIBMCRYPT) ..."
	cd $(LIBMCRYP_SOURCE)/$(LIBMCRYPT);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib"
	@echo "Configring  $(LIBMCRYPT) done" 
	@cd $(LIBMCRYP_SOURCE)/$(LIBMCRYPT);sed -i -e "s/define malloc/undef malloc/" config.h;
	@cd $(LIBMCRYP_SOURCE)/$(LIBMCRYPT);sed -i -e "s/define realloc/undef realloc/" config.h;
	@touch $@

#
# Compile
#
.PHONY: libmcrypt-compile

libmcrypt-compile: $(LIBMCRYPT_DIR)/.libmcrypt_compiled

$(LIBMCRYPT_DIR)/.libmcrypt_compiled: $(LIBMCRYPT_DIR)/.libmcrypt_configured
	@echo "Compiling $(LIBMCRYPT) ..." 
	make -C $(LIBMCRYP_SOURCE)/$(LIBMCRYPT) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS="-I$(LIBS_INSTALL_PATH)/include"
	make -C $(LIBMCRYP_SOURCE)/$(LIBMCRYPT) install
	@echo "Compiling $(LIBMCRYPT) done"
	@touch $@
#
# Update
#
.PHONY: libmcrypt-update

libmcrypt-update:
	@echo "Updating $(LIBMCRYPT) ..."
	@if [ -d "$(LIBMCRYP_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBMCRYP_SOURCE); \
	fi
	@echo "Updating $(LIBMCRYPT) done"

#
# Status
#
.PHONY: libmcrypt-status

libmcrypt-status:
	@echo "Statusing $(LIBMCRYPT) ..."
	@if [ -d "$(LIBMCRYP_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBMCRYP_SOURCE); \
	fi
	@echo "Statusing $(LIBMCRYPT) done"

#
# Clean
#
.PHONY: libmcrypt-clean

libmcrypt-clean:
	@rm -f $(LIBMCRYPT_DIR)/.libmcrypt_configured
	@if [ -d "$(LIBMCRYP_SOURCE)" ]; then\
		make -C $(LIBMCRYP_SOURCE)/$(LIBMCRYPT) clean; \
	fi

#
# Dist clean
#
.PHONY: libmcrypt-distclean

libmcrypt-distclean:
	@rm -f $(LIBMCRYPT_DIR)/.libmcrypt_*

#
# Install
#
.PHONY: libmcrypt-install

libmcrypt-install:
