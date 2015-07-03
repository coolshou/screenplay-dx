##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# dns makefile fragments 
##############################################################################

#
# Defines
#

DNS             := dns#
DNS_SERVER_URL  := $(TOP_LIBS_URL)/$(DNS)#b
DNS_DIR         := $(TOP_LIBS_DIR)#
DNS_SOURCE      := $(DNS_DIR)/$(DNS)
DNS_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        DNS_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: dns-downloaded

dns-downloaded: $(DNS_DIR)/.dns_downloaded

$(DNS_DIR)/.dns_downloaded:
	@echo "Downloading $(DNS) from $(DNS_SERVER_URL) ..."
	@if [ ! -d "$(DNS_SOURCE)" ]; then \
		cd $(DNS_DIR); \
		$(TOP_DOWNLOAD) $(DNS_SERVER_URL); \
	fi
	@echo "Downloading $(DNS) from $(DNS_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: dns-unpacked

dns-unpacked: $(DNS_DIR)/.dns_unpacked

$(DNS_DIR)/.dns_unpacked: $(DNS_DIR)/.dns_downloaded
	@echo "Unpacking $(DNS) ..."
	@touch $@


#
# Patch the source
#
.PHONY: dns-patched

dns-patched: $(DNS_DIR)/.dns_patched

$(DNS_DIR)/.dns_patched: $(DNS_DIR)/.dns_unpacked
	# Patching...
# Patching...
	@touch $@

#
# config
#
.PHONY: dns-config

dns-config: 

#
# Configuration
#
.PHONY: dns-configured

dns-configured:  dns-config $(DNS_DIR)/.dns_configured

$(DNS_DIR)/.dns_configured: $(DNS_DIR)/.dns_patched $(DNS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(DNS) ..."
	@echo "Configuring $(DNS) done"
	@touch $@

#
# Compile
#
.PHONY: dns-compile

dns-compile: $(DNS_DIR)/.dns_compiled

$(DNS_DIR)/.dns_compiled: $(DNS_DIR)/.dns_configured
	@echo "Compiling $(DNS) ..."
	make -C $(DNS_SOURCE)/
	@echo "Compiling $(DNS) done"
	@touch $@

#
# Update
#
.PHONY: dns-update

dns-update:
	@echo "Updating $(DNS) ..."
	@if [ -d "$(DNS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(DNS_SOURCE); \
	fi
	@echo "Updating $(DNS) done"

#
# Status
#
.PHONY: dns-status

dns-status:
	@echo "Statusing $(DNS) ..."
	@if [ -d "$(DNS_SOURCE)" ]; then\
		$(TOP_STATUS) $(DNS_SOURCE); \
	fi
	@echo "Statusing $(DNS) done"

#
# Clean
#
.PHONY: dns-clean

dns-clean:
	@rm -f $(DNS_DIR)/.dns_configured
	@if [ -d "$(DNS_SOURCE)" ]; then\
		make -C $(DNS_SOURCE)/$(DNS)/source clean; \
	fi

#
# Dist clean
#
.PHONY: dns-distclean

dns-distclean:
	@rm -f $(DNS_DIR)/.dns*

#
# Install
#
.PHONY: dns-install

dns-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(DNS_SOURCE)/dns $(TOP_INSTALL_ROOTFS_DIR)/bin
