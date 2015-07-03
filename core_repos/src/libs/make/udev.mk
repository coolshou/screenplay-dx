##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  joshua_lee@alphanetworks.com
# udev makefile fragments 
##############################################################################

#
# Defines
#
ifndef  UDEV_VERSION 
UDEV_VERSION := 120
endif

UDEV             := udev-$(UDEV_VERSION)#
UDEV_SERVER_URL  := $(TOP_LIBS_URL)/udev/$(UDEV)
UDEV_DIR         := $(TOP_LIBS_DIR)#
UDEV_SOURCE      := $(UDEV_DIR)/$(UDEV)
UDEV_CONFIG      := 


#
# Download  the source 
#
.PHONY: udev-downloaded

udev-downloaded: $(UDEV_DIR)/.udev_downloaded

$(UDEV_DIR)/.udev_downloaded:
	@echo "Downloading $(UDEV) from $(UDEV_SERVER_URL) ..."
	@if [ ! -d "$(UDEV_SOURCE)" ]; then \
		cd $(UDEV_DIR); \
		$(TOP_DOWNLOAD) $(UDEV_SERVER_URL); \
	fi
	@echo "Downloading $(UDEV) done"
	@touch $@

#
# Unpack the source
#
.PHONY: udev-unpacked

udev-unpacked: $(UDEV_DIR)/.udev_unpacked

$(UDEV_DIR)/.udev_unpacked: $(UDEV_DIR)/.udev_downloaded
	@echo "Unpacking $(UDEV) ..."
	if [ -d "$(UDEV_SOURCE)/$(UDEV)" ]; then \
		rm -fr $(UDEV_SOURCE)/$(UDEV); \
	fi
	cd $(UDEV_SOURCE); tar jxvf $(UDEV).tar.bz2
	@echo "Unpacking $(UDEV) done"
	@touch $@


#
# Patch the source
#
.PHONY: udev-patched

udev-patched: $(UDEV_DIR)/.udev_patched

$(UDEV_DIR)/.udev_patched: $(UDEV_DIR)/.udev_unpacked
	# Patching...
	@touch $@


#
# Configuration
#
.PHONY: udev-configured

udev-configured:  $(UDEV_DIR)/.udev_configured

$(UDEV_DIR)/.udev_configured: $(UDEV_DIR)/.udev_patched $(TOP_CURRENT_SET)
	@echo "Configuring $(UDEV) ..."
	@echo "Configuring $(UDEV) done"
	@touch $@

#
# Compile
#
.PHONY: udev-compile

udev-compile: udev-configured
	@echo "Compiling $(UDEV) ..." 
	-make CROSS_COMPILE="$(CROSS)" -C $(UDEV_SOURCE)/$(UDEV)
	@echo "Compiling $(UDEV) done" 

#
# Update
#
.PHONY: udev-update

udev-update:
	@echo "Updating $(UDEV) ..."
	@if [ -d "$(UDEV_SOURCE)" ]; then\
		$(TOP_UPDATE) $(UDEV_SOURCE); \
	fi
	@echo "Updating $(UDEV) done"

#
# Status
#
.PHONY: udev-status

udev-status:
	@echo "Statusing $(UDEV) ..."
	@echo "Statusing $(UDEV) done"

#
# Clean
#
.PHONY: udev-clean

udev-clean:
	@rm -f $(UDEV_DIR)/.udev_configured
	@if [ -d "$(UDEV_SOURCE)" ]; then\
		make -C $(UDEV_SOURCE)/$(UDEV) clean; \
	fi

#
# Dist clean
#
.PHONY: udev-distclean

udev-distclean:
	@rm -f $(UDEV_DIR)/.udev_*

#
# Install
#
.PHONY: udev-install

udev-install:
	-make -C $(UDEV_SOURCE)/$(UDEV)  CC=$(CC) CROSS_COMPILE="$(CROSS)" DESTDIR=$(TOP_INSTALL_ROOTFS_DIR) install-bin

