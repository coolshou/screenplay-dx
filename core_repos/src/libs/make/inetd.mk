##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# inetd makefile fragments 
##############################################################################

#
# Defines
#
ifndef  INETD_VERSION 
INETD_VERSION := 0.01
endif

INETD             := inetd-$(INETD_VERSION)#
INETD_SERVER_URL  := $(TOP_LIBS_URL)/inetd/$(INETD)
INETD_DIR         := $(TOP_LIBS_DIR)#
INETD_SOURCE      := $(INETD_DIR)/$(INETD)
INETD_CONFIG      := 


#
# Download  the source 
#
.PHONY: inetd-downloaded

inetd-downloaded: $(INETD_DIR)/.inetd_downloaded

$(INETD_DIR)/.inetd_downloaded:
	@echo "Downloading $(INETD) from $(INETD_SERVER_URL) ..."
	@if [ ! -d "$(INETD_SOURCE)" ]; then \
		cd $(INETD_DIR); \
		$(TOP_DOWNLOAD) $(INETD_SERVER_URL); \
	fi
	@echo "Downloading $(INETD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: inetd-unpacked

inetd-unpacked: $(INETD_DIR)/.inetd_unpacked

$(INETD_DIR)/.inetd_unpacked: $(INETD_DIR)/.inetd_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: inetd-patched

inetd-patched: $(INETD_DIR)/.inetd_patched

$(INETD_DIR)/.inetd_patched: $(INETD_DIR)/.inetd_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: inetd-config

inetd-config: 

#
# Configuration
#
.PHONY: inetd-configured

inetd-configured:  inetd-config $(INETD_DIR)/.inetd_configured

$(INETD_DIR)/.inetd_configured: $(INETD_DIR)/.inetd_patched $(INETD_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: inetd-compile

inetd-compile: inetd-configured
	@echo "Compiling $(INETD) ..." 
	make -C $(INETD_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@echo "Compiling $(INETD) done"

#
# Update
#
.PHONY: inetd-update

inetd-update:
	@echo "Updating $(INETD) ..."
	@if [ -d "$(INETD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(INETD_SOURCE); \
	fi
	@echo "Updating $(INETD) done"

#
# Status
#
.PHONY: inetd-status

inetd-status:
	@echo "Statusing $(INETD) ..."
	@if [ -d "$(INETD_SOURCE)" ]; then\
		$(TOP_STATUS) $(INETD_SOURCE); \
	fi
	@echo "Statusing $(INETD) done"

#
# Clean
#
.PHONY: inetd-clean

inetd-clean:
	@rm -f $(INETD_DIR)/.inetd_configured
	@if [ -d "$(INETD_SOURCE)" ]; then\
		make -C $(INETD_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: inetd-distclean

inetd-distclean:
	@rm -f $(INETD_DIR)/.inetd_*

#
# Install
#
.PHONY: inetd-install

inetd-install:
