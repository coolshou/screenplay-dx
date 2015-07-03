##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# sigma_key_tools makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_JANUS_KEY_TOOLS_VERSION 
CONF_JANUS_KEY_TOOLS_VERSION := janus_pk-8644-0_4-t3-1
endif

SIGMA_KEY_TOOLS_SERVER_URL  := $(TOP_LIBS_URL)/sigma_sdk/key_tools
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_KEY_TOOL_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)/key_tools
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
.PHONY: sigma_key_tools-downloaded

sigma_key_tools-downloaded: $(SIGMA_SDK_DIR)/.sigma_key_tools_downloaded

$(SIGMA_SDK_DIR)/.sigma_key_tools_downloaded:
	@echo "Downloading $(SIGMA_SDK_SOURCE) from $(SIGMA_KEY_TOOLS_SERVER_URL) ..."
	rm -fr $(SIGMA_KEY_TOOL_SOURCE)
	rm -fr $(SIGMA_SDK_SOURCE)/$(CONF_JANUS_KEY_TOOLS_VERSION)
	cd $(SIGMA_SDK_SOURCE); $(TOP_DOWNLOAD) $(SIGMA_KEY_TOOLS_SERVER_URL);
	@echo "Downloading key tools done"
	@touch $@

#
# Unpack the source
#
.PHONY: sigma_key_tools-unpacked

sigma_key_tools-unpacked: $(SIGMA_SDK_DIR)/.sigma_key_tools_unpacked

$(SIGMA_SDK_DIR)/.sigma_key_tools_unpacked:sigma_key_tools-downloaded
	@echo "Unpacking key tools "
	cd $(SIGMA_SDK_SOURCE); tar zxvf $(SIGMA_KEY_TOOL_SOURCE)/$(CONF_JANUS_KEY_TOOLS_VERSION).tar.gz;
	@touch $@

#
# Patch the source
#
.PHONY: sigma_key_tools-patched

sigma_key_tools-patched: $(SIGMA_SDK_DIR)/.sigma_key_tools_patched

$(SIGMA_SDK_DIR)/.sigma_key_tools_patched: $(SIGMA_SDK_DIR)/.sigma_key_tools_unpacked
	@touch $@

#
# config
#
.PHONY: sigma_key_tools-config

sigma_key_tools-config: 

#
# Configuration
#
.PHONY: sigma_key_tools-configured

sigma_key_tools-configured:  sigma_key_tools-config $(SIGMA_SDK_DIR)/.sigma_key_tools_configured

$(SIGMA_SDK_DIR)/.sigma_key_tools_configured: $(SIGMA_SDK_DIR)/.sigma_key_tools_patched $(SIGMA_SDK_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: sigma_key_tools-compile

sigma_key_tools-compile: sigma_key_tools-unpacked
	 @echo "Compiling sigma key tools ..."
	 make -f $(SIGMA_SDK_SOURCE)/compile.mk sigma_key_tools
	 @echo "Compiling sigma key tools done"
	 @touch $@

#
# Update
#
.PHONY: sigma_key_tools-update

sigma_key_tools-update:
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) done"

#
# Status
#
.PHONY: sigma_key_tools-status

sigma_key_tools-status:
	@echo "Statusing $(SIGMA_SDK) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_STATUS) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Statusing $(SIGMA_SDK) done"

#
# Clean
#
.PHONY: sigma_key_tools-clean

sigma_key_tools-clean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_key_tools_downloaded

#
# Dist clean
#
.PHONY: sigma_key_tools-distclean

sigma_key_tools-distclean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_key_tools_*

#
# Install
#
.PHONY: sigma_key_tools-install

sigma_key_tools-install:

