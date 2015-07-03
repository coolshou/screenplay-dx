##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# zeroconf makefile fragments 
##############################################################################

#
# Defines
#
ifndef  ZEROCONF_VERSION 
ZEROCONF_VERSION := 0.6
endif

ZEROCONF             := zeroconf-$(ZEROCONF_VERSION)# 
ZEROCONF_SERVER_URL  := $(TOP_LIBS_URL)/zeroconf/$(ZEROCONF)
ZEROCONF_DIR         := $(TOP_LIBS_DIR)#
ZEROCONF_SOURCE      := $(ZEROCONF_DIR)/$(ZEROCONF)
ZEROCONF_CONFIG      := 


#
# Download  the source 
#
.PHONY: zeroconf-downloaded

zeroconf-downloaded: $(ZEROCONF_DIR)/.zeroconf_downloaded

$(ZEROCONF_DIR)/.zeroconf_downloaded:
	@echo "Downdownloading $(ZEROCONF) from $(ZEROCONF_SERVER_URL) ..."
	@if [ ! -d "$(ZEROCONF_SOURCE)" ]; then \
		cd $(ZEROCONF_DIR); \
		$(TOP_DOWNLOAD) $(ZEROCONF_SERVER_URL); \
	fi
	@echo "Downdownloading $(ZEROCONF) done"
	@touch $@

#
# Unpack the source
#
.PHONY: zeroconf-unpacked

zeroconf-unpacked: $(ZEROCONF_DIR)/.zeroconf_unpacked

$(ZEROCONF_DIR)/.zeroconf_unpacked: $(ZEROCONF_DIR)/.zeroconf_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: zeroconf-patched

zeroconf-patched: $(ZEROCONF_DIR)/.zeroconf_patched

$(ZEROCONF_DIR)/.zeroconf_patched: $(ZEROCONF_DIR)/.zeroconf_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: zeroconf-config

zeroconf-config: 

#
# Configuration
#
.PHONY: zeroconf-configured

zeroconf-configured:  zeroconf-config $(ZEROCONF_DIR)/.zeroconf_configured

$(ZEROCONF_DIR)/.zeroconf_configured: $(ZEROCONF_DIR)/.zeroconf_patched $(ZEROCONF_CONFIG) $(TOP_CURRENT_SET)
	# Configuring...
	@touch $@

#
# Compile
#
.PHONY: zeroconf-compile

zeroconf-compile: zeroconf-configured
	@echo "Compiling $(ZEROCONF) ..."
	make -C $(ZEROCONF_SOURCE) -f Makefile.custom
	@echo "Compiling $(ZEROCONF) done"

#
# Update
#
.PHONY: zeroconf-update

zeroconf-update:
	@echo "Updating $(ZEROCONF) ..."
	@if [ -d "$(ZEROCONF_SOURCE)" ]; then\
		$(TOP_UPDATE) $(ZEROCONF_SOURCE); \
	fi
	@echo "Updating $(ZEROCONF) done"

#
# Status
#
.PHONY: zeroconf-status

zeroconf-status:
	@echo "Statusing $(ZEROCONF) ..."
	@if [ -d "$(ZEROCONF_SOURCE)" ]; then\
		$(TOP_STATUS) $(ZEROCONF_SOURCE); \
	fi
	@echo "Statusing $(ZEROCONF) done"

#
# Clean
#
.PHONY: zeroconf-clean

zeroconf-clean:
	@rm -f $(ZEROCONF_DIR)/.zeroconf_configured
	@if [ -d "$(ZEROCONF_SOURCE)" ]; then\
		make -C $(ZEROCONF_SOURCE) -f Makefile.custom clean; \
	fi

#
# Dist clean
#
.PHONY: zeroconf-distclean

zeroconf-distclean:
	@rm -f $(ZEROCONF_DIR)/.zeroconf_*

#
# Install
#
.PHONY: zeroconf-install

zeroconf-install:
	make -C $(ZEROCONF_SOURCE) -f Makefile.custom install
