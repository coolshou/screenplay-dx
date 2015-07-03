##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# mt-daapd makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_MT_DAAPD_VERSION 
CONF_MT_DAAPD_VERSION := 0.2.4.2
endif

MT_DAAPD             := mt-daapd-$(CONF_MT_DAAPD_VERSION)#
MT_DAAPD_SERVER_URL  := $(TOP_LIBS_URL)/mt-daapd/$(MT_DAAPD)#
MT_DAAPD_DIR         := $(TOP_LIBS_DIR)#
MT_DAAPD_SOURCE      := $(MT_DAAPD_DIR)/$(MT_DAAPD)#
MT_DAAPD_CONFIG      := 

#
# Download  the source 
#
.PHONY: mt-daapd-downloaded

mt-daapd-downloaded: $(MT_DAAPD_DIR)/.mt-daapd_downloaded

$(MT_DAAPD_DIR)/.mt-daapd_downloaded:
	@echo "Downloading $(MT_DAAPD) from $(MT_DAAPD_SERVER_URL) ..."
	@if [ ! -d "$(MT_DAAPD_SOURCE)" ]; then \
		cd $(MT_DAAPD_DIR); \
		$(TOP_DOWNLOAD) $(MT_DAAPD_SERVER_URL); \
	fi
	@echo "Downloading $(MT_DAAPD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: mt-daapd-unpacked

mt-daapd-unpacked: $(MT_DAAPD_DIR)/.mt-daapd_unpacked

$(MT_DAAPD_DIR)/.mt-daapd_unpacked: $(MT_DAAPD_DIR)/.mt-daapd_downloaded $(wildcard $(MT_DAAPD_SOURCE)/*.tar.gz)
	@echo "Unpacking $(MT_DAAPD) ..."
	if [ -d "$(MT_DAAPD_SOURCE)/$(MT_DAAPD)" ]; then \
		rm -fr $(MT_DAAPD_SOURCE)/$(MT_DAAPD); \
	fi
	(cd $(MT_DAAPD_SOURCE); tar xvzf $(MT_DAAPD).tar.gz)
	@echo "Unpacking $(MT_DAAPD) done"
	@touch $@


#
# Patch the source
#
.PHONY: mt-daapd-patched

mt-daapd-patched: $(MT_DAAPD_DIR)/.mt-daapd_patched

$(MT_DAAPD_DIR)/.mt-daapd_patched: $(MT_DAAPD_DIR)/.mt-daapd_unpacked
	@echo "Patching $(MT_DAAPD) ..."
	cd $(MT_DAAPD_SOURCE);patch -p0 <$(MT_DAAPD).patch
	@echo "Patching $(MT_DAAPD) done"
	@touch $@

#
# config
#
.PHONY: mt-daapd-config

mt-daapd-config: 

#
# Configuration
#
.PHONY: mt-daapd-configured

mt-daapd-configured:  mt-daapd-config $(MT_DAAPD_DIR)/.mt-daapd_configured

$(MT_DAAPD_DIR)/.mt-daapd_configured: $(MT_DAAPD_DIR)/.mt-daapd_patched $(MT_DAAPD_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(MT_DAAPD) ..."
	cd $(MT_DAAPD_SOURCE)/$(MT_DAAPD); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --with-gdbm-includes=$(LIBS_INSTALL_PATH)/include --with-gdbm-libs=$(LIBS_INSTALL_PATH)/lib --with-id3tag=$(LIBS_INSTALL_PATH)/lib CC=$(CC)
	@echo "Configuring $(MT_DAAPD) done"
	@touch $@

#
# Compile
#
.PHONY: mt-daapd-compile

mt-daapd-compile: $(MT_DAAPD_DIR)/.mt-daapd_compiled

$(MT_DAAPD_DIR)/.mt-daapd_compiled: $(MT_DAAPD_DIR)/.mt-daapd_configured
	@echo "Compiling $(MT_DAAPD) ..."
	make -C $(MT_DAAPD_SOURCE)/$(MT_DAAPD)
	make -C $(MT_DAAPD_SOURCE)/$(MT_DAAPD) install
	@echo "Compiling $(MT_DAAPD) done"
	@touch $@

#
# Update
#
.PHONY: mt-daapd-update

mt-daapd-update:
	@echo "Updating $(MT_DAAPD) ..."
	@if [ -d "$(MT_DAAPD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MT_DAAPD_SOURCE); \
	fi
	@echo "Updating $(MT_DAAPD) done"

#
# Status
#
.PHONY: mt-daapd-status

mt-daapd-status:
	@echo "Statusing $(MT_DAAPD) ..."
	@if [ -d "$(MT_DAAPD_SOURCE)" ]; then\
		$(TOP_STATUS) $(MT_DAAPD_SOURCE); \
	fi
	@echo "Statusing $(MT_DAAPD) done"

#
# Clean
#
.PHONY: mt-daapd-clean

mt-daapd-clean:
	@rm -f $(MT_DAAPD_DIR)/.mt-daapd_configured
	@if [ -d "$(MT_DAAPD_SOURCE)" ]; then\
		make -C $(MT_DAAPD_SOURCE)/$(MT_DAAPD) clean; \
	fi

#
# Dist clean
#
.PHONY: mt-daapd-distclean

mt-daapd-distclean:
	@rm -f $(MT_DAAPD_DIR)/.mt-daapd*

#
# Install
#
.PHONY: mt-daapd-install

mt-daapd-install:
	@echo "Installing $(MT_DAAPD) ..."
	-cp -f $(MT_DAAPD_SOURCE)/config/mt-daapd.playlist $(TOP_INSTALL_ROOTFS_DIR)/etc
	if [ ! -d "$(TOP_INSTALL_ROOTFS_DIR)/var" ]; then \
		mkdir $(TOP_INSTALL_ROOTFS_DIR)/var; \
		mkdir $(TOP_INSTALL_ROOTFS_DIR)/var/admin-root; \
	fi
#	-cp -f $(MT_DAAPD_SOURCE)/admin-root/config.html $(TOP_INSTALL_ROOTFS_DIR)/var/admin-root/
#	-cp -f $(MT_DAAPD_SOURCE)/admin-root/index.html $(TOP_INSTALL_ROOTFS_DIR)/var/admin-root/
	-cp -f $(MT_DAAPD_SOURCE)/admin-root/* $(TOP_INSTALL_ROOTFS_DIR)/var/admin-root/
	-cp -f $(LIBS_INSTALL_PATH)/sbin/mt-daapd $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/bin/mt-daapd

