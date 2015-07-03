##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# intel-dtcp makefile fragments 
##############################################################################

#
# Defines
#
ifndef  INTEL_DTCP_VERSION 
INTEL_DTCP_VERSION := 1.1
endif

INTEL_DTCP             := intel_dtcp-$(INTEL_DTCP_VERSION)#
INTEL_DTCP_SERVER_URL  := $(TOP_LIBS_URL)/intel_dtcp/$(INTEL_DTCP)
INTEL_DTCP_DIR         := $(TOP_LIBS_DIR)#
INTEL_DTCP_SOURCE      := $(INTEL_DTCP_DIR)/$(INTEL_DTCP)
INTEL_DTCP_CONFIG      := 


#
# Download  the source 
#
.PHONY: intel_dtcp-downloaded

intel_dtcp-downloaded: $(INTEL_DTCP_DIR)/.intel_dtcp_downloaded

$(INTEL_DTCP_DIR)/.intel_dtcp_downloaded:
	@echo "Downloading $(INTEL_DTCP) from $(INTEL_DTCP_SERVER_URL) ..."
	@if [ ! -d "$(INTEL_DTCP_SOURCE)" ]; then \
		cd $(INTEL_DTCP_DIR); \
		$(TOP_DOWNLOAD) $(INTEL_DTCP_SERVER_URL); \
	fi
	@echo "Downloading $(INTEL_DTCP) done"
	@touch $@

#
# Unpack the source
#
.PHONY: intel_dtcp-unpacked

intel_dtcp-unpacked: $(INTEL_DTCP_DIR)/.intel_dtcp_unpacked

$(INTEL_DTCP_DIR)/.intel_dtcp_unpacked: $(INTEL_DTCP_DIR)/.intel_dtcp_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: intel_dtcp-patched

intel_dtcp-patched: $(INTEL_DTCP_DIR)/.intel_dtcp_patched

$(INTEL_DTCP_DIR)/.intel_dtcp_patched: $(INTEL_DTCP_DIR)/.intel_dtcp_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: intel_dtcp-config

intel_dtcp-config: 

#
# Configuration
#
.PHONY: intel_dtcp-configured

intel_dtcp-configured:  intel_dtcp-config $(INTEL_DTCP_DIR)/.intel_dtcp_configured

$(INTEL_DTCP_DIR)/.intel_dtcp_configured: $(INTEL_DTCP_DIR)/.intel_dtcp_patched $(INTEL_DTCP_CONFIG) $(TOP_CURRENT_SET)
	# Configuring...
	@touch $@

#
# Compile
#
.PHONY: intel_dtcp-compile

intel_dtcp-compile: intel_dtcp-configured
	@echo "Compiling $(INTEL_DTCP_SOURCE) ..."
	make -C $(INTEL_DTCP_SOURCE) 
	@echo "Compiling $(INTEL_DTCP_SOURCE) done"

#
# Update
#
.PHONY: intel_dtcp-update

intel_dtcp-update:
	@echo "Updating $(INTEL_DTCP) ..."
	@if [ -d "$(INTEL_DTCP_SOURCE)" ]; then\
		$(TOP_UPDATE) $(INTEL_DTCP_SOURCE); \
	fi
	@echo "Updating $(INTEL_DTCP) done"

#
# Status
#
.PHONY: intel_dtcp-status

intel_dtcp-status:
	@echo "Statusing $(INTEL_DTCP) ..."
	@if [ -d "$(INTEL_DTCP_SOURCE)" ]; then\
		$(TOP_STATUS) $(INTEL_DTCP_SOURCE); \
	fi
	@echo "Statusing $(INTEL_DTCP) done"

#
# Clean
#
.PHONY: intel_dtcp-clean

intel_dtcp-clean:
	@rm -f $(INTEL_DTCP_DIR)/.intel_dtcp_configured
	@if [ -d "$(INTEL_DTCP_SOURCE)" ]; then\
		make -C $(INTEL_DTCP_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: intel_dtcp-distclean

intel_dtcp-distclean:
	@rm -f $(INTEL_DTCP_DIR)/.intel_dtcp_*

#
# Install
#
.PHONY: intel_dtcp-install

intel_dtcp-install:
