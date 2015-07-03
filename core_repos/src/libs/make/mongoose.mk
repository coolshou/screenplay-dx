##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# mongoose makefile fragments 
##############################################################################

#
# Defines
#
ifndef  MONGOOSE_VERSION 
MONGOOSE_VERSION := 3.0
endif

MONGOOSE             := mongoose-$(MONGOOSE_VERSION)#
MONGOOSE_SERVER_URL  := $(TOP_LIBS_URL)/mongoose/$(MONGOOSE)
MONGOOSE_DIR         := $(TOP_LIBS_DIR)#
MONGOOSE_SOURCE      := $(MONGOOSE_DIR)/$(MONGOOSE)
MONGOOSE_BUILD_DIR   := $(MONGOOSE_SOURCE)/$(MONGOOSE)/build
MONGOOSE_CONFIG      := 


#
# Download  the source 
#
.PHONY: mongoose-downloaded

mongoose-downloaded: $(MONGOOSE_DIR)/.mongoose_downloaded

$(MONGOOSE_DIR)/.mongoose_downloaded:
	@echo "Downloading $(MONGOOSE) from $(MONGOOSE_SERVER_URL) ..."
	@if [ ! -d "$(MONGOOSE_SOURCE)" ]; then \
		cd $(MONGOOSE_DIR); \
		$(TOP_DOWNLOAD) $(MONGOOSE_SERVER_URL); \
	fi
	@echo "Downloading $(MONGOOSE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: mongoose-unpacked

mongoose-unpacked: $(MONGOOSE_DIR)/.mongoose_unpacked

$(MONGOOSE_DIR)/.mongoose_unpacked: $(MONGOOSE_DIR)/.mongoose_downloaded $(wildcard $(MONGOOSE_SOURCE)/*.tgz)
	@echo "Unpacking $(MONGOOSE) ..."
	if [ -d "$(MONGOOSE_SOURCE)/$(MONGOOSE)" ]; then \
		rm -fr $(MONGOOSE_SOURCE)/$(MONGOOSE); \
	fi
	cd $(MONGOOSE_SOURCE);tar xvzf  $(MONGOOSE).tgz
	@echo "Unpacking $(MONGOOSE) done"
	@touch $@


#
# Patch the source
#
.PHONY: mongoose-patched

mongoose-patched: $(MONGOOSE_DIR)/.mongoose_patched

$(MONGOOSE_DIR)/.mongoose_patched: $(MONGOOSE_DIR)/.mongoose_unpacked
# Patching...
	@echo "Patching $(MONGOOSE) ..."
#	cd $(MONGOOSE_SOURCE);patch -p0 < $(MONGOOSE).patch
	@echo "Patching $(MONGOOSE) done"
	@touch $@

#
# config
#
.PHONY: mongoose-config

mongoose-config: 

#
# Configuration
#
.PHONY: mongoose-configured

mongoose-configured:  mongoose-config $(MONGOOSE_DIR)/.mongoose_configured

$(MONGOOSE_DIR)/.mongoose_configured: $(MONGOOSE_DIR)/.mongoose_patched $(MONGOOSE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(MONGOOSE) ..."
	@echo "Configuring $(MONGOOSE) done"
	@touch $@

#
# Compile
#
.PHONY: mongoose-compile

mongoose-compile: $(MONGOOSE_DIR)/.mongoose_compiled

$(MONGOOSE_DIR)/.mongoose_compiled: $(MONGOOSE_DIR)/.mongoose_configured
	@echo "Compiling $(MONGOOSE) ..."
	make -C $(MONGOOSE_SOURCE)/$(MONGOOSE) CC=$(CC)
	make -C $(MONGOOSE_SOURCE)/$(MONGOOSE) install
	@echo "Compiling $(MONGOOSE) done"
	@touch $@

#
# Update
#
.PHONY: mongoose-update

mongoose-update:
	@echo "Updating $(MONGOOSE) ..."
	@if [ -d "$(MONGOOSE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MONGOOSE_SOURCE); \
	fi
	@echo "Updating $(MONGOOSE) done"

#
# Status
#
.PHONY: mongoose-status

mongoose-status:
	@echo "Statusing $(MONGOOSE) ..."
	@if [ -d "$(MONGOOSE_SOURCE)" ]; then\
		$(TOP_STATUS) $(MONGOOSE_SOURCE); \
	fi
	@echo "Statusing $(MONGOOSE) done"

#
# Clean
#
.PHONY: mongoose-clean

mongoose-clean:
	@rm -f $(MONGOOSE_DIR)/.mongoose_configured
	@if [ -d "$(MONGOOSE_SOURCE)" ]; then\
		make -C $(MONGOOSE_SOURCE)/$(MONGOOSE) clean; \
	fi

#
# Dist clean
#
.PHONY: mongoose-distclean

mongoose-distclean:
	@rm -f $(MONGOOSE_DIR)/.mongoose_*

#
# Install
#
.PHONY: mongoose-install

mongoose-install:
	cp -f $(MONGOOSE_DIR)/mongoose $(TOP_INSTALL_ROOTFS_DIR)/bin
	chmod +x $(TOP_INSTALL_ROOTFS_DIR)/bin/mongoose

