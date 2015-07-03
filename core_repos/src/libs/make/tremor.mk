##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# tremor makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_TREMOR_VERSION 
CONF_TREMOR_VERSION := 1.0
endif

TREMOR             := tremor-$(CONF_TREMOR_VERSION)#
TREMOR_SERVER_URL  := $(TOP_LIBS_URL)/tremor/$(TREMOR)
TREMOR_DIR         := $(TOP_LIBS_DIR)#
TREMOR_SOURCE      := $(TREMOR_DIR)/$(TREMOR)
TREMOR_CONFIG      := 


#
# Download  the source 
#
.PHONY: tremor-downloaded

tremor-downloaded: $(TREMOR_DIR)/.tremor_downloaded

$(TREMOR_DIR)/.tremor_downloaded:
	@echo "Downloading $(TREMOR) from $(TREMOR_SERVER_URL) ..."
	@if [ ! -d "$(TREMOR_SOURCE)" ]; then \
		cd $(TREMOR_DIR); \
		$(TOP_DOWNLOAD) $(TREMOR_SERVER_URL); \
	fi
	@echo "Downloading $(TREMOR) done"
	@touch $@

#
# Unpack the source
#
.PHONY: tremor-unpacked

tremor-unpacked: $(TREMOR_DIR)/.tremor_unpacked

$(TREMOR_DIR)/.tremor_unpacked: $(TREMOR_DIR)/.tremor_downloaded $(wildcard $(TREMOR_SOURCE)/*.tgz)
	@echo "Unpacking $(TREMOR) ..."
	if [ -d "$(TREMOR_SOURCE)/$(TREMOR)" ]; then \
		rm -fr $(TREMOR_SOURCE)/$(TREMOR);\
	fi
	cd $(TREMOR_SOURCE); tar zxvf $(TREMOR).tgz
	@echo "Unpacking $(TREMOR) done"
	@touch $@


#
# Patch the source
#
.PHONY: tremor-patched

tremor-patched: $(TREMOR_DIR)/.tremor_patched

$(TREMOR_DIR)/.tremor_patched: $(TREMOR_DIR)/.tremor_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: tremor-config

tremor-config: 

#
# Configuration
#
.PHONY: tremor-configured

tremor-configured:  tremor-config $(TREMOR_DIR)/.tremor_configured

$(TREMOR_DIR)/.tremor_configured: $(TREMOR_DIR)/.tremor_patched $(TREMOR_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(TREMOR) ..."
	cd $(TREMOR_SOURCE)/Tremor; ./autogen.sh;./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-lc -pthread"
	@echo "Configuring $(TREMOR) done"
	@touch $@

#
# Compile
#
.PHONY: tremor-compile

tremor-compile: $(TREMOR_DIR)/.tremor_compiled

$(TREMOR_DIR)/.tremor_compiled: $(TREMOR_DIR)/.tremor_configured
	@echo "Compiling $(TREMOR) ..."
	make -C $(TREMOR_SOURCE)/Tremor CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(TREMOR_SOURCE)/Tremor install
	@echo "Compiling $(TREMOR) done"
	@touch $@

#
# Update
#
.PHONY: tremor-update

tremor-update:
	@echo "Updating $(TREMOR) ..."
	@if [ -d "$(TREMOR_SOURCE)" ]; then\
		$(TOP_UPDATE) $(TREMOR_SOURCE); \
	fi
	@echo "Updating $(TREMOR) done"

#
# Status
#
.PHONY: tremor-status

tremor-status:
	@echo "Statusing $(TREMOR) ..."
	@if [ -d "$(TREMOR_SOURCE)" ]; then\
		$(TOP_STATUS) $(TREMOR_SOURCE); \
	fi
	@echo "Statusing $(TREMOR) done"

#
# Clean
#
.PHONY: tremor-clean

tremor-clean:
	@rm -f $(TREMOR_DIR)/.tremor_configured
	@if [ -d "$(TREMOR_SOURCE)" ]; then\
		make -C $(TREMOR_SOURCE)/Tremor clean; \
	fi

#
# Dist clean
#
.PHONY: tremor-distclean

tremor-distclean:
	@rm -f $(TREMOR_DIR)/.tremor_*

#
# Install
#
.PHONY: tremor-install

tremor-install:
