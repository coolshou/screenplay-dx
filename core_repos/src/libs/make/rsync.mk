##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# rsync makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_RSYNC_VERSION 
RSYNC_VERSION := 3.0.6
else
RSYNC_VERSION := $(CONF_RSYNC_VERSION)
endif

RSYNC             := rsync-$(RSYNC_VERSION)#
RSYNC_SERVER_URL  := $(TOP_LIBS_URL)/rsync/$(RSYNC)#b
RSYNC_DIR         := $(TOP_LIBS_DIR)#
RSYNC_SOURCE      := $(RSYNC_DIR)/$(RSYNC)
RSYNC_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        RSYNC_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: rsync-downloaded

rsync-downloaded: $(RSYNC_DIR)/.rsync_downloaded

$(RSYNC_DIR)/.rsync_downloaded:
	@echo "Downloading $(RSYNC) from $(RSYNC_SERVER_URL) ..."
	@if [ ! -d "$(RSYNC_SOURCE)" ]; then \
		cd $(RSYNC_DIR); \
		$(TOP_DOWNLOAD) $(RSYNC_SERVER_URL); \
	fi
	@echo "Downloading $(RSYNC) from $(RSYNC_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: rsync-unpacked

rsync-unpacked: $(RSYNC_DIR)/.rsync_unpacked

$(RSYNC_DIR)/.rsync_unpacked: $(RSYNC_DIR)/.rsync_downloaded $(RSYNC_SOURCE)/$(RSYNC).tar.gz
	@echo "Unpacking $(RSYNC) ..."
	if [ -d "$(RSYNC_SOURCE)/$(RSYNC)" ]; then \
		rm -fr $(RSYNC_SOURCE)/$(RSYNC); \
	fi
	cd $(RSYNC_SOURCE); tar xvzf  $(RSYNC).tar.gz
	@echo "Unpacking $(RSYNC) done"
	@touch $@


#
# Patch the source
#
.PHONY: rsync-patched

rsync-patched: $(RSYNC_DIR)/.rsync_patched

$(RSYNC_DIR)/.rsync_patched: $(RSYNC_DIR)/.rsync_unpacked
	# Patching...
# Patching...
	cd $(RSYNC_SOURCE)/$(RSYNC); patch -p1 < ../$(RSYNC).patch
	@touch $@

#
# config
#
.PHONY: rsync-config

rsync-config: 

#
# Configuration
#
.PHONY: rsync-configured

rsync-configured:  rsync-config $(RSYNC_DIR)/.rsync_configured

$(RSYNC_DIR)/.rsync_configured: $(RSYNC_DIR)/.rsync_patched $(RSYNC_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(RSYNC) ..."
	#cd $(RSYNC_SOURCE)/$(RSYNC);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) --with-bdb=/home/peggy_huang/db-4.2.52/build_unix/db_install/include --without-ssl-dir $(RSYNC_SHARED_FLAGS)
	cd $(RSYNC_SOURCE)/$(RSYNC);./configure --host=$(BUILD_TARGET)
	@echo "Configuring $(RSYNC) done"
	@touch $@

#
# Compile
#
.PHONY: rsync-compile

rsync-compile: $(RSYNC_DIR)/.rsync_compiled

$(RSYNC_DIR)/.rsync_compiled: $(RSYNC_DIR)/.rsync_configured
	@echo "Compiling $(RSYNC) ..."
	make -C $(RSYNC_SOURCE)/$(RSYNC)/
	@echo "Compiling $(RSYNC) done"
	@touch $@

#
# Update
#
.PHONY: rsync-update

rsync-update:
	@echo "Updating $(RSYNC) ..."
	@if [ -d "$(RSYNC_SOURCE)" ]; then\
		$(TOP_UPDATE) $(RSYNC_SOURCE); \
	fi
	@echo "Updating $(RSYNC) done"

#
# Status
#
.PHONY: rsync-status

rsync-status:
	@echo "Statusing $(RSYNC) ..."
	@if [ -d "$(RSYNC_SOURCE)" ]; then\
		$(TOP_STATUS) $(RSYNC_SOURCE); \
	fi
	@echo "Statusing $(RSYNC) done"

#
# Clean
#
.PHONY: rsync-clean

rsync-clean:
	@rm -f $(RSYNC_DIR)/.rsync_configured
	@if [ -d "$(RSYNC_SOURCE)" ]; then\
		make -C $(RSYNC_SOURCE)/$(RSYNC)/source clean; \
	fi

#
# Dist clean
#
.PHONY: rsync-distclean

rsync-distclean:
	@rm -f $(RSYNC_DIR)/.rsync_*

#
# Install
#
.PHONY: rsync-install

rsync-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(RSYNC_SOURCE)/$(RSYNC)/rsync $(TOP_INSTALL_ROOTFS_DIR)/sbin
