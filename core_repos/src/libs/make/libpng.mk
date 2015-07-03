##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libpng makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBPNG_VERSION 
CONF_LIBPNG_VERSION := 1.2.43
endif

LIBPNG             := libpng-$(CONF_LIBPNG_VERSION)#
LIBPNG_SERVER_URL  := $(TOP_LIBS_URL)/libpng/$(LIBPNG)
LIBPNG_DIR         := $(TOP_LIBS_DIR)#
LIBPNG_SOURCE      := $(LIBPNG_DIR)/$(LIBPNG)
LIBPNG_CONFIG      := 


#
# Download  the source 
#
.PHONY: libpng-downloaded

libpng-downloaded: $(LIBPNG_DIR)/.libpng_downloaded

$(LIBPNG_DIR)/.libpng_downloaded:
	@echo "Downloading $(LIBPNG) from $(LIBPNG_SERVER_URL) ..."
	@if [ ! -d "$(LIBPNG_SOURCE)" ]; then \
		cd $(LIBPNG_DIR); \
		$(TOP_DOWNLOAD) $(LIBPNG_SERVER_URL); \
	fi
	@echo "Downloading $(LIBPNG) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libpng-unpacked

libpng-unpacked: $(LIBPNG_DIR)/.libpng_unpacked

$(LIBPNG_DIR)/.libpng_unpacked: $(LIBPNG_DIR)/.libpng_downloaded $(LIBPNG_SOURCE)/$(LIBPNG).tar.gz
	@echo "Unpacking $(LIBPNG) ..."
	if [ -d "$(LIBPNG_SOURCE)/$(LIBPNG)" ]; then \
		rm -fr  $(LIBPNG_SOURCE)/$(LIBPNG); \
	fi
	cd $(LIBPNG_SOURCE); tar zxvf $(LIBPNG).tar.gz
	@echo "Unpacking $(LIBPNG) done"
	@touch $@


#
# Patch the source
#
.PHONY: libpng-patched

libpng-patched: $(LIBPNG_DIR)/.libpng_patched

$(LIBPNG_DIR)/.libpng_patched: $(LIBPNG_DIR)/.libpng_unpacked
	# Patching...
#	(cd  $(LIBPNG_SOURCE)/$(LIBPNG);patch -p0 < ../float_fix.patch)
	@touch $@

#
# config
#
.PHONY: libpng-config

libpng-config: 

#
# Configuration
#
.PHONY: libpng-configured

libpng-configured:  libpng-config $(LIBPNG_DIR)/.libpng_configured

$(LIBPNG_DIR)/.libpng_configured: $(LIBPNG_DIR)/.libpng_patched $(LIBPNG_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configring  $(LIBPNG) ..."
	cd $(LIBPNG_SOURCE)/$(LIBPNG);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib"
	@echo "Configring  $(LIBPNG) done" 
	@touch $@

#
# Compile
#
.PHONY: libpng-compile

libpng-compile: $(LIBPNG_DIR)/.libpng_compiled

$(LIBPNG_DIR)/.libpng_compiled: $(LIBPNG_DIR)/.libpng_configured
	@echo "Compiling $(LIBPNG) ..." 
	make -C $(LIBPNG_SOURCE)/$(LIBPNG) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS="-I$(LIBS_INSTALL_PATH)/include"
	make -C $(LIBPNG_SOURCE)/$(LIBPNG) install
	@echo "Compiling $(LIBPNG) done"
	@touch $@
#
# Update
#
.PHONY: libpng-update

libpng-update:
	@echo "Updating $(LIBPNG) ..."
	@if [ -d "$(LIBPNG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBPNG_SOURCE); \
	fi
	@echo "Updating $(LIBPNG) done"

#
# Status
#
.PHONY: libpng-status

libpng-status:
	@echo "Statusing $(LIBPNG) ..."
	@if [ -d "$(LIBPNG_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBPNG_SOURCE); \
	fi
	@echo "Statusing $(LIBPNG) done"

#
# Clean
#
.PHONY: libpng-clean

libpng-clean:
	@rm -f $(LIBPNG_DIR)/.libpng_configured
	@if [ -d "$(LIBPNG_SOURCE)" ]; then\
		make -C $(LIBPNG_SOURCE)/$(LIBPNG) clean; \
	fi

#
# Dist clean
#
.PHONY: libpng-distclean

libpng-distclean:
	@rm -f $(LIBPNG_DIR)/.libpng_*

#
# Install
#
.PHONY: libpng-install

libpng-install:
