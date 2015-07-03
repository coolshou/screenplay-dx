##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# flac makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_FLAC_VERSION 
CONF_FLAC_VERSION := 1.2.1
endif

FLAC             := flac-$(CONF_FLAC_VERSION)#
FLAC_FILE        := flac-$(CONF_FLAC_VERSION).tgz#
FLAC_SERVER_URL  := $(TOP_LIBS_URL)/flac/
FLAC_DIR         := $(TOP_LIBS_DIR)/flac/#
FLAC_SOURCE      := $(FLAC_DIR)/$(FLAC)
FLAC_SOURCE_FILE := $(FLAC_DIR)/$(FLAC_FILE)
FLAC_CONFIG      := 


#
# Download  the source 
#
.PHONY: flac-downloaded

flac-downloaded: $(TOP_LIBS_DIR)/.flac_downloaded

$(TOP_LIBS_DIR)/.flac_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: flac-unpacked

flac-unpacked: $(TOP_LIBS_DIR)/.flac_unpacked

$(TOP_LIBS_DIR)/.flac_unpacked: $(TOP_LIBS_DIR)/.flac_downloaded $(wildcard $(FLAC_SOURCE)/*.tgz)
	@echo "Unpacking $(FLAC_FILE) ..."
	if [ -d "$(FLAC_SOURCE)" ]; then \
		rm -fr $(FLAC_SOURCE);\
	fi
	cd $(FLAC_DIR); tar zxvf $(FLAC_FILE)
	@echo "Unpacking $(FLAC_FILE) done"
	@touch $@


#
# Patch the source
#
.PHONY: flac-patched

flac-patched: $(TOP_LIBS_DIR)/.flac_patched

$(TOP_LIBS_DIR)/.flac_patched: $(TOP_LIBS_DIR)/.flac_unpacked
	# Patching...
	@echo "the patch file alphanetworks_modify_file.txt is in the $(FLAC_SOURCE) ..."
	@touch $@

#
# config
#
.PHONY: flac-config

flac-config: 

#
# Configuration
#
.PHONY: flac-configured

flac-configured:  flac-config $(TOP_LIBS_DIR)/.flac_configured

$(TOP_LIBS_DIR)/.flac_configured: $(TOP_LIBS_DIR)/.flac_patched $(FLAC_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FLAC) ..."
	cd $(FLAC_SOURCE); ./configure --prefix=$(LIBS_INSTALL_PATH)  --host=$(BUILD_TARGET) --disable-ogg --disable-xmms-plugin --disable-cpplibs --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-lc -pthread"
	@echo "Configuring $(FLAC) done"
	@touch $@

#
# Compile
#
.PHONY: flac-compile

flac-compile: $(TOP_LIBS_DIR)/.flac_compiled

$(TOP_LIBS_DIR)/.flac_compiled: $(TOP_LIBS_DIR)/.flac_configured
	@echo "Compiling $(FLAC) ..."
	make -C $(FLAC_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(FLAC_SOURCE) install
	@echo "Compiling $(FLAC) done"
	@touch $@

#
# Update
#
.PHONY: flac-update

flac-update:
	@echo "Updating $(FLAC) ..."
	@if [ -d "$(FLAC_SOURCE_FILE)" ]; then\
		$(TOP_UPDATE) $(FLAC_SOURCE_FILE); \
	fi
	@echo "Updating $(FLAC) done"

#
# Status
#
.PHONY: flac-status

flac-status:
	@echo "Statusing $(FLAC) ..."
	@if [ -d "$(FLAC_SOURCE_FILE)" ]; then\
		$(TOP_STATUS) $(FLAC_SOURCE_FILE); \
	fi
	@echo "Statusing $(FLAC) done"

#
# Clean
#
.PHONY: flac-clean

flac-clean:
	@rm -f $(TOP_LIBS_DIR)/.flac_configured
	@if [ -d "$(FLAC_SOURCE)" ]; then\
		make -C $(FLAC_SOURCE)/Tremor clean; \
	fi

#
# Dist clean
#
.PHONY: flac-distclean

flac-distclean:
	@rm -f $(TOP_LIBS_DIR)/.flac_*

#
# Install
#
.PHONY: flac-install

flac-install:
