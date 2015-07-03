##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# libusb makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBUSB_VERSION 
CONF_LIBUSB_VERSION := 0.1.12
endif

LIBUSB             := libusb-$(CONF_LIBUSB_VERSION)#
LIBUSB_SERVER_URL  := $(TOP_LIBS_URL)/libusb/$(LIBUSB)
LIBUSB_DIR         := $(TOP_LIBS_DIR)#
LIBUSB_SOURCE      := $(LIBUSB_DIR)/$(LIBUSB)
LIBUSB_CONFIG      := 

#
# Download  the source 
#
.PHONY: libusb-downloaded

libusb-downloaded: $(LIBUSB_DIR)/.libusb_downloaded

$(LIBUSB_DIR)/.libusb_downloaded:
	@echo "Downloading $(LIBUSB) from $(LIBUSB_SERVER_URL) ..."
	@if [ ! -d "$(LIBUSB_SOURCE)" ]; then \
		cd $(LIBUSB_DIR); \
		$(TOP_DOWNLOAD) $(LIBUSB_SERVER_URL); \
	fi
	@echo "Downloading $(LIBUSB) from $(LIBUSB_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libusb-unpacked

libusb-unpacked: $(LIBUSB_DIR)/.libusb_unpacked

$(LIBUSB_DIR)/.libusb_unpacked: $(LIBUSB_DIR)/.libusb_downloaded $(LIBUSB_SOURCE)/$(LIBUSB).tar.gz
	@echo "Unpacking $(LIBUSB) ..."
	if [ -d "$(LIBUSB_SOURCE)/$(LIBUSB)" ]; then \
		rm -fr $(LIBUSB_SOURCE)/$(LIBUSB); \
	fi
	cd $(LIBUSB_SOURCE); tar zxvf $(LIBUSB).tar.gz
	@echo "Unpacking $(LIBUSB) done"
	@touch $@


#
# Patch the source
#
.PHONY: libusb-patched

libusb-patched: $(LIBUSB_DIR)/.libusb_patched

$(LIBUSB_DIR)/.libusb_patched: $(LIBUSB_DIR)/.libusb_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libusb-config

libusb-config: 

#
# Configuration
#
.PHONY: libusb-configured

libusb-configured:  libusb-config $(LIBUSB_DIR)/.libusb_configured

$(LIBUSB_DIR)/.libusb_configured: $(LIBUSB_DIR)/.libusb_patched $(LIBUSB_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBUSB) ..."
	cd $(LIBUSB_SOURCE)/$(LIBUSB);./configure --prefix=$(LIBS_INSTALL_PATH)   --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) 
	@echo "Configuring $(LIBUSB) done"
	@touch $@

#
# Compile
#
.PHONY: libusb-compile

libusb-compile: $(LIBUSB_DIR)/.libusb_compiled

$(LIBUSB_DIR)/.libusb_compiled: $(LIBUSB_DIR)/.libusb_configured
	@echo "Compiling $(LIBUSB) ..."
	#make -C $(LIBUSB_SOURCE)/$(LIBUSB) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBUSB_SOURCE)/$(LIBUSB) 
	make -C $(LIBUSB_SOURCE)/$(LIBUSB)  install
	@echo "Compiling $(LIBUSB) done"
	@touch $@

#
# Update
#
.PHONY: libusb-update

libusb-update:
	@echo "Updating $(LIBUSB) ..."
	@if [ -d "$(LIBUSB_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBUSB_SOURCE); \
	fi
	@echo "Updating $(LIBUSB) done"

#
# Status
#
.PHONY: libusb-status

libusb-status:
	@echo "Statusing $(LIBUSB) ..."
	@if [ -d "$(LIBUSB_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBUSB_SOURCE); \
	fi
	@echo "Statusing $(LIBUSB) done"

#
# Clean
#
.PHONY: libusb-clean

libusb-clean:
	@rm -f $(LIBUSB_DIR)/.libusb_configured
	@if [ -d "$(LIBUSB_SOURCE)" ]; then\
		make -C $(LIBUSB_SOURCE)/$(LIBUSB) clean; \
	fi

#
# Dist clean
#
.PHONY: libusb-distclean

libusb-distclean:
	@rm -f $(LIBUSB_DIR)/.libusb_*

#
# Install
#
.PHONY: libusb-install

libusb-install:
