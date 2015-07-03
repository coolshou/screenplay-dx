##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libvorbis makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBVORBIS_VERSION 
LIBVORBIS_VERSION := 1.1.2
endif

LIBVORBIS             := libvorbis-$(LIBVORBIS_VERSION)#
LIBVORBIS_SERVER_URL  := $(TOP_LIBS_URL)/libvorbis/$(LIBVORBIS)#
LIBVORBIS_DIR         := $(TOP_LIBS_DIR)#
LIBVORBIS_SOURCE      := $(LIBVORBIS_DIR)/$(LIBVORBIS)#
LIBVORBIS_CONFIG      := 


#
# Download  the source 
#
.PHONY: libvorbis-downloaded

libvorbis-downloaded: $(LIBVORBIS_DIR)/.libvorbis_downloaded

$(LIBVORBIS_DIR)/.libvorbis_downloaded:
	@echo "Downloading $(LIBVORBIS) from $(LIBVORBIS_SERVER_URL) ..."
	@if [ ! -d "$(LIBVORBIS_SOURCE)" ]; then \
		cd $(LIBVORBIS_DIR); \
		$(TOP_DOWNLOAD) $(LIBVORBIS_SERVER_URL); \
	fi
	@echo "Downloading $(LIBVORBIS) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libvorbis-unpacked

libvorbis-unpacked: $(LIBVORBIS_DIR)/.libvorbis_unpacked

$(LIBVORBIS_DIR)/.libvorbis_unpacked: $(LIBVORBIS_DIR)/.libvorbis_downloaded $(LIBVORBIS_SOURCE)/$(LIBVORBIS).tar.gz
	@echo "Unpacking $(LIBVORBIS) ..."
	if [ -d "$(LIBVORBIS_SOURCE)/$(LIBVORBIS)" ]; then \
		rm -fr $(LIBVORBIS_SOURCE)/$(LIBVORBIS);\
	fi
	cd $(LIBVORBIS_SOURCE); tar zxvf $(LIBVORBIS).tar.gz
	@echo "Unpacking $(LIBVORBIS) done"
	@touch $@


#
# Patch the source
#
.PHONY: libvorbis-patched

libvorbis-patched: $(LIBVORBIS_DIR)/.libvorbis_patched

$(LIBVORBIS_DIR)/.libvorbis_patched: $(LIBVORBIS_DIR)/.libvorbis_unpacked
	# Patching...
	@echo "Patching $(LIBVORBIS) ..."
	-cd $(LIBVORBIS_SOURCE); patch -p0 < $(LIBVORBIS).patch
	@echo "Patching $(LIBVORBIS) done"
	@touch $@

#
# config
#
.PHONY: libvorbis-config

libvorbis-config: 

#
# Configuration
#
.PHONY: libvorbis-configured

libvorbis-configured:  libvorbis-config $(LIBVORBIS_DIR)/.libvorbis_configured

$(LIBVORBIS_DIR)/.libvorbis_configured: $(LIBVORBIS_DIR)/.libvorbis_patched $(LIBVORBIS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBVORBIS) ..."
	cd $(LIBVORBIS_SOURCE)/$(LIBVORBIS); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB)
	@echo "Configuring $(LIBVORBIS) done"
	@touch $@

#
# Compile
#
.PHONY: libvorbis-compile

libvorbis-compile: $(LIBVORBIS_DIR)/.libvorbis_compiled

$(LIBVORBIS_DIR)/.libvorbis_compiled: $(LIBVORBIS_DIR)/.libvorbis_configured
	@echo "Compiling $(LIBVORBIS) ..."
	make -C $(LIBVORBIS_SOURCE)/$(LIBVORBIS) 
	make -C $(LIBVORBIS_SOURCE)/$(LIBVORBIS) install
	@echo "Compiling $(LIBVORBIS) done"
	@touch $@

#
# Update
#
.PHONY: libvorbis-update

libvorbis-update:
	@echo "Updating $(LIBVORBIS) ..."
	@if [ -d "$(LIBVORBIS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBVORBIS_SOURCE); \
	fi
	@echo "Updating $(LIBVORBIS) done"

#
# Status
#
.PHONY: libvorbis-status

libvorbis-status:
	@echo "Statusing $(LIBVORBIS) ..."
	@if [ -d "$(LIBVORBIS_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBVORBIS_SOURCE); \
	fi
	@echo "Statusing $(LIBVORBIS) done"

#
# Clean
#
.PHONY: libvorbis-clean

libvorbis-clean:
	@rm -f $(LIBVORBIS_DIR)/.libvorbis_configured
	@if [ -d "$(LIBVORBIS_SOURCE)" ]; then\
		make -C $(LIBVORBIS_SOURCE)/$(LIBVORBIS) clean; \
	fi

#
# Dist clean
#
.PHONY: libvorbis-distclean

libvorbis-distclean:
	@rm -f $(LIBVORBIS_DIR)/.libvorbis_*

#
# Install
#
.PHONY: libvorbis-install

libvorbis-install:
