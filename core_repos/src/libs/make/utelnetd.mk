##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# utelnetd makefile fragments 
##############################################################################

#
# Defines
#
ifndef  UTELNETD_VERSION 
UTELNETD_VERSION := 0.1.9
endif

UTELNETD             := utelnetd-$(UTELNETD_VERSION)#
UTELNETD_SERVER_URL  := $(TOP_LIBS_URL)/utelnetd/$(UTELNETD)
UTELNETD_DIR         := $(TOP_LIBS_DIR)#
UTELNETD_SOURCE      := $(UTELNETD_DIR)/$(UTELNETD)
UTELNETD_CONFIG      := 


#
# Download  the source 
#
.PHONY: utelnetd-downloaded

utelnetd-downloaded: $(UTELNETD_DIR)/.utelnetd_downloaded

$(UTELNETD_DIR)/.utelnetd_downloaded:
	@echo "Dowloading $(UTELNETD) from $(UTELNETD_SERVER_URL) ..."
	@if [ ! -d "$(UTELNETD_SOURCE)" ]; then \
		cd $(UTELNETD_DIR); \
		$(TOP_DOWNLOAD) $(UTELNETD_SERVER_URL); \
	fi
	@echo "Dowloading $(UTELNETD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: utelnetd-unpacked

utelnetd-unpacked: $(UTELNETD_DIR)/.utelnetd_unpacked

$(UTELNETD_DIR)/.utelnetd_unpacked: $(UTELNETD_DIR)/.utelnetd_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: utelnetd-patched

utelnetd-patched: $(UTELNETD_DIR)/.utelnetd_patched

$(UTELNETD_DIR)/.utelnetd_patched: $(UTELNETD_DIR)/.utelnetd_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: utelnetd-config

utelnetd-config: 

#
# Configuration
#
.PHONY: utelnetd-configured

utelnetd-configured:  utelnetd-config $(UTELNETD_DIR)/.utelnetd_configured

$(UTELNETD_DIR)/.utelnetd_configured: $(UTELNETD_DIR)/.utelnetd_patched $(UTELNETD_CONFIG) $(TOP_CURRENT_SET)
	# Configuring...
	@touch $@

#
# Compile
#
.PHONY: utelnetd-compile

utelnetd-compile: utelnetd-configured
	@echo "Compiling $(UTELNETD) ..."
	make -C $(UTELNETD_SOURCE) -f Makefile.custom
	@echo "Compiling $(UTELNETD) done"

#
# Update
#
.PHONY: utelnetd-update

utelnetd-update:
	@echo "Updating $(UTELNETD) ..."
	@if [ -d "$(UTELNETD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(UTELNETD_SOURCE); \
	fi
	@echo "Updating $(UTELNETD) done"

#
# Status
#
.PHONY: utelnetd-status

utelnetd-status:
	@echo "Statusing $(UTELNETD) ..."
	@if [ -d "$(UTELNETD_SOURCE)" ]; then\
		$(TOP_STATUS) $(UTELNETD_SOURCE); \
	fi
	@echo "Statusing $(UTELNETD) done"

#
# Clean
#
.PHONY: utelnetd-clean

utelnetd-clean:
	@rm -f $(UTELNETD_DIR)/.utelnetd_configured
	@if [ -d "$(UTELNETD_SOURCE)" ]; then\
		make -C $(UTELNETD_SOURCE) -f Makefile.custom clean; \
	fi

#
# Dist clean
#
.PHONY: utelnetd-distclean

utelnetd-distclean:
	@rm -f $(UTELNETD_DIR)/.utelnetd_*

#
# Install
#
.PHONY: utelnetd-install

utelnetd-install:
	-make -C $(UTELNETD_SOURCE) -f Makefile.custom install
