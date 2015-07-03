##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# mcx makefile fragments 
##############################################################################

#
# Defines
#
MCX_SERVER_URL  := $(TOP_MCX_URL)#
MCX_DIR         := $(TOP_LIBS_DIR)#
MCX_SOURCE      := $(MCX_DIR)/mcx
MCX_CONFIG      := 


#
# Download  the source 
#
.PHONY: mcx-downloaded

mcx-downloaded: $(MCX_DIR)/.mcx_downloaded

$(MCX_DIR)/.mcx_downloaded:
	@echo "Downloading $(MCX_SOURCE) from $(MCX_SERVER_URL) ..."
	@if [ ! -d "$(MCX_SOURCE)" ]; then \
		cd $(MCX_DIR); \
		$(TOP_DOWNLOAD) $(MCX_SERVER_URL) $(MCX_SOURCE); \
	fi
	@echo "Downloading $(MCX_SOURCE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: mcx-unpacked

mcx-unpacked: $(MCX_DIR)/.mcx_unpacked

$(MCX_DIR)/.mcx_unpacked: $(MCX_DIR)/.mcx_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: mcx-patched

mcx-patched: $(MCX_DIR)/.mcx_patched

$(MCX_DIR)/.mcx_patched: $(MCX_DIR)/.mcx_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: mcx-config

mcx-config: 

#
# Configuration
#
.PHONY: mcx-configured

mcx-configured:  mcx-config $(MCX_DIR)/.mcx_configured

$(MCX_DIR)/.mcx_configured: $(MCX_DIR)/.mcx_patched $(MCX_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: mcx-compile

mcx-compile: mcx-configured
	@echo "Compiling $(MCX_SOURCE) ..."
	make -C $(MCX_SOURCE) 
	@echo "Compiling $(MCX_SOURCE) done"

#
# Update
#
.PHONY: mcx-update

mcx-update:
	@echo "Updating mcx  ..."
	@if [ -d "$(MCX_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MCX_SOURCE); \
	fi
	@echo "Updating mcx  done"

#
# Status
#
.PHONY: mcx-status

mcx-status:
	@echo "Statusing mcx ..."
	@if [ -d "$(MCX_SOURCE)" ]; then\
		$(TOP_STATUS) $(MCX_SOURCE); \
	fi
	@echo "Statusing mcx done"

#
# Clean
#
.PHONY: mcx-clean

mcx-clean:
	@rm -f $(MCX_DIR)/.mcx_configured
	@if [ -d "$(MCX_SOURCE)" ]; then\
		make -C $(MCX_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: mcx-distclean

mcx-distclean:
	@rm -f $(MCX_DIR)/.mcx*

#
# Install
#
.PHONY: mcx-install

mcx-install:
