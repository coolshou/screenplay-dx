##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# flashlite3 makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_FLASHLITE3_VERSION 
CONF_FLASHLITE3_VERSION := SMP8654_3_8_0-3.mips
endif

SIGMA_SDK_SERVER_URL	:= $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_SOURCE		:= $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)#

FLASHLITE3_DIR			:= $(SIGMA_SDK_SOURCE)/flashlite3#
FLASHLITE3             := flashlite3_$(CONF_FLASHLITE3_VERSION)#
FLASHLITE3_SOURCE      := $(FLASHLITE3_DIR)/$(FLASHLITE3)#
FLASHLITE3_LIB_DIR     := $(FLASHLITE3_SOURCE)/targets/linux/SigmaDesigns/release#




# Download  the source 
#
.PHONY: flashlite3-downloaded

flashlite3-downloaded: 

#
# Unpack the source
#
.PHONY: flashlite3-unpacked

flashlite3-unpacked: $(TOP_LIBS_DIR)/.flashlite3_unpacked

$(TOP_LIBS_DIR)/.flashlite3_unpacked: $(FLASHLITE3_SOURCE).gz 
	@echo "Unpacking $(FLASHLITE3) ..."
	if [ -d "$(FLASHLITE3_SOURCE)" ]; then \
		rm -fr $(FLASHLITE3_SOURCE); \
	fi
	(cd $(FLASHLITE3_DIR); tar xvf $(FLASHLITE3).gz)
	@echo "Unpacking $(FLASHLITE3) done"
	@touch $@



#
# Patch the source
#
.PHONY: flashlite3-patched

flashlite3-patched: $(TOP_LIBS_DIR)/.flashlite3_patched

$(TOP_LIBS_DIR)/.flashlite3_patched: $(TOP_LIBS_DIR)/.flashlite3_unpacked
	# Patching...
ifeq (x$(CONF_FLASHLITE3_WITH_EDK), xy)
	rm -rf $(FLASHLITE3_SOURCE)/source/ae/edk/*;\
	cp -rf $(FLASHLITE3_DIR)/extensions/edk/* $(FLASHLITE3_SOURCE)/source/ae/edk/;
	cp -rf $(FLASHLITE3_DIR)/extensions/IEDKExtensions.mk $(FLASHLITE3_SOURCE)/build/linux/modules/IEDKExtensions.mk;
endif
	@touch $@

#
# config
#
.PHONY: flashlite3-config

flashlite3-config: 

#
# Configuration
#
.PHONY: flashlite3-configured

flashlite3-configured:  flashlite3-config $(TOP_LIBS_DIR)/.flashlite3_configured

$(TOP_LIBS_DIR)/.flashlite3_configured: $(TOP_LIBS_DIR)/.flashlite3_patched $(FLASHLITE3_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FLASHLITE3) ..."
	@touch $@

#
# Compile
#
.PHONY: flashlite3-compile

flashlite3-compile: $(TOP_LIBS_DIR)/.flashlite3_compiled

$(TOP_LIBS_DIR)/.flashlite3_compiled: $(TOP_LIBS_DIR)/.flashlite3_configured
ifeq (x$(CONF_FLASHLITE3_WITH_EDK), xy)
	cp -f $(FLASHLITE3_DIR)/extensions/Makefile $(FLASHLITE3_SOURCE)/build/linux/Makefile
	(cd $(FLASHLITE3_SOURCE)/build/linux/; make -f Makefile clean; make -f Makefile;);
	cp -avRf $(FLASHLITE3_LIB_DIR)/lib $(FLASHLITE3_SOURCE)
	cp -f $(FLASHLITE3_LIB_DIR)/bin/*.so $(FLASHLITE3_SOURCE)/lib
	cp -avRf $(FLASHLITE3_LIB_DIR)/bin $(FLASHLITE3_SOURCE)
endif
	@echo "Compiling $(FLASHLITE3) ..."
	@echo "Compiling $(FLASHLITE3) done"
	@touch $@

#
# Update
#
.PHONY: flashlite3-update

flashlite3-update:
	@echo "Updating $(FLASHLITE3) ..."
	@if [ -d "$(FLASHLITE3_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FLASHLITE3_SOURCE); \
	fi
	@echo "Updating $(FLASHLITE3) done"

#
# Status
#
.PHONY: flashlite3-status

flashlite3-status:
	@echo "Statusing $(FLASHLITE3) ..."
	@if [ -d "$(FLASHLITE3_SOURCE)" ]; then\
		$(TOP_STATUS) $(FLASHLITE3_SOURCE); \
	fi
	@echo "Statusing $(FLASHLITE3) done"

#
# Clean
#
.PHONY: flashlite3-clean

flashlite3-clean:
	@rm -f $(TOP_LIBS_DIR)/.flashlite3_configured

#
# Dist clean
#
.PHONY: flashlite3-distclean

flashlite3-distclean:
	@rm -f $(TOP_LIBS_DIR)/.flashlite3*

#
# Install
#
.PHONY: flashlite3-install

flashlite3-install:
	cp -avRf $(FLASHLITE3_SOURCE)/lib $(LIBS_INSTALL_PATH)/
ifeq (x$(CONF_FOR_ADOBE_CERT), xy)
	cp -avRf $(FLASHLITE3_SOURCE)/bin $(TOP_INSTALL_ROOTFS_DIR)/
endif # CONF_FOR_ADOBE_CERT
ifeq (x$(CONF_ENABLE_STAGECRAFT_PLAYER), xy)
	cp $(FLASHLITE3_SOURCE)/bin/stagecraft $(TOP_INSTALL_ROOTFS_DIR)/bin
endif
	mkdir -p $(TOP_BUILD_ROOTFS_DIR)/etc/stagecraft-data/ssl/certs
	cp $(FLASHLITE3_DIR)/ca-bundle.crt $(TOP_BUILD_ROOTFS_DIR)/etc/stagecraft-data/ssl/certs/
	(cd $(TOP_BUILD_ROOTFS_DIR);ln -s /tmp/stagecraft-data/shared-objects etc/stagecraft-data/shared-objects;)
	(cd $(TOP_BUILD_ROOTFS_DIR);ln -s /tmp/stagecraft-data/cookies etc/stagecraft-data/cookies;)
	mkdir -p $(TOP_BUILD_ROOTFS_DIR)/usr/lib
	(cd $(TOP_BUILD_ROOTFS_DIR);ln -s /etc/stagecraft-data/ssl/certs/ usr/lib/ssl;)
