##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# cardea makefile fragments 
##############################################################################

#
# Defines
#
CARDEA_SERVER_URL  := $(TOP_LIBS_URL)/cardea#
CARDEA_DIR         := $(TOP_LIBS_DIR)#
CARDEA_SOURCE      := $(CARDEA_DIR)/cardea
CARDEA_CONFIG      := 


#
# Download  the source 
#
.PHONY: cardea-downloaded

cardea-downloaded: $(CARDEA_DIR)/.cardea_downloaded

$(CARDEA_DIR)/.cardea_downloaded:
	@echo "Downloading cardea from $(CARDEA_SERVER_URL) ..."
	@if [ ! -d "$(CARDEA_SOURCE)" ]; then \
		cd $(CARDEA_DIR); \
		$(TOP_DOWNLOAD) $(CARDEA_SERVER_URL); \
	fi
	@echo "Downloading cardea done"
	@touch $@

#
# Unpack the source
#
.PHONY: cardea-unpacked

cardea-unpacked: $(CARDEA_DIR)/.cardea_unpacked

$(CARDEA_DIR)/.cardea_unpacked: $(CARDEA_DIR)/.cardea_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: cardea-patched

cardea-patched: $(CARDEA_DIR)/.cardea_patched

$(CARDEA_DIR)/.cardea_patched: $(CARDEA_DIR)/.cardea_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: cardea-config

cardea-config: 

#
# Configuration
#
.PHONY: cardea-configured

cardea-configured:  cardea-config $(CARDEA_DIR)/.cardea_configured

$(CARDEA_DIR)/.cardea_configured: $(CARDEA_DIR)/.cardea_patched $(CARDEA_CONFIG) $(TOP_CURRENT_SET)
	# Configuring...
	@touch $@

#
# Compile
#
.PHONY: cardea-compile

cardea-compile: cardea-configured
	@echo "Compiling cardea ..."
	make -C $(CARDEA_SOURCE) 
	@echo "Compiling cardea done"

#
# Update
#
.PHONY: cardea-update

cardea-update:
	@echo "Updating cardea ..."
	@if [ -d "$(CARDEA_SOURCE)" ]; then\
		$(TOP_UPDATE) $(CARDEA_SOURCE); \
	fi
	@echo "Updating cardea done"

#
# Status
#
.PHONY: cardea-status

cardea-status:
	@echo "Statusing cardea ..."
	@if [ -d "$(CARDEA_SOURCE)" ]; then\
		$(TOP_STATUS) $(CARDEA_SOURCE); \
	fi
	@echo "Statusing cardea done"

#
# Clean
#
.PHONY: cardea-clean

cardea-clean:
	@rm -f $(CARDEA_DIR)/.cardea_configured
	@if [ -d "$(CARDEA_SOURCE)" ]; then\
		make -C $(CARDEA_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: cardea-distclean

cardea-distclean:
	@rm -f $(CARDEA_DIR)/.cardea_*
#@rm -fr $(CARDEA_SOURCE)

#
# Install
#
.PHONY: cardea-install

cardea-install:
