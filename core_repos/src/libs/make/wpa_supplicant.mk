##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# wpa-supplicant makefile fragments 
##############################################################################

#
# Defines
#
ifndef  WPA_SUPPLICANT_VERSION 
WPA_SUPPLICANT_VERSION := 0.4.8_otus
endif

WPA_SUPPLICANT             := wpa_supplicant-$(WPA_SUPPLICANT_VERSION)#
WPA_SUPPLICANT_SERVER_URL  := $(TOP_LIBS_URL)/wpa_supplicant/$(WPA_SUPPLICANT)
WPA_SUPPLICANT_DIR         := $(TOP_LIBS_DIR)#
WPA_SUPPLICANT_SOURCE      := $(WPA_SUPPLICANT_DIR)/$(WPA_SUPPLICANT)
WPA_SUPPLICANT_CONFIG      := 


#
# Download  the source 
#
.PHONY: wpa_supplicant-downloaded

wpa_supplicant-downloaded: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_downloaded

$(WPA_SUPPLICANT_DIR)/.wpa_supplicant_downloaded:
	@echo "Downloading $(WPA_SUPPLICANT) from $(WPA_SUPPLICANT_SERVER_URL) ..."
	@if [ ! -d "$(WPA_SUPPLICANT_SOURCE)" ]; then \
		cd $(WPA_SUPPLICANT_DIR); \
		$(TOP_DOWNLOAD) $(WPA_SUPPLICANT_SERVER_URL); \
	fi
	@echo "Downloading $(WPA_SUPPLICANT) from $(WPA_SUPPLICANT_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: wpa_supplicant-unpacked

wpa_supplicant-unpacked: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_unpacked

$(WPA_SUPPLICANT_DIR)/.wpa_supplicant_unpacked: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: wpa_supplicant-patched

wpa_supplicant-patched: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_patched

$(WPA_SUPPLICANT_DIR)/.wpa_supplicant_patched: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: wpa_supplicant-config

wpa_supplicant-config: 

#
# Configuration
#
.PHONY: wpa_supplicant-configured

wpa_supplicant-configured:  wpa_supplicant-config $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_configured

$(WPA_SUPPLICANT_DIR)/.wpa_supplicant_configured: $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_patched $(WPA_SUPPLICANT_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: wpa_supplicant-compile

wpa_supplicant-compile: wpa_supplicant-configured $(WIRELESS_TOOLS_DIR)/.wpa_supplicant_compiled

$(WPA_SUPPLICANT_DIR)/.wpa_supplicant_compiled:
	@echo "Compiling $(WPA_SUPPLICANT) ..."
	make -C $(WPA_SUPPLICANT_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@echo "Compiling $(WPA_SUPPLICANT) done"
	@touch $@

#
# Update
#
.PHONY: wpa_supplicant-update

wpa_supplicant-update:
	@echo "Updating $(WPA_SUPPLICANT) ..."
	@if [ -d "$(WPA_SUPPLICANT_SOURCE)" ]; then\
		$(TOP_UPDATE) $(WPA_SUPPLICANT_SOURCE); \
	fi
	@echo "Updating $(WPA_SUPPLICANT) done"

#
# Status
#
.PHONY: wpa_supplicant-status

wpa_supplicant-status:
	@echo "Statusing $(WPA_SUPPLICANT) ..."
	@if [ -d "$(WPA_SUPPLICANT_SOURCE)" ]; then\
		$(TOP_STATUS) $(WPA_SUPPLICANT_SOURCE); \
	fi
	@echo "Statusing $(WPA_SUPPLICANT) done"

#
# Clean
#
.PHONY: wpa_supplicant-clean

wpa_supplicant-clean:
	@rm -f $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_configured
	@if [ -d "$(WPA_SUPPLICANT_SOURCE)" ]; then\
		make -C $(WPA_SUPPLICANT_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: wpa_supplicant-distclean

wpa_supplicant-distclean:
	@rm -f $(WPA_SUPPLICANT_DIR)/.wpa_supplicant_*

#
# Install
#
.PHONY: wpa_supplicant-install

wpa_supplicant-install:
	-mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	cp $(WPA_SUPPLICANT_SOURCE)/wpa_supplicant $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
