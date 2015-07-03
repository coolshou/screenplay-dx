##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# zlib makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_ZLIB_VERSION 
CONF_ZLIB_VERSION := 1.2.2
endif

ZLIB             := zlib-$(CONF_ZLIB_VERSION)#
ZLIB_SERVER_URL  := $(TOP_LIBS_URL)/zlib/$(ZLIB)
ZLIB_DIR         := $(TOP_LIBS_DIR)#
ZLIB_SOURCE      := $(ZLIB_DIR)/$(ZLIB)
ZLIB_CONFIG      := 

ifeq (x$(ENABLE_SHLIB),xyes)
        ZLIB_SHARED_FLAGS      := --shared
endif

#
# Download  the source 
#
.PHONY: zlib-downloaded

zlib-downloaded: $(ZLIB_DIR)/.zlib_downloaded

$(ZLIB_DIR)/.zlib_downloaded:
	@echo "Downloading $(ZLIB) from $(ZLIB_SERVER_URL) ..."
	@if [ ! -d "$(ZLIB_SOURCE)" ]; then \
		cd $(ZLIB_DIR); \
		$(TOP_DOWNLOAD) $(ZLIB_SERVER_URL); \
	fi
	@echo "Downloading $(ZLIB) from $(ZLIB_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: zlib-unpacked

zlib-unpacked: $(ZLIB_DIR)/.zlib_unpacked

$(ZLIB_DIR)/.zlib_unpacked: $(ZLIB_DIR)/.zlib_downloaded $(ZLIB_SOURCE)/$(ZLIB).tar.gz
	@echo "Unpacking $(ZLIB) ..."
	if [ -d "$(ZLIB_SOURCE)/$(ZLIB)" ]; then \
		rm -fr $(ZLIB_SOURCE)/$(ZLIB); \
	fi
	cd $(ZLIB_SOURCE); tar zxvf $(ZLIB).tar.gz
	@echo "Unpacking $(ZLIB) done"
	@touch $@


#
# Patch the source
#
.PHONY: zlib-patched

zlib-patched: $(ZLIB_DIR)/.zlib_patched

$(ZLIB_DIR)/.zlib_patched: $(ZLIB_DIR)/.zlib_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: zlib-config

zlib-config: 

#
# Configuration
#
.PHONY: zlib-configured

zlib-configured:  zlib-config $(ZLIB_DIR)/.zlib_configured

$(ZLIB_DIR)/.zlib_configured: $(ZLIB_DIR)/.zlib_patched $(ZLIB_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(ZLIB) ..."
	cd $(ZLIB_SOURCE)/$(ZLIB);./configure --prefix=$(LIBS_INSTALL_PATH) $(ZLIB_SHARED_FLAGS)
	@echo "Configuring $(ZLIB) done"
	@touch $@

#
# Compile
#
.PHONY: zlib-compile

zlib-compile: $(ZLIB_DIR)/.zlib_compiled

$(ZLIB_DIR)/.zlib_compiled: $(ZLIB_DIR)/.zlib_configured
	@echo "Compiling $(ZLIB) ..."
	#make -C $(ZLIB_SOURCE)/$(ZLIB) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(ZLIB_SOURCE)/$(ZLIB) 
	make -C $(ZLIB_SOURCE)/$(ZLIB)  install
	@echo "Compiling $(ZLIB) done"
	@touch $@

#
# Update
#
.PHONY: zlib-update

zlib-update:
	@echo "Updating $(ZLIB) ..."
	@if [ -d "$(ZLIB_SOURCE)" ]; then\
		$(TOP_UPDATE) $(ZLIB_SOURCE); \
	fi
	@echo "Updating $(ZLIB) done"

#
# Status
#
.PHONY: zlib-status

zlib-status:
	@echo "Statusing $(ZLIB) ..."
	@if [ -d "$(ZLIB_SOURCE)" ]; then\
		$(TOP_STATUS) $(ZLIB_SOURCE); \
	fi
	@echo "Statusing $(ZLIB) done"

#
# Clean
#
.PHONY: zlib-clean

zlib-clean:
	@rm -f $(ZLIB_DIR)/.zlib_configured
	@if [ -d "$(ZLIB_SOURCE)" ]; then\
		make -C $(ZLIB_SOURCE)/$(ZLIB) clean; \
	fi

#
# Dist clean
#
.PHONY: zlib-distclean

zlib-distclean:
	@rm -f $(ZLIB_DIR)/.zlib_*

#
# Install
#
.PHONY: zlib-install

zlib-install:
