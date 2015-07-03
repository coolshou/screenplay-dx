##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libupnp makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBUPNP_VERSION 
LIBUPNP_VERSION := 1.2.1
endif

LIBUPNP             := libupnp-$(LIBUPNP_VERSION)#
LIBUPNP_SERVER_URL  := $(TOP_LIBS_URL)/libupnp/$(LIBUPNP)#
LIBUPNP_DIR         := $(TOP_LIBS_DIR)#
LIBUPNP_SOURCE      := $(LIBUPNP_DIR)/$(LIBUPNP)
LIBUPNP_CONFIG      := 


#
# Download  the source 
#
.PHONY: libupnp-downloaded

libupnp-downloaded: $(LIBUPNP_DIR)/.libupnp_downloaded

$(LIBUPNP_DIR)/.libupnp_downloaded:
	@echo "Downloading $(LIBUPNP) from $(LIBUPNP_SERVER_URL) ..."
	@if [ ! -d "$(LIBUPNP_SOURCE)" ]; then \
		cd $(LIBUPNP_DIR); \
		$(TOP_DOWNLOAD) $(LIBUPNP_SERVER_URL); \
	fi
	@echo "Downloading $(LIBUPNP) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libupnp-unpacked

libupnp-unpacked: $(LIBUPNP_DIR)/.libupnp_unpacked

$(LIBUPNP_DIR)/.libupnp_unpacked: $(LIBUPNP_DIR)/.libupnp_downloaded $(LIBUPNP_SOURCE)/$(LIBUPNP).tar.gz
	@echo "Unpacking $(LIBUPNP) ..."
	if [ -d "$(LIBUPNP_SOURCE)/$(LIBUPNP)" ]; then \
		rm -fr $(LIBUPNP_SOURCE)/$(LIBUPNP); \
	fi
	cd $(LIBUPNP_SOURCE); tar zxvf $(LIBUPNP).tar.gz
	@echo "Unpacking $(LIBUPNP) done"
	@touch $@


#
# Patch the source
#
.PHONY: libupnp-patched

libupnp-patched: $(LIBUPNP_DIR)/.libupnp_patched

$(LIBUPNP_DIR)/.libupnp_patched: $(LIBUPNP_DIR)/.libupnp_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libupnp-config

libupnp-config: 

#
# Configuration
#
.PHONY: libupnp-configured

libupnp-configured:  libupnp-config $(LIBUPNP_DIR)/.libupnp_configured

$(LIBUPNP_DIR)/.libupnp_configured: $(LIBUPNP_DIR)/.libupnp_patched $(LIBUPNP_CONFIG) $(TOP_CURRENT_SET)
	# Configuring..
	if [ -f $(LIBUPNP_SOURCE)/$(LIBUPNP)/configure ]; then \
		cd $(LIBUPNP_SOURCE)/$(LIBUPNP); CC=$(CROSS)gcc AR=$(CROSS)ar RANLIB=$(CROSS)ranlib NM=$(CROSS)nm ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB); \
	fi
	@touch $@

#
# Compile
#
.PHONY: libupnp-compile

libupnp-compile: $(LIBUPNP_DIR)/.libupnp_compiled

$(LIBUPNP_DIR)/.libupnp_compiled: $(LIBUPNP_DIR)/.libupnp_configured
	@echo "Compiling $(LIBUPNP) ..."
	if [ -f $(LIBUPNP_SOURCE)/$(LIBUPNP)/configure ]; then \
		cd $(LIBUPNP_SOURCE)/$(LIBUPNP); CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(CROSS)ld make ; \
		make -C $(LIBUPNP_SOURCE)/$(LIBUPNP) install; \
	else \
		make STATIC=1 CLIENT=0 PREFIX=$(LIBS_INSTALL_PATH) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(CROSS)ld -C $(LIBUPNP_SOURCE)/$(LIBUPNP)/upnp; \
	fi

	@echo "Compiling $(LIBUPNP) done"
	@touch $@

#
# Update
#
.PHONY: libupnp-update

libupnp-update:
	@echo "Updating $(LIBUPNP) ..."
	@if [ -d "$(LIBUPNP_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBUPNP_SOURCE); \
	fi
	@echo "Updating $(LIBUPNP) done"

#
# Status
#
.PHONY: libupnp-status

libupnp-status:
	@echo "Statusing $(LIBUPNP) ..."
	@if [ -d "$(LIBUPNP_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBUPNP_SOURCE); \
	fi
	@echo "Statusing $(LIBUPNP) done"

#
# Clean
#
.PHONY: libupnp-clean

libupnp-clean:
	@rm -f $(LIBUPNP_DIR)/.libupnp_configured
	@if [ -d "$(LIBUPNP_SOURCE)" ]; then\
		make -C $(LIBUPNP_SOURCE)/$(LIBUPNP)/upnp clean; \
	fi

#
# Dist clean
#
.PHONY: libupnp-distclean

libupnp-distclean:
	@rm -f $(LIBUPNP_DIR)/.libupnp_*

#
# Install
#
.PHONY: libupnp-install

libupnp-install:
