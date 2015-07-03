##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libxml2 makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBXML2VERSION 
LIBXML2VERSION := 2.6.32
endif

LIBXML2             := libxml2-$(LIBXML2VERSION)#
LIBXML2_SERVER_URL  := $(TOP_LIBS_URL)/libxml2/$(LIBXML2)
LIBXML2_DIR         := $(TOP_LIBS_DIR)#
LIBXML2_SOURCE      := $(LIBXML2_DIR)/$(LIBXML2)
LIBXML2CONFIG       := 


#
# Download  the source 
#
.PHONY: libxml2-downloaded

libxml2-downloaded: $(LIBXML2_DIR)/.libxml2_downloaded

$(LIBXML2_DIR)/.libxml2_downloaded:
	@echo "Downloading $(LIBXML2) from $(LIBXML2_SERVER_URL) ..."
	@if [ ! -d "$(LIBXML2_SOURCE)" ]; then \
		cd $(LIBXML2_DIR); \
		$(TOP_DOWNLOAD) $(LIBXML2_SERVER_URL); \
	fi
	@echo "Downloading $(LIBXML2) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libxml2-unpacked

libxml2-unpacked: $(LIBXML2_DIR)/.libxml2_unpacked

$(LIBXML2_DIR)/.libxml2_unpacked: $(LIBXML2_DIR)/.libxml2_downloaded $(LIBXML2_SOURCE)/$(LIBXML2).tar.gz
	@echo "Unpacking the $(LIBXML2) ..."
	if [ -d "$(LIBXML2_SOURCE)/$(LIBXML2)" ]; then \
		rm -fr $(LIBXML2_SOURCE)/$(LIBXML2); \
	fi
	cd $(LIBXML2_SOURCE); tar xzvf $(LIBXML2).tar.gz
	@echo "Unpacking the $(LIBXML2) done"
	@touch $@


#
# Patch the source
#
.PHONY: libxml2-patched

libxml2-patched: $(LIBXML2_DIR)/.libxml2_patched

$(LIBXML2_DIR)/.libxml2_patched: $(LIBXML2_DIR)/.libxml2_unpacked
	cd $(LIBXML2_SOURCE)/; patch -p0 < $(LIBXML2_SOURCE)/$(LIBXML2).patch 
	@touch $@

#
# config
#
.PHONY: libxml2-config

libxml2-config: 

#
# Configuration
#
.PHONY: libxml2-configured

libxml2-configured:  libxml2-config $(LIBXML2_DIR)/.libxml2_configured

$(LIBXML2_DIR)/.libxml2_configured: $(LIBXML2_DIR)/.libxml2_patched $(LIBXML2CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBXML2) ..."
	cd $(LIBXML2_SOURCE)/$(LIBXML2);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB)  --with-minimum --with-sax1 --with-xpath --with-output --with-push --with-tree --with-valid --with-xinclude --with-c14n --with-xptr --with-reader --with-writer
	@echo "Configuring $(LIBXML2) done"
	@touch $@

#
# Compile
#
.PHONY: libxml2-compile

libxml2-compile: $(LIBXML2_DIR)/.libxml2_compiled

$(LIBXML2_DIR)/.libxml2_compiled: $(LIBXML2_DIR)/.libxml2_configured
	@echo "Compiling $(LIBXML) ..."
	make -C $(LIBXML2_SOURCE)/$(LIBXML2) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBXML2_SOURCE)/$(LIBXML2) install
	ln -sf $(LIBS_INSTALL_PATH)/include/libxml2/libxml/  $(LIBS_INSTALL_PATH)/include/libxml
	@echo "Compiling $(LIBXML) done"
	@touch $@

#
# Update
#
.PHONY: libxml2-update

libxml2-update:
	@echo "Updating $(LIBXML2) ..."
	@if [ -d "$(LIBXML2_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBXML2_SOURCE); \
	fi
	@echo "Updating $(LIBXML2) done"

#
# Status
#
.PHONY: libxml2-status

libxml2-status:
	@echo "Statusing $(LIBXML2) ..."
	@if [ -d "$(LIBXML2_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBXML2_SOURCE); \
	fi
	@echo "Statusing $(LIBXML2) done"

#
# Clean
#
.PHONY: libxml2-clean

libxml2-clean:
	@rm -f $(LIBXML2_DIR)/.libxml2_configured
	@if [ -d "$(LIBXML2_SOURCE)" ]; then\
		make -C $(LIBXML2_SOURCE)/$(LIBXML2) clean; \
	fi

#
# Dist clean
#
.PHONY: libxml2-distclean

libxml2-distclean:
	@rm -f $(LIBXML2_DIR)/.libxml2_*

#
# Install
#
.PHONY: libxml2-install

libxml2-install:
