##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# libtool makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBTOOL_VERSION 
CONF_LIBTOOL_VERSION := 1.5
endif

LIBTOOL             := libtool-$(CONF_LIBTOOL_VERSION)#
LIBTOOL_SERVER_URL  := $(TOP_LIBS_URL)/libtool/$(LIBTOOL)
LIBTOOL_DIR         := $(TOP_LIBS_DIR)#
LIBTOOL_SOURCE      := $(LIBTOOL_DIR)/$(LIBTOOL)
LIBTOOL_CONFIG      := 

#
# Download  the source 
#
.PHONY: libtool-downloaded

libtool-downloaded: $(LIBTOOL_DIR)/.libtool_downloaded

$(LIBTOOL_DIR)/.libtool_downloaded:
	@echo "Downloading $(LIBTOOL) from $(LIBTOOL_SERVER_URL) ..."
	@if [ ! -d "$(LIBTOOL_SOURCE)" ]; then \
		cd $(LIBTOOL_DIR); \
		$(TOP_DOWNLOAD) $(LIBTOOL_SERVER_URL); \
	fi
	@echo "Downloading $(LIBTOOL) from $(LIBTOOL_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libtool-unpacked

libtool-unpacked: $(LIBTOOL_DIR)/.libtool_unpacked

$(LIBTOOL_DIR)/.libtool_unpacked: $(LIBTOOL_DIR)/.libtool_downloaded $(LIBTOOL_SOURCE)/$(LIBTOOL).tar.gz
	@echo "Unpacking $(LIBTOOL) ..."
	if [ -d "$(LIBTOOL_SOURCE)/$(LIBTOOL)" ]; then \
		rm -fr $(LIBTOOL_SOURCE)/$(LIBTOOL); \
	fi
	cd $(LIBTOOL_SOURCE); tar zxvf $(LIBTOOL).tar.gz
	@echo "Unpacking $(LIBTOOL) done"
	@touch $@


#
# Patch the source
#
.PHONY: libtool-patched

libtool-patched: $(LIBTOOL_DIR)/.libtool_patched

$(LIBTOOL_DIR)/.libtool_patched: $(LIBTOOL_DIR)/.libtool_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libtool-config

libtool-config: 

#
# Configuration
#
.PHONY: libtool-configured

libtool-configured:  libtool-config $(LIBTOOL_DIR)/.libtool_configured

$(LIBTOOL_DIR)/.libtool_configured: $(LIBTOOL_DIR)/.libtool_patched $(LIBTOOL_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBTOOL) ..."
	cd $(LIBTOOL_SOURCE)/$(LIBTOOL);./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)
	@echo "Configuring $(LIBTOOL) done"
	@touch $@

#
# Compile
#
.PHONY: libtool-compile

libtool-compile: $(LIBTOOL_DIR)/.libtool_compiled

$(LIBTOOL_DIR)/.libtool_compiled: $(LIBTOOL_DIR)/.libtool_configured
	@echo "Compiling $(LIBTOOL) ..."
	#make -C $(LIBTOOL_SOURCE)/$(LIBTOOL) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBTOOL_SOURCE)/$(LIBTOOL) 
	make -C $(LIBTOOL_SOURCE)/$(LIBTOOL)  install
	@echo "Compiling $(LIBTOOL) done"
	@touch $@

#
# Update
#
.PHONY: libtool-update

libtool-update:
	@echo "Updating $(LIBTOOL) ..."
	@if [ -d "$(LIBTOOL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBTOOL_SOURCE); \
	fi
	@echo "Updating $(LIBTOOL) done"

#
# Status
#
.PHONY: libtool-status

libtool-status:
	@echo "Statusing $(LIBTOOL) ..."
	@if [ -d "$(LIBTOOL_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBTOOL_SOURCE); \
	fi
	@echo "Statusing $(LIBTOOL) done"

#
# Clean
#
.PHONY: libtool-clean

libtool-clean:
	@rm -f $(LIBTOOL_DIR)/.libtool_configured
	@if [ -d "$(LIBTOOL_SOURCE)" ]; then\
		make -C $(LIBTOOL_SOURCE)/$(LIBTOOL) clean; \
	fi

#
# Dist clean
#
.PHONY: libtool-distclean

libtool-distclean:
	@rm -f $(LIBTOOL_DIR)/.libtool_*

#
# Install
#
.PHONY: libtool-install

libtool-install:
