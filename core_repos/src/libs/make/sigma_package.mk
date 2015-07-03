##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# sigma_package makefile fragments 
##############################################################################

#
# Defines
#

SIGMA_SDK_SERVER_URL  := $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_CONFIG      := 
RUA_DIR := $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)/MRUA_src
SIGMA_RUA_SDK	=	$(CONF_SIGMA_RUA_SDK)
SIGMA_RUA_FW	=	$(CONF_SIGMA_RUA_FW)
export SIGMA_RUA_SDK
export SIGMA_SDK_SOURCE
export SIGMA_RUA_FW

#
# Download  the source 
#
.PHONY: sigma_package-downloaded

sigma_package-downloaded: $(SIGMA_SDK_DIR)/.sigma_package_downloaded

$(SIGMA_SDK_DIR)/.sigma_package_downloaded:
	@echo "Downloading $(SIGMA_SDK_SOURCE) from $(SIGMA_SDK_SERVER_URL) ..."
	@if [ ! -d "$(SIGMA_SDK_SOURCE)" ]; then \
		cd $(SIGMA_SDK_DIR); \
		$(TOP_DOWNLOAD) $(SIGMA_SDK_SERVER_URL); \
	fi
	@echo "Downloading $(SIGMA_SDK_SOURCE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: sigma_package-unpacked

sigma_package-unpacked: $(SIGMA_SDK_DIR)/.sigma_package_unpacked

$(SIGMA_SDK_DIR)/.sigma_package_unpacked: $(SIGMA_SDK_DIR)/.sigma_package_downloaded
	@touch $@


#
# Patch the source
#
.PHONY: sigma_package-patched

sigma_package-patched: $(SIGMA_SDK_DIR)/.sigma_package_patched

$(SIGMA_SDK_DIR)/.sigma_package_patched: $(SIGMA_SDK_DIR)/.sigma_package_unpacked

#
# config
#
.PHONY: sigma_package-config

sigma_package-config: 

#
# Configuration
#
.PHONY: sigma_package-configured

sigma_package-configured:  sigma_package-config $(SIGMA_SDK_DIR)/.sigma_package_configured

$(SIGMA_SDK_DIR)/.sigma_package_configured: $(SIGMA_SDK_DIR)/.sigma_package_patched $(SIGMA_SDK_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: sigma_package-compile

sigma_package-compile: sigma_package-configured
	# Compiling...

#
# Update
#
.PHONY: sigma_package-update

sigma_package-update:
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) done"

#
# Status
#
.PHONY: sigma_package-status

sigma_package-status:
	@echo "Statusing $(SIGMA_SDK) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_STATUS) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Statusing $(SIGMA_SDK) done"

#
# Clean
#
.PHONY: sigma_package-clean

sigma_package-clean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_package_downloaded

#
# Dist clean
#
.PHONY: sigma_package-distclean

sigma_package-distclean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_package_*

#
# Install
#
.PHONY: sigma_package-install

sigma_package-install:

