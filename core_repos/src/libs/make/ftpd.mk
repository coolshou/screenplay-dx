##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# ftpd makefile fragments 
##############################################################################

#
# Defines
#
ifndef  FTPD_VERSION 
FTPD_VERSION := 0.18-pre1
endif

FTPD             := linux-ftpd-$(FTPD_VERSION)#
FTPD_SERVER_URL  := $(TOP_LIBS_URL)/ftpd/$(FTPD)
FTPD_DIR         := $(TOP_LIBS_DIR)#
FTPD_SOURCE      := $(FTPD_DIR)/$(FTPD)
FTPD_CONFIG      := 


#
# Download  the source 
#
.PHONY: ftpd-downloaded

ftpd-downloaded: $(FTPD_DIR)/.ftpd_downloaded

$(FTPD_DIR)/.ftpd_downloaded:
	@echo "Downloading $(FTPD) from $(FTPD_SERVER_URL) ..."
	@if [ ! -d "$(FTPD_SOURCE)" ]; then \
		cd $(FTPD_DIR); \
		$(TOP_DOWNLOAD) $(FTPD_SERVER_URL); \
	fi
	@echo "Downloading $(FTPD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: ftpd-unpacked

ftpd-unpacked: $(FTPD_DIR)/.ftpd_unpacked

$(FTPD_DIR)/.ftpd_unpacked: $(FTPD_DIR)/.ftpd_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: ftpd-patched

ftpd-patched: $(FTPD_DIR)/.ftpd_patched

$(FTPD_DIR)/.ftpd_patched: $(FTPD_DIR)/.ftpd_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: ftpd-config

ftpd-config: 

#
# Configuration
#
.PHONY: ftpd-configured

ftpd-configured:  ftpd-config $(FTPD_DIR)/.ftpd_configured

$(FTPD_DIR)/.ftpd_configured: $(FTPD_DIR)/.ftpd_patched $(FTPD_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: ftpd-compile

ftpd-compile: ftpd-configured
	@echo "Compiling $(FTPD) ..."
	make -C $(FTPD_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@echo "Compiling $(FTPD) done"

#
# Update
#
.PHONY: ftpd-update

ftpd-update:
	@echo "Updating $(FTPD) ..."
	@if [ -d "$(FTPD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FTPD_SOURCE); \
	fi
	@echo "Updating $(FTPD) done"

#
# Status
#
.PHONY: ftpd-status

ftpd-status:
	@echo "Statusing $(FTPD) ..."
	@if [ -d "$(FTPD_SOURCE)" ]; then\
		$(TOP_STATUS) $(FTPD_SOURCE); \
	fi
	@echo "Statusing $(FTPD) done"

#
# Clean
#
.PHONY: ftpd-clean

ftpd-clean:
	@rm -f $(FTPD_DIR)/.ftpd_configured
	@if [ -d "$(FTPD_SOURCE)" ]; then\
		make -C $(FTPD_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: ftpd-distclean

ftpd-distclean:
	@rm -f $(FTPD_DIR)/.ftpd_*

#
# Install
#
.PHONY: ftpd-install

ftpd-install:
