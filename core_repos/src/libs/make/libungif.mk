##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libungif makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBUNGIF_VERSION 
CONF_LIBUNGIF_VERSION := 4.1.3
endif

LIBUNGIF             := libungif-$(CONF_LIBUNGIF_VERSION)#
LIBUNGIF_SERVER_URL  := $(TOP_LIBS_URL)/libungif/$(LIBUNGIF)
LIBUNGIF_DIR         := $(TOP_LIBS_DIR)#
LIBUNGIF_SOURCE      := $(LIBUNGIF_DIR)/$(LIBUNGIF)
LIBUNGIF_CONFIG      := 


#
# Download  the source 
#
.PHONY: libungif-downloaded

libungif-downloaded: $(LIBUNGIF_DIR)/.libungif_downloaded

$(LIBUNGIF_DIR)/.libungif_downloaded:
	@echo "Downloading $(LIBUNGIF) from $(LIBUNGIF_SERVER_URL) ..."
	@if [ ! -d "$(LIBUNGIF_SOURCE)" ]; then \
		cd $(LIBUNGIF_DIR); \
		$(TOP_DOWNLOAD) $(LIBUNGIF_SERVER_URL); \
	fi
	@echo "Downloading $(LIBUNGIF) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libungif-unpacked

libungif-unpacked: $(LIBUNGIF_DIR)/.libungif_unpacked

$(LIBUNGIF_DIR)/.libungif_unpacked: $(LIBUNGIF_DIR)/.libungif_downloaded $(wildcard $(LIBUNGIF_SOURCE)/*.tar.gz)
	@echo "Unpacking $(LIBUNGIF) ..."
	if [ -d "$(LIBUNGIF_SOURCE)/$(LIBUNGIF)" ]; then \
		rm -fr $(LIBUNGIF_SOURCE)/$(LIBUNGIF); \
	fi
	cd $(LIBUNGIF_SOURCE); tar zxvf $(LIBUNGIF).tar.gz
	@echo "Unpacking $(LIBUNGIF) done"
	@touch $@


#
# Patch the source
#
.PHONY: libungif-patched

libungif-patched: $(LIBUNGIF_DIR)/.libungif_patched

$(LIBUNGIF_DIR)/.libungif_patched: $(LIBUNGIF_DIR)/.libungif_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libungif-config

libungif-config: 

#
# Configuration
#
.PHONY: libungif-configured

libungif-configured:  libungif-config $(LIBUNGIF_DIR)/.libungif_configured

$(LIBUNGIF_DIR)/.libungif_configured: $(LIBUNGIF_DIR)/.libungif_patched $(LIBUNGIF_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBUNGIF) ..."
	cd $(LIBUNGIF_SOURCE)/$(LIBUNGIF); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) --without-x
	@echo "Configuring $(LIBUNGIF) done"
	@touch $@

#
# Compile
#
.PHONY: libungif-compile

libungif-compile: $(LIBUNGIF_DIR)/.libungif_compiled

$(LIBUNGIF_DIR)/.libungif_compiled: $(LIBUNGIF_DIR)/.libungif_configured
	@echo "Compiling $(LIBUNGI) ..."
	make -C $(LIBUNGIF_SOURCE)/$(LIBUNGIF) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBUNGIF_SOURCE)/$(LIBUNGIF) install
	@echo "Compiling $(LIBUNGI) done"
	@touch $@

#
# Update
#
.PHONY: libungif-update

libungif-update:
	@echo "Updating $(LIBUNGIF) ..."
	@if [ -d "$(LIBUNGIF_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBUNGIF_SOURCE); \
	fi
	@echo "Updating $(LIBUNGIF) done"

#
# Status
#
.PHONY: libungif-status

libungif-status:
	@echo "Statusing $(LIBUNGIF) ..."
	@if [ -d "$(LIBUNGIF_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBUNGIF_SOURCE); \
	fi
	@echo "Statusing $(LIBUNGIF) done"

#
# Clean
#
.PHONY: libungif-clean

libungif-clean:
	@rm -f $(LIBUNGIF_DIR)/.libungif_configured
	@if [ -d "$(LIBUNGIF_SOURCE)" ]; then\
		make -C $(LIBUNGIF_SOURCE)/$(LIBUNGIF) clean; \
	fi

#
# Dist clean
#
.PHONY: libungif-distclean

libungif-distclean:
	@rm -f $(LIBUNGIF_DIR)/.libungif_*

#
# Install
#
.PHONY: libungif-install

libungif-install:
