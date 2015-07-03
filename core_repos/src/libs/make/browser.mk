##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# browser makefile fragments 
##############################################################################

#
# Defines
#
ifndef  BROWSER_VERSION 
BROWSER_VERSION := fresco
endif

BROWSER_SERVER_URL  := $(TOP_LIBS_URL)/browser/$(BROWSER_VERSION)#
BROWSER_DIR         := $(TOP_LIBS_DIR)#
BROWSER_SOURCE      := $(BROWSER_DIR)/$(BROWSER_VERSION)#
BROWSER_CONFIG      := 


#
# Download  the source 
#
.PHONY: browser-downloaded

browser-downloaded: $(BROWSER_DIR)/.browser_downloaded

$(BROWSER_DIR)/.browser_downloaded:
	@echo "Downloading $(BROWSER_VERSION) from $(BROWSER_SERVER_URL) ..."
	@if [ ! -d "$(BROWSER_SOURCE)" ]; then \
		cd $(BROWSER_DIR); \
		$(TOP_DOWNLOAD) $(BROWSER_SERVER_URL); \
	fi
	@echo "Downloading $(BROWSER_VERSION) done"
	@touch $@

#
# Unpack the source
#
.PHONY: browser-unpacked

browser-unpacked: $(BROWSER_DIR)/.browser_unpacked

$(BROWSER_DIR)/.browser_unpacked: $(BROWSER_DIR)/.browser_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: browser-patched

browser-patched: $(BROWSER_DIR)/.browser_patched

$(BROWSER_DIR)/.browser_patched: $(BROWSER_DIR)/.browser_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: browser-config

browser-config: 

#
# Configuration
#
.PHONY: browser-configured

browser-configured:  browser-config $(BROWSER_DIR)/.browser_configured

$(BROWSER_DIR)/.browser_configured: $(BROWSER_DIR)/.browser_patched $(BROWSER_CONFIG) $(TOP_CURRENT_SET)
	# Configuring
	@touch $@

#
# Compile
#
.PHONY: browser-compile

browser-compile: browser-configured
	@echo "Compiling $(BROWSER_VERSION) ..."
	make -C $(BROWSER_SOURCE) 
	@echo "Compiling $(BROWSER_VERSION) done"

#
# Update
#
.PHONY: browser-update

browser-update:
	@echo "Updating $(BROWSER_VERSION) ..."
	@if [ -d "$(BROWSER_SOURCE)" ]; then\
		$(TOP_UPDATE) $(BROWSER_SOURCE); \
	fi
	@echo "Updating $(BROWSER_VERSION) done"

#
# Status
#
.PHONY: browser-status

browser-status:
	@echo "Statusing $(BROWSER_VERSION) ..."
	@if [ -d "$(BROWSER_SOURCE)" ]; then\
		$(TOP_STATUS) $(BROWSER_SOURCE); \
	fi
	@echo "Statusing $(BROWSER_VERSION) done"

#
# Clean
#
.PHONY: browser-clean

browser-clean:
	@rm -f $(BROWSER_DIR)/.browser_configured
	@if [ -d "$(BROWSER_SOURCE)" ]; then\
		make -C $(BROWSER_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: browser-distclean

browser-distclean:
	@rm -f $(BROWSER_DIR)/.browser_*
#@rm -fr $(BROWSER_SOURCE)

#
# Install
#
.PHONY: browser-install

browser-install:
