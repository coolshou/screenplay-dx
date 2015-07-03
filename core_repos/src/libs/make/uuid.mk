##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# uuid makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_UUID_VERSION 
UUID_VERSION := 1.41.10
else
UUID_VERSION := $(CONF_UUID_VERSION)
endif

UUID             := uuid-$(UUID_VERSION)#
UUID_SERVER_URL  := $(TOP_LIBS_URL)/uuid/$(UUID)#b
UUID_DIR         := $(TOP_LIBS_DIR)#
UUID_SOURCE      := $(UUID_DIR)/$(UUID)
UUID_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        UUID_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: uuid-downloaded

uuid-downloaded: $(UUID_DIR)/.uuid_downloaded

$(UUID_DIR)/.uuid_downloaded:
	@echo "Downloading $(UUID) from $(UUID_SERVER_URL) ..."
	@if [ ! -d "$(UUID_SOURCE)" ]; then \
		cd $(UUID_DIR); \
		$(TOP_DOWNLOAD) $(UUID_SERVER_URL); \
	fi
	@echo "Downloading $(UUID) from $(UUID_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: uuid-unpacked

uuid-unpacked: $(UUID_DIR)/.uuid_unpacked

$(UUID_DIR)/.uuid_unpacked: $(UUID_DIR)/.uuid_downloaded $(UUID_SOURCE)/$(UUID).tar.gz
	@echo "Unpacking $(UUID) ..."
	if [ -d "$(UUID_SOURCE)/$(UUID)" ]; then \
		rm -fr $(UUID_SOURCE)/$(UUID); \
	fi
	cd $(UUID_SOURCE); tar xvzf  $(UUID).tar.gz
	@echo "Unpacking $(UUID) done"
	@touch $@


#
# Patch the source
#
.PHONY: uuid-patched

uuid-patched: $(UUID_DIR)/.uuid_patched

$(UUID_DIR)/.uuid_patched: $(UUID_DIR)/.uuid_unpacked
	# Patching...
# Patching...
	#cd $(UUID_SOURCE)/$(UUID); patch -p1 < ../$(UUID).patch
	@touch $@

#
# config
#
.PHONY: uuid-config

uuid-config: 

#
# Configuration
#
.PHONY: uuid-configured

uuid-configured:  uuid-config $(UUID_DIR)/.uuid_configured

$(UUID_DIR)/.uuid_configured: $(UUID_DIR)/.uuid_patched $(UUID_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(UUID) ..."
	cd $(UUID_SOURCE)/$(UUID);export CPPFLAGS=-fPIC; export CFLAGS=-fPIC ; ./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET)
	@echo "Configuring $(UUID) done"
	@touch $@

#
# Compile
#
.PHONY: uuid-compile

uuid-compile: $(UUID_DIR)/.uuid_compiled

$(UUID_DIR)/.uuid_compiled: $(UUID_DIR)/.uuid_configured
	@echo "Compiling $(UUID) ..."
	export CPPFLAGS=-fPIC; export CFLAGS=-fPIC ; make -C $(UUID_SOURCE)/$(UUID)/ 
	make -C $(UUID_SOURCE)/$(UUID)/ install-libs
	@echo "Compiling $(UUID) done"
	@touch $@

#
# Update
#
.PHONY: uuid-update

uuid-update:
	@echo "Updating $(UUID) ..."
	@if [ -d "$(UUID_SOURCE)" ]; then\
		$(TOP_UPDATE) $(UUID_SOURCE); \
	fi
	@echo "Updating $(UUID) done"

#
# Status
#
.PHONY: uuid-status

uuid-status:
	@echo "Statusing $(UUID) ..."
	@if [ -d "$(UUID_SOURCE)" ]; then\
		$(TOP_STATUS) $(UUID_SOURCE); \
	fi
	@echo "Statusing $(UUID) done"

#
# Clean
#
.PHONY: uuid-clean

uuid-clean:
	@rm -f $(UUID_DIR)/.uuid_configured
	@if [ -d "$(UUID_SOURCE)" ]; then\
		make -C $(UUID_SOURCE)/$(UUID) clean; \
	fi

#
# Dist clean
#
.PHONY: uuid-distclean

uuid-distclean:
	@rm -f $(UUID_DIR)/.uuid_*

#
# Install
#
.PHONY: uuid-install

uuid-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
