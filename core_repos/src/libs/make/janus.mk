##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# janus makefile fragments 
##############################################################################

#
# Defines
#
JANUS_SERVER_URL  := $(TOP_LIBS_URL)/janus
JANUS_DIR         := $(TOP_LIBS_DIR)#
JANUS_SOURCE      := $(JANUS_DIR)/janus
JANUS_CONFIG      := 


#
# Download  the source 
#
.PHONY: janus-downloaded

janus-downloaded: $(JANUS_DIR)/.janus_downloaded

$(JANUS_DIR)/.janus_downloaded:
	@echo "Downloading $(JANUS_SOURCE) from $(JANUS_SERVER_URL) ..."
	@if [ ! -d "$(JANUS_SOURCE)" ]; then \
		cd $(JANUS_DIR); \
		$(TOP_DOWNLOAD) $(JANUS_SERVER_URL); \
	fi
	@echo "Downloading $(JANUS_SOURCE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: janus-unpacked

janus-unpacked: $(JANUS_DIR)/.janus_unpacked

$(JANUS_DIR)/.janus_unpacked: $(JANUS_DIR)/.janus_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: janus-patched

janus-patched: $(JANUS_DIR)/.janus_patched

$(JANUS_DIR)/.janus_patched: $(JANUS_DIR)/.janus_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: janus-config

janus-config: 

#
# Configuration
#
.PHONY: janus-configured

janus-configured:  janus-config $(JANUS_DIR)/.janus_configured

$(JANUS_DIR)/.janus_configured: $(JANUS_DIR)/.janus_patched $(JANUS_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: janus-compile

janus-compile: janus-configured
	@echo "Compiling $(JANUS_SOURCE) ..."
	make -C $(JANUS_SOURCE) 
	@echo "Compiling $(JANUS_SOURCE) done"

#
# Update
#
.PHONY: janus-update

janus-update:
	@echo "Updating JANUS ..."
	@if [ -d "$(JANUS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(JANUS_SOURCE); \
	fi
	@echo "Updating JANUS done" 

#
# Status
#
.PHONY: janus-status

janus-status:
	@echo "Statusing JANUS ..."
	@if [ -d "$(JANUS_SOURCE)" ]; then\
		$(TOP_STATUS) $(JANUS_SOURCE); \
	fi
	@echo "Statusing JANUS done"

#
# Clean
#
.PHONY: janus-clean

janus-clean:
	@rm -f $(JANUS_DIR)/.janus_configured
	@if [ -d "$(JANUS_SOURCE)" ]; then\
		make -C $(JANUS_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: janus-distclean

janus-distclean:
	@rm -f $(JANUS_DIR)/.janus_*

#
# Install
#
.PHONY: janus-install

janus-install:
