##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# dhcpcd makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_DHCPCD_VERSION 
CONF_DHCPCD_VERSION := 1.3.22-pl1
endif

DHCPCD             := dhcpcd-$(CONF_DHCPCD_VERSION)#
DHCPCD_SERVER_URL  := $(TOP_LIBS_URL)/dhcpcd/$(DHCPCD)
DHCPCD_DIR         := $(TOP_LIBS_DIR)#
DHCPCD_SOURCE      := $(DHCPCD_DIR)/$(DHCPCD)
DHCPCD_CONFIG      := 


#
# Download  the source 
#
.PHONY: dhcpcd-downloaded

dhcpcd-downloaded: $(DHCPCD_DIR)/.dhcpcd_downloaded

$(DHCPCD_DIR)/.dhcpcd_downloaded:
	@echo "Downloading $(DHCPCD) from $(DHCPCD_SERVER_URL) ..."
	@if [ ! -d "$(DHCPCD_SOURCE)" ]; then \
		cd $(DHCPCD_DIR); \
		$(TOP_DOWNLOAD) $(DHCPCD_SERVER_URL); \
	fi
	@echo "Downloading $(DHCPCD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: dhcpcd-unpacked

dhcpcd-unpacked: $(DHCPCD_DIR)/.dhcpcd_unpacked

$(DHCPCD_DIR)/.dhcpcd_unpacked: $(DHCPCD_DIR)/.dhcpcd_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: dhcpcd-patched

dhcpcd-patched: $(DHCPCD_DIR)/.dhcpcd_patched

$(DHCPCD_DIR)/.dhcpcd_patched: $(DHCPCD_DIR)/.dhcpcd_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: dhcpcd-config

dhcpcd-config: 

#
# Configuration
#
.PHONY: dhcpcd-configured

dhcpcd-configured:  dhcpcd-config $(DHCPCD_DIR)/.dhcpcd_configured

$(DHCPCD_DIR)/.dhcpcd_configured: $(DHCPCD_DIR)/.dhcpcd_patched $(DHCPCD_CONFIG) $(TOP_CURRENT_SET)
	# Configuring...
	@touch $@

#
# Compile
#
.PHONY: dhcpcd-compile

dhcpcd-compile: dhcpcd-configured $(DHCPCD_DIR)/.dhcpcd_compiled

$(DHCPCD_DIR)/.dhcpcd_compiled:
	@echo "Compiling $(DHCPCD) ..."
	make -C $(DHCPCD_SOURCE) -f Makefile.custom 
	@echo "Compiling $(DHCPCD) done"
	@touch $@

#
# Update
#
.PHONY: dhcpcd-update

dhcpcd-update:
	@echo "Updating $(DHCPCD) ..."
	@if [ -d "$(DHCPCD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(DHCPCD_SOURCE); \
	fi
	@echo "Updating $(DHCPCD) done"

#
# Status
#
.PHONY: dhcpcd-status

dhcpcd-status:
	@echo "Statusing $(DHCPCD) ..."
	@if [ -d "$(DHCPCD_SOURCE)" ]; then\
		$(TOP_STATUS) $(DHCPCD_SOURCE); \
	fi
	@echo "Statusing $(DHCPCD) done"

#
# Clean
#
.PHONY: dhcpcd-clean

dhcpcd-clean:
	@rm -f $(DHCPCD_DIR)/.dhcpcd_configured
	@if [ -d "$(DHCPCD_SOURCE)" ]; then\
		make -C $(DHCPCD_SOURCE) -f Makefile.custom clean; \
	fi

#
# Dist clean
#
.PHONY: dhcpcd-distclean

dhcpcd-distclean:
	@rm -f $(DHCPCD_DIR)/.dhcpcd_*

#
# Install
#
.PHONY: dhcpcd-install

dhcpcd-install:
	make -C $(DHCPCD_SOURCE) -f Makefile.custom install
