##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# netatalk makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_NETATALK_VERSION 
NETATALK_VERSION := 2.0.3
else
NETATALK_VERSION := $(CONF_NETATALK_VERSION)
endif

NETATALK             := netatalk-$(NETATALK_VERSION)#
NETATALK_SERVER_URL  := $(TOP_LIBS_URL)/netatalk/$(NETATALK)#b
NETATALK_DIR         := $(TOP_LIBS_DIR)#
NETATALK_SOURCE      := $(NETATALK_DIR)/$(NETATALK)
NETATALK_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        NETATALK_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: netatalk-downloaded

netatalk-downloaded: $(NETATALK_DIR)/.netatalk_downloaded

$(NETATALK_DIR)/.netatalk_downloaded:
	@echo "Downloading $(NETATALK) from $(NETATALK_SERVER_URL) ..."
	@if [ ! -d "$(NETATALK_SOURCE)" ]; then \
		cd $(NETATALK_DIR); \
		$(TOP_DOWNLOAD) $(NETATALK_SERVER_URL); \
	fi
	@echo "Downloading $(NETATALK) from $(NETATALK_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: netatalk-unpacked

netatalk-unpacked: $(NETATALK_DIR)/.netatalk_unpacked

$(NETATALK_DIR)/.netatalk_unpacked: $(NETATALK_DIR)/.netatalk_downloaded $(NETATALK_SOURCE)/$(NETATALK).tar.gz
	@echo "Unpacking $(NETATALK) ..."
	if [ -d "$(NETATALK_SOURCE)/$(NETATALK)" ]; then \
		rm -fr $(NETATALK_SOURCE)/$(NETATALK); \
	fi
	cd $(NETATALK_SOURCE); tar xvzf  $(NETATALK).tar.gz
	@echo "Unpacking $(NETATALK) done"
	@touch $@


#
# Patch the source
#
.PHONY: netatalk-patched

netatalk-patched: $(NETATALK_DIR)/.netatalk_patched

$(NETATALK_DIR)/.netatalk_patched: $(NETATALK_DIR)/.netatalk_unpacked
	# Patching...
# Patching...
	@touch $@

#
# config
#
.PHONY: netatalk-config

netatalk-config: 

#
# Configuration
#
.PHONY: netatalk-configured

netatalk-configured:  netatalk-config $(NETATALK_DIR)/.netatalk_configured

$(NETATALK_DIR)/.netatalk_configured: $(NETATALK_DIR)/.netatalk_patched $(NETATALK_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(NETATALK) ..."
	#cd $(NETATALK_SOURCE)/$(NETATALK);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) --with-bdb=/home/peggy_huang/db-4.2.52/build_unix/db_install/include --without-ssl-dir $(NETATALK_SHARED_FLAGS)
	cd $(NETATALK_SOURCE)/$(NETATALK);./configure --host=$(BUILD_TARGET) --with-bdb=$(LIBS_INSTALL_PATH)include --without-ssl-dir --disable-cups $(NETATALK_SHARED_FLAGS)
	@echo "Configuring $(NETATALK) done"
	@touch $@

#
# Compile
#
.PHONY: netatalk-compile

netatalk-compile: $(NETATALK_DIR)/.netatalk_compiled

$(NETATALK_DIR)/.netatalk_compiled: $(NETATALK_DIR)/.netatalk_configured
	@echo "Compiling $(NETATALK) ..."
	make -C $(NETATALK_SOURCE)/$(NETATALK)/
	@echo "Compiling $(NETATALK) done"
	@touch $@

#
# Update
#
.PHONY: netatalk-update

netatalk-update:
	@echo "Updating $(NETATALK) ..."
	@if [ -d "$(NETATALK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(NETATALK_SOURCE); \
	fi
	@echo "Updating $(NETATALK) done"

#
# Status
#
.PHONY: netatalk-status

netatalk-status:
	@echo "Statusing $(NETATALK) ..."
	@if [ -d "$(NETATALK_SOURCE)" ]; then\
		$(TOP_STATUS) $(NETATALK_SOURCE); \
	fi
	@echo "Statusing $(NETATALK) done"

#
# Clean
#
.PHONY: netatalk-clean

netatalk-clean:
	@rm -f $(NETATALK_DIR)/.netatalk_configured
	@if [ -d "$(NETATALK_SOURCE)" ]; then\
		make -C $(NETATALK_SOURCE)/$(NETATALK)/source clean; \
	fi

#
# Dist clean
#
.PHONY: netatalk-distclean

netatalk-distclean:
	@rm -f $(NETATALK_DIR)/.netatalk_*

#
# Install
#
.PHONY: netatalk-install

netatalk-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/afpd/afpd $(TOP_INSTALL_ROOTFS_DIR)/sbin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/config/afpd.conf.tmpl $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/afpd.conf
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/config/AppleVolumes.default.tmpl $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/AppleVolumes.default
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/config/AppleVolumes.system.cobalt $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/AppleVolumes.system
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_guest.a $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_guest.la $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_guest.so $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_passwd.a $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_passwd.la $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
	cp -f $(NETATALK_SOURCE)/$(NETATALK)/etc/uams/.libs/uams_passwd.so $(TOP_INSTALL_ROOTFS_DIR)/usr/local/etc/netatalk/uams
