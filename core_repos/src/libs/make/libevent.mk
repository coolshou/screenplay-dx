##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libevent makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBEVENT_VERSION 
LIBEVENT_VERSION := 1.4.14b-stable
endif

LIBEVENT             := libevent-$(LIBEVENT_VERSION)#
LIBEVENT_SERVER_URL  := $(TOP_LIBS_URL)/libevent/$(LIBEVENT)
LIBEVENT_DIR         := $(TOP_LIBS_DIR)#
LIBEVENT_SOURCE      := $(LIBEVENT_DIR)/$(LIBEVENT)
LIBEVENT_BUILD_DIR   := $(LIBEVENT_SOURCE)/$(LIBEVENT)/build
LIBEVENT_CONFIG      := 


#
# Download  the source 
#
.PHONY: libevent-downloaded

libevent-downloaded: $(LIBEVENT_DIR)/.libevent_downloaded

$(LIBEVENT_DIR)/.libevent_downloaded:
	@echo "Downloading $(LIBEVENT) from $(LIBEVENT_SERVER_URL) ..."
	@if [ ! -d "$(LIBEVENT_SOURCE)" ]; then \
		cd $(LIBEVENT_DIR); \
		$(TOP_DOWNLOAD) $(LIBEVENT_SERVER_URL); \
	fi
	@echo "Downloading $(LIBEVENT) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libevent-unpacked

libevent-unpacked: $(LIBEVENT_DIR)/.libevent_unpacked

$(LIBEVENT_DIR)/.libevent_unpacked: $(LIBEVENT_DIR)/.libevent_downloaded $(wildcard $(LIBEVENT_SOURCE)/*.tar.gz)
	@echo "Unpacking $(LIBEVENT) ..."
	if [ -d "$(LIBEVENT_SOURCE)/$(LIBEVENT)" ]; then \
		rm -fr $(LIBEVENT_SOURCE)/$(LIBEVENT); \
	fi
	cd $(LIBEVENT_SOURCE);tar xvzf  $(LIBEVENT).tar.gz
	@echo "Unpacking $(LIBEVENT) done"
	@touch $@


#
# Patch the source
#
.PHONY: libevent-patched

libevent-patched: $(LIBEVENT_DIR)/.libevent_patched

$(LIBEVENT_DIR)/.libevent_patched: $(LIBEVENT_DIR)/.libevent_unpacked
# Patching...
	@echo "Patching $(LIBEVENT) ..."
	@echo "Patching $(LIBEVENT) done"
	@touch $@

#
# config
#
.PHONY: libevent-config

libevent-config: 

#
# Configuration
#
.PHONY: libevent-configured

libevent-configured:  libevent-config $(LIBEVENT_DIR)/.libevent_configured

$(LIBEVENT_DIR)/.libevent_configured: $(LIBEVENT_DIR)/.libevent_patched $(LIBEVENT_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBEVENT) ..."
	cd $(LIBEVENT_SOURCE)/$(LIBEVENT); ./configure --prefix=$(LIBS_INSTALL_PATH) --exec-prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-static=no --enable-shared=yes
	@echo "Configuring $(LIBEVENT) done"
	@touch $@

#
# Compile
#
.PHONY: libevent-compile

libevent-compile: $(LIBEVENT_DIR)/.libevent_compiled

$(LIBEVENT_DIR)/.libevent_compiled: $(LIBEVENT_DIR)/.libevent_configured
	@echo "Compiling $(LIBEVENT) ..."
	make -C $(LIBEVENT_SOURCE)/$(LIBEVENT) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBEVENT_SOURCE)/$(LIBEVENT) install
	@echo "Compiling $(LIBEVENT) done"
	@touch $@

#
# Update
#
.PHONY: libevent-update

libevent-update:
	@echo "Updating $(LIBEVENT) ..."
	@if [ -d "$(LIBEVENT_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBEVENT_SOURCE); \
	fi
	@echo "Updating $(LIBEVENT) done"

#
# Status
#
.PHONY: libevent-status

libevent-status:
	@echo "Statusing $(LIBEVENT) ..."
	@if [ -d "$(LIBEVENT_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBEVENT_SOURCE); \
	fi
	@echo "Statusing $(LIBEVENT) done"

#
# Clean
#
.PHONY: libevent-clean

libevent-clean:
	@rm -f $(LIBEVENT_DIR)/.libevent_configured
	@if [ -d "$(LIBEVENT_SOURCE)" ]; then\
		make -C $(LIBEVENT_SOURCE)/$(LIBEVENT) clean; \
	fi

#
# Dist clean
#
.PHONY: libevent-distclean

libevent-distclean:
	@rm -f $(LIBEVENT_DIR)/.libevent_*

#
# Install
#
.PHONY: libevent-install

libevent-install:
