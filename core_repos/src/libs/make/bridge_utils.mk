##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# bridge_utils makefile fragments 
##############################################################################

#
# Defines
#
ifndef  BRIDGE_UTILSVERSION 
BRIDGE_UTILSVERSION := 0.9.2
endif

BRIDGE_UTILS            := bridge_utils-$(BRIDGE_UTILSVERSION)#
BRIDGE_UTILS_SERVER_URL := $(TOP_LIBS_URL)/bridge_utils/$(BRIDGE_UTILS)
BRIDGE_UTILS_DIR        := $(TOP_LIBS_DIR)#
BRIDGE_UTILS_SOURCE     := $(BRIDGE_UTILS_DIR)/$(BRIDGE_UTILS)
BRIDGE_UTILSCONFIG      := 


#
# Download  the source 
#
.PHONY: bridge_utils-downloaded

bridge_utils-downloaded: $(BRIDGE_UTILS_DIR)/.bridge_utils_downloaded

$(BRIDGE_UTILS_DIR)/.bridge_utils_downloaded:
	@echo "Downloading $(BRIDGE_UTILS) from $(BRIDGE_UTILS_SERVER_URL) ..."
	@if [ ! -d "$(BRIDGE_UTILS_SOURCE)" ]; then \
		cd $(BRIDGE_UTILS_DIR); \
		$(TOP_DOWNLOAD) $(BRIDGE_UTILS_SERVER_URL); \
	fi
	@echo "Downloading $(BRIDGE_UTILS) done"
	@touch $@

#
# Unpack the source
#
.PHONY: bridge_utils-unpacked

bridge_utils-unpacked: $(BRIDGE_UTILS_DIR)/.bridge_utils_unpacked

$(BRIDGE_UTILS_DIR)/.bridge_utils_unpacked: $(BRIDGE_UTILS_DIR)/.bridge_utils_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: bridge_utils-patched

bridge_utils-patched: $(BRIDGE_UTILS_DIR)/.bridge_utils_patched

$(BRIDGE_UTILS_DIR)/.bridge_utils_patched: $(BRIDGE_UTILS_DIR)/.bridge_utils_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: bridge_utils-config

bridge_utils-config: 

#
# Configuration
#
.PHONY: bridge_utils-configured

bridge_utils-configured:  bridge_utils-config $(BRIDGE_UTILS_DIR)/.bridge_utils_configured

$(BRIDGE_UTILS_DIR)/.bridge_utils_configured: $(BRIDGE_UTILS_DIR)/.bridge_utils_patched $(BRIDGE_UTILSCONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: bridge_utils-compile

bridge_utils-compile: bridge_utils-configured
	@echo "Compiling $(BRIDGE_UTILS) ..."
	make -C $(BRIDGE_UTILS_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@echo "Compiling $(BRIDGE_UTILS) done"

#
# Update
#
.PHONY: bridge_utils-update

bridge_utils-update:
	@echo "Updating $(BRIDGE_UTILS) ..."
	@if [ -d "$(BRIDGE_UTILS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(BRIDGE_UTILS_SOURCE); \
	fi
	@echo "Updating $(BRIDGE_UTILS) done"

#
# Status
#
.PHONY: bridge_utils-status

bridge_utils-status:
	@echo "Statusing $(BRIDGE_UTILS) ..."
	@if [ -d "$(BRIDGE_UTILS_SOURCE)" ]; then\
		$(TOP_STATUS) $(BRIDGE_UTILS_SOURCE); \
	fi
	@echo "Statusing $(BRIDGE_UTILS) done"


#
# Clean
#
.PHONY: bridge_utils-clean

bridge_utils-clean:
	@rm -f $(BRIDGE_UTILS_DIR)/.bridge_utils_configured
	@if [ -d "$(BRIDGE_UTILS_SOURCE)" ]; then\
		make -C $(BRIDGE_UTILS_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: bridge_utils-distclean

bridge_utils-distclean:
	@rm -f $(BRIDGE_UTILS_DIR)/.bridge_utils_*
#@rm -fr $(BRIDGE_UTILS_SOURCE)

#
# Install
#
.PHONY: bridge_utils-install

bridge_utils-install:
	$(STRIP) --remove-section=.comment --remove-section=.note $(BRIDGE_UTILS_SOURCE)/brctl/brctl
	cp -f $(BRIDGE_UTILS_SOURCE)/brctl/brctl $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
