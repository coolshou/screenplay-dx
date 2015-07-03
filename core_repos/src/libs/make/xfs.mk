##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# xfs makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_XFS_VERSION 
XFS_VERSION := 3.1.1-1
else
XFS_VERSION := $(CONF_XFS_VERSION)
endif

XFS             := xfs-$(XFS_VERSION)#
XFS_SERVER_URL  := $(TOP_LIBS_URL)/xfs/$(XFS)#b
XFS_DIR         := $(TOP_LIBS_DIR)#
XFS_SOURCE      := $(XFS_DIR)/$(XFS)
XFS_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        XFS_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: xfs-downloaded

xfs-downloaded: $(XFS_DIR)/.xfs_downloaded

$(XFS_DIR)/.xfs_downloaded:
	@echo "Downloading $(XFS) from $(XFS_SERVER_URL) ..."
	@if [ ! -d "$(XFS_SOURCE)" ]; then \
		cd $(XFS_DIR); \
		$(TOP_DOWNLOAD) $(XFS_SERVER_URL); \
	fi
	@echo "Downloading $(XFS) from $(XFS_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: xfs-unpacked

xfs-unpacked: $(XFS_DIR)/.xfs_unpacked

$(XFS_DIR)/.xfs_unpacked: $(XFS_DIR)/.xfs_downloaded $(XFS_SOURCE)/$(XFS).tar.gz
	@echo "Unpacking $(XFS) ..."
	if [ -d "$(XFS_SOURCE)/$(XFS)" ]; then \
		rm -fr $(XFS_SOURCE)/$(XFS); \
	fi
	cd $(XFS_SOURCE); tar xvzf  $(XFS).tar.gz
	@echo "Unpacking $(XFS) done"
	@touch $@


#
# Patch the source
#
.PHONY: xfs-patched

xfs-patched: $(XFS_DIR)/.xfs_patched

$(XFS_DIR)/.xfs_patched: $(XFS_DIR)/.xfs_unpacked
	# Patching...
# Patching...
	cd $(XFS_SOURCE)/$(XFS); patch -p1 < ../$(XFS).patch
	@touch $@

#
# config
#
.PHONY: xfs-config

xfs-config: 

#
# Configuration
#
.PHONY: xfs-configured

xfs-configured:  xfs-config $(XFS_DIR)/.xfs_configured

$(XFS_DIR)/.xfs_configured: $(XFS_DIR)/.xfs_patched $(XFS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(XFS) ..."
	#cd $(XFS_SOURCE)/$(XFS);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET)
	@echo "Configuring $(XFS) done"
	@touch $@

#
# Compile
#
.PHONY: xfs-compile

xfs-compile: $(XFS_DIR)/.xfs_compiled

$(XFS_DIR)/.xfs_compiled: $(XFS_DIR)/.xfs_configured
	@echo "Compiling $(XFS) ..."
	export LOCAL_CONFIGURE_OPTIONS='--host=$(BUILD_TARGET) --target=$(BUILD_TARGET) CC=$(CC) CFLAGS=-I$(TOP_LIBS_DIR)/uuid-$(CONF_UUID_VERSION)/uuid-$(CONF_UUID_VERSION)/lib/ LDFLAGS=-L$(TOP_LIBS_DIR)/uuid-$(CONF_UUID_VERSION)/uuid-$(CONF_UUID_VERSION)/lib/ LIBUUID_CFLAGS=-luuid';make -C $(XFS_SOURCE)/$(XFS)/
	@echo "Compiling $(XFS) done"
	@touch $@

#
# Update
#
.PHONY: xfs-update

xfs-update:
	@echo "Updating $(XFS) ..."
	@if [ -d "$(XFS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(XFS_SOURCE); \
	fi
	@echo "Updating $(XFS) done"

#
# Status
#
.PHONY: xfs-status

xfs-status:
	@echo "Statusing $(XFS) ..."
	@if [ -d "$(XFS_SOURCE)" ]; then\
		$(TOP_STATUS) $(XFS_SOURCE); \
	fi
	@echo "Statusing $(XFS) done"

#
# Clean
#
.PHONY: xfs-clean

xfs-clean:
	@rm -f $(XFS_DIR)/.xfs_configured
	@if [ -d "$(XFS_SOURCE)" ]; then\
		make -C $(XFS_SOURCE)/$(XFS)/source clean; \
	fi

#
# Dist clean
#
.PHONY: xfs-distclean

xfs-distclean:
	@rm -f $(XFS_DIR)/.xfs_*

#
# Install
#
.PHONY: xfs-install

xfs-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(XFS_SOURCE)/$(XFS)/mkfs/mkfs.xfs $(TOP_INSTALL_ROOTFS_DIR)/sbin
	cp -f $(XFS_SOURCE)/$(XFS)/repair/xfs_repair $(TOP_INSTALL_ROOTFS_DIR)/sbin


