##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# wireless-tools makefile fragments 
##############################################################################

#
# Defines
#
ifndef  WIRELESS_TOOLS_VERSION 
WIRELESS_TOOLS_VERSION := wireless_tools.29
endif

WIRELESS_TOOLS_SERVER_URL  := $(TOP_LIBS_URL)/wireless_tools/$(WIRELESS_TOOLS_VERSION)#
WIRELESS_TOOLS_DIR         := $(TOP_LIBS_DIR)#
WIRELESS_TOOLS_SOURCE      := $(WIRELESS_TOOLS_DIR)/$(WIRELESS_TOOLS_VERSION)#
WIRELESS_TOOLS_CONFIG      := 


#
# Download  the source 
#
.PHONY: wireless_tools-downloaded

wireless_tools-downloaded: $(WIRELESS_TOOLS_DIR)/.wireless_tools_downloaded

$(WIRELESS_TOOLS_DIR)/.wireless_tools_downloaded:
	@echo "Downloading $(WIRELESS_TOOLS_VERSION) from $(WIRELESS_TOOLS_SERVER_URL) ..."
	@if [ ! -d "$(WIRELESS_TOOLS_SOURCE)" ]; then \
		cd $(WIRELESS_TOOLS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_TOOLS_SERVER_URL); \
	fi
	@echo "Downloading $(WIRELESS_TOOLS_VERSION) done"
	@touch $@

#
# Unpack the source
#
.PHONY: wireless_tools-unpacked

wireless_tools-unpacked: $(WIRELESS_TOOLS_DIR)/.wireless_tools_unpacked

$(WIRELESS_TOOLS_DIR)/.wireless_tools_unpacked: $(WIRELESS_TOOLS_DIR)/.wireless_tools_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: wireless_tools-patched

wireless_tools-patched: $(WIRELESS_TOOLS_DIR)/.wireless_tools_patched

$(WIRELESS_TOOLS_DIR)/.wireless_tools_patched: $(WIRELESS_TOOLS_DIR)/.wireless_tools_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: wireless_tools-config

wireless_tools-config: 

#
# Configuration
#
.PHONY: wireless_tools-configured

wireless_tools-configured:  wireless_tools-config $(WIRELESS_TOOLS_DIR)/.wireless_tools_configured

$(WIRELESS_TOOLS_DIR)/.wireless_tools_configured: $(WIRELESS_TOOLS_DIR)/.wireless_tools_patched $(WIRELESS_TOOLS_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: wireless_tools-compile

wireless_tools-compile: wireless_tools-configured $(WIRELESS_TOOLS_DIR)/.wireless_tools_compiled

$(WIRELESS_TOOLS_DIR)/.wireless_tools_compiled:
	@echo "Compiling $(WIRELESS_TOOLS_VERSION) ..."
	make -C $(WIRELESS_TOOLS_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@echo "Compiling $(WIRELESS_TOOLS_VERSION) done"
	@touch $@

#
# Update
#
.PHONY: wireless_tools-update

wireless_tools-update:
	@echo "Updating $(WIRELESS_TOOLS_VERSION) ..."
	@if [ -d "$(WIRELESS_TOOLS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(WIRELESS_TOOLS_SOURCE); \
	fi
	@echo "Updating $(WIRELESS_TOOLS_VERSION) done"

#
# Status
#
.PHONY: wireless_tools-status

wireless_tools-status:
	@echo "Statusing $(WIRELESS_TOOLS) ..."
	@if [ -d "$(WIRELESS_TOOLS_SOURCE)" ]; then\
		$(TOP_STATUS) $(WIRELESS_TOOLS_SOURCE); \
	fi
	@echo "Statusing $(WIRELESS_TOOLS) done"

#
# Clean
#
.PHONY: wireless_tools-clean

wireless_tools-clean:
	@rm -f $(WIRELESS_TOOLS_DIR)/.wireless_tools_configured
	@if [ -d "$(WIRELESS_TOOLS_SOURCE)" ]; then\
		make -C $(WIRELESS_TOOLS_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: wireless_tools-distclean

wireless_tools-distclean:
	@rm -f $(WIRELESS_TOOLS_DIR)/.wireless_tools_*

#
# Install
#
.PHONY: wireless_tools-install

wireless_tools-install:
	-$(STRIP) --remove-section=.comment --remove-section=.note $(WIRELESS_TOOLS_SOURCE)/iwconfig
	-$(STRIP) --remove-section=.comment --remove-section=.note $(WIRELESS_TOOLS_SOURCE)/iwlist
	-$(STRIP) --remove-section=.comment --remove-section=.note $(WIRELESS_TOOLS_SOURCE)/iwpriv
	-$(STRIP) --remove-section=.comment --remove-section=.note $(WIRELESS_TOOLS_SOURCE)/iwspy
	-mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	cp $(WIRELESS_TOOLS_SOURCE)/iwconfig $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	cp $(WIRELESS_TOOLS_SOURCE)/iwlist   $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	cp $(WIRELESS_TOOLS_SOURCE)/iwpriv   $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
#	cp $(WIRELESS_TOOLS_SOURCE)/iwspy $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
