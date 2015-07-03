##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# libexif makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBEXIF_VERSION 
CONF_LIBEXIF_VERSION := 0.6.17# 
endif

LIBEXIF             := libexif-$(CONF_LIBEXIF_VERSION)#
LIBEXIF_SERVER_URL  := $(TOP_LIBS_URL)/libexif/$(LIBEXIF)
LIBEXIF_DIR         := $(TOP_LIBS_DIR)#
LIBEXIF_SOURCE      := $(LIBEXIF_DIR)/$(LIBEXIF)
LIBEXIF_CONFIG      := 

#
# Download  the source 
#
.PHONY: libexif-downloaded

libexif-downloaded: $(LIBEXIF_DIR)/.libexif_downloaded

$(LIBEXIF_DIR)/.libexif_downloaded:
	@echo "Downloading $(LIBEXIF) from $(LIBEXIF_SERVER_URL) ..."
	@if [ ! -d "$(LIBEXIF_SOURCE)" ]; then \
		cd $(LIBEXIF_DIR); \
		$(TOP_DOWNLOAD) $(LIBEXIF_SERVER_URL); \
	fi
	@echo "Downloading $(LIBEXIF) from $(LIBEXIF_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libexif-unpacked

libexif-unpacked: $(LIBEXIF_DIR)/.libexif_unpacked

$(LIBEXIF_DIR)/.libexif_unpacked: $(LIBEXIF_DIR)/.libexif_downloaded $(LIBEXIF_SOURCE)/$(LIBEXIF).tar.bz2
	@echo "Unpacking $(LIBEXIF) ..."
	if [ -d "$(LIBEXIF_SOURCE)/$(LIBEXIF)" ]; then \
		rm -fr $(LIBEXIF_SOURCE)/$(LIBEXIF); \
	fi
	cd $(LIBEXIF_SOURCE); tar xjvf $(LIBEXIF).tar.bz2
	@echo "Unpacking $(LIBEXIF) done"
	@touch $@


#
# Patch the source
#
.PHONY: libexif-patched

libexif-patched: $(LIBEXIF_DIR)/.libexif_patched

$(LIBEXIF_DIR)/.libexif_patched: $(LIBEXIF_DIR)/.libexif_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libexif-config

libexif-config: 

#
# Configuration
#
.PHONY: libexif-configured

libexif-configured:  libexif-config $(LIBEXIF_DIR)/.libexif_configured

$(LIBEXIF_DIR)/.libexif_configured: $(LIBEXIF_DIR)/.libexif_patched $(LIBEXIF_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBEXIF) ..."
	cd $(LIBEXIF_SOURCE)/$(LIBEXIF);./configure --prefix=$(LIBS_INSTALL_PATH)   --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)
	@echo "Configuring $(LIBEXIF) done"
	@touch $@

#
# Compile
#
.PHONY: libexif-compile

libexif-compile: $(LIBEXIF_DIR)/.libexif_compiled

$(LIBEXIF_DIR)/.libexif_compiled: $(LIBEXIF_DIR)/.libexif_configured
	@echo "Compiling $(LIBEXIF) ..."
	#make -C $(LIBEXIF_SOURCE)/$(LIBEXIF) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBEXIF_SOURCE)/$(LIBEXIF) 
	make -C $(LIBEXIF_SOURCE)/$(LIBEXIF)  install
	@echo "Compiling $(LIBEXIF) done"
	@touch $@

#
# Update
#
.PHONY: libexif-update

libexif-update:
	@echo "Updating $(LIBEXIF) ..."
	@if [ -d "$(LIBEXIF_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBEXIF_SOURCE); \
	fi
	@echo "Updating $(LIBEXIF) done"

#
# Status
#
.PHONY: libexif-status

libexif-status:
	@echo "Statusing $(LIBEXIF) ..."
	@if [ -d "$(LIBEXIF_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBEXIF_SOURCE); \
	fi
	@echo "Statusing $(LIBEXIF) done"

#
# Clean
#
.PHONY: libexif-clean

libexif-clean:
	@rm -f $(LIBEXIF_DIR)/.libexif_configured
	@if [ -d "$(LIBEXIF_SOURCE)" ]; then\
		make -C $(LIBEXIF_SOURCE)/$(LIBEXIF) clean; \
	fi

#
# Dist clean
#
.PHONY: libexif-distclean

libexif-distclean:
	@rm -f $(LIBEXIF_DIR)/.libexif_*

#
# Install
#
.PHONY: libexif-install

libexif-install:
