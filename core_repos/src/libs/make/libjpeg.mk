##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libjpeg makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBJPEG_VERSION 
CONF_LIBJPEG_VERSION := v6b
endif

LIBJPEG             := libjpeg-$(CONF_LIBJPEG_VERSION)#

LIBJPEG_SERVER_URL  := $(TOP_LIBS_URL)/libjpeg/$(LIBJPEG)
LIBJPEG_DIR         := $(TOP_LIBS_DIR)#
LIBJPEG_SOURCE      := $(LIBJPEG_DIR)/$(LIBJPEG)#
LIBJPEG_CONFIG      := 

ifeq (x$(ENABLE_SHLIB),xyes)
LIBJPEG_SHARED_FLAGS      := --enable-shared
endif


#
# Download  the source 
#
.PHONY: libjpeg-downloaded

libjpeg-downloaded: $(LIBJPEG_DIR)/.libjpeg_downloaded

$(LIBJPEG_DIR)/.libjpeg_downloaded:
	@echo "Downloading $(LIBJPEG) from $(LIBJPEG_SERVER_URL) ..."
	@if [ ! -d "$(LIBJPEG_SOURCE)" ]; then \
		cd $(LIBJPEG_DIR); \
		$(TOP_DOWNLOAD) $(LIBJPEG_SERVER_URL); \
	fi
	@echo "Downloading $(LIBJPEG) from $(LIBJPEG_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libjpeg-unpacked

libjpeg-unpacked: $(LIBJPEG_DIR)/.libjpeg_unpacked

$(LIBJPEG_DIR)/.libjpeg_unpacked: $(LIBJPEG_DIR)/.libjpeg_downloaded $(LIBJPEG_SOURCE)/jpegsrc.$(CONF_LIBJPEG_VERSION).tar.gz
	@echo "Unpacking $(LIBJPEG) ..."
	if [ -d "$(LIBJPEG_SOURCE)/jpeg-6b" ]; then \
		rm -fr $(LIBJPEG_SOURCE)/jpeg-6b; \
	fi
	cd $(LIBJPEG_SOURCE); tar zxvf jpegsrc.$(CONF_LIBJPEG_VERSION).tar.gz; 
	cd $(LIBJPEG_SOURCE); tar zxvf libtool-1.5.24.tar.gz; 
	@echo "Unpacking $(LIBJPEG) done"
	@touch $@


#
# Patch the source
#
.PHONY: libjpeg-patched

libjpeg-patched: $(LIBJPEG_DIR)/.libjpeg_patched

$(LIBJPEG_DIR)/.libjpeg_patched: $(LIBJPEG_DIR)/.libjpeg_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libjpeg-config

libjpeg-config: 

#
# Configuration
#
.PHONY: libjpeg-configured

libjpeg-configured:  libjpeg-config $(LIBJPEG_DIR)/.libjpeg_configured

$(LIBJPEG_DIR)/.libjpeg_configured: $(LIBJPEG_DIR)/.libjpeg_patched $(LIBJPEG_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring the $(LIBJPEG) ..."
	cd $(LIBJPEG_SOURCE)/libtool-1.5.24; ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --disable-nls 
	cd $(LIBJPEG_SOURCE)/jpeg-6b; ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) $(LIBJPEG_SHARED_FLAGS) 
	@echo "Configuring the $(LIBJPEG) done"
	@touch $@

#
# Compile
#
.PHONY: libjpeg-compile

libjpeg-compile: $(LIBJPEG_DIR)/.libjpeg_compiled

$(LIBJPEG_DIR)/.libjpeg_compiled:$(LIBJPEG_DIR)/.libjpeg_configured
	@echo "Compiling the $(LIBJPEG) ..."
	make -C $(LIBJPEG_SOURCE)/libtool-1.5.24
	cp -f $(LIBJPEG_SOURCE)/libtool-1.5.24/libtool $(LIBJPEG_SOURCE)/jpeg-6b/
	make -C $(LIBJPEG_SOURCE)/jpeg-6b
	make -C $(LIBJPEG_SOURCE)/jpeg-6b install-lib 
	@echo "Compiling the $(LIBJPEG) done"
	@touch $@

#
# Update
#
.PHONY: libjpeg-update

libjpeg-update:
	@echo "Updating $(LIBJPEG) ..."
	@if [ -d "$(LIBJPEG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBJPEG_SOURCE); \
	fi
	@echo "Updating $(LIBJPEG) done"

#
# Status
#
.PHONY: libjpeg-status

libjpeg-status:
	@echo "Statusing $(LIBJPEG) ..."
	@if [ -d "$(LIBJPEG_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBJPEG_SOURCE); \
	fi
	@echo "Statusing $(LIBJPEG) done"

#
# Clean
#
.PHONY: libjpeg-clean

libjpeg-clean:
	@rm -f $(LIBJPEG_DIR)/.libjpeg_configured
	@if [ -d "$(LIBJPEG_SOURCE)" ]; then\
		make -C $(LIBJPEG_SOURCE)/jpeg-6b clean; \
	fi

#
# Dist clean
#
.PHONY: libjpeg-distclean

libjpeg-distclean:
	@rm -f $(LIBJPEG_DIR)/.libjpeg_*

#
# Install
#
.PHONY: libjpeg-install

libjpeg-install:
