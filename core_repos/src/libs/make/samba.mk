##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# samba makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_SAMBA_VERSION 
SAMBA_VERSION := 3.0.28a
else
SAMBA_VERSION := $(CONF_SAMBA_VERSION)
endif

SAMBA             := samba-$(SAMBA_VERSION)#
SAMBA_SERVER_URL  := $(TOP_LIBS_URL)/samba/$(SAMBA)#b
SAMBA_DIR         := $(TOP_LIBS_DIR)#
SAMBA_SOURCE      := $(SAMBA_DIR)/$(SAMBA)
SAMBA_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        SAMBA_SHARED_FLAGS      := --shared
#endif

ifeq ($(SAMBA_VERSION), 3.0.28a)
SOURCE_FOLDER := source
else
SOURCE_FOLDER := source3
endif

#
# Download  the source 
#
.PHONY: samba-downloaded

samba-downloaded: $(SAMBA_DIR)/.samba_downloaded

$(SAMBA_DIR)/.samba_downloaded:
	@echo "Downloading $(SAMBA) from $(SAMBA_SERVER_URL) ..."
	@if [ ! -d "$(SAMBA_SOURCE)" ]; then \
		cd $(SAMBA_DIR); \
		$(TOP_DOWNLOAD) $(SAMBA_SERVER_URL); \
	fi
	@echo "Downloading $(SAMBA) from $(SAMBA_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: samba-unpacked

samba-unpacked: $(SAMBA_DIR)/.samba_unpacked

$(SAMBA_DIR)/.samba_unpacked: $(SAMBA_DIR)/.samba_downloaded $(SAMBA_SOURCE)/$(SAMBA).tar.gz
	@echo "Unpacking $(SAMBA) ..."
	if [ -d "$(SAMBA_SOURCE)/$(SAMBA)" ]; then \
		rm -fr $(SAMBA_SOURCE)/$(SAMBA); \
	fi
	cd $(SAMBA_SOURCE); tar xvzf  $(SAMBA).tar.gz
	@echo "Unpacking $(SAMBA) done"
	@touch $@


#
# Patch the source
#
.PHONY: samba-patched

samba-patched: $(SAMBA_DIR)/.samba_patched

$(SAMBA_DIR)/.samba_patched: $(SAMBA_DIR)/.samba_unpacked
	# Patching...
# Patching...
	cd $(SAMBA_SOURCE)/$(SAMBA); patch -p1 < ../$(SAMBA).patch
	if [ x$(CONF_SAMBA_FTRUNCATE_PATCH) == xy && x$(CONF_SAMBA_VERSION_3_0_28A) == xy]; then \
		cd $(SAMBA_SOURCE)/$(SAMBA); patch -p2 < ../ftruncate.patch ;\
	fi
	@touch $@

#
# config
#
.PHONY: samba-config

samba-config: 

#
# Configuration
#
.PHONY: samba-configured

samba-configured:  samba-config $(SAMBA_DIR)/.samba_configured

$(SAMBA_DIR)/.samba_configured: $(SAMBA_DIR)/.samba_patched $(SAMBA_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(SAMBA) ..."
	cd $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) --disable-cups $(SAMBA_SHARED_FLAGS) --with-ldap=no --enable-debug=yes --enable-shared=no
	#cd $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER);./configure --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) --disable-cups $(SAMBA_SHARED_FLAGS)
	@echo "Configuring $(SAMBA) done"
	@touch $@

#
# Compile
#
.PHONY: samba-compile

samba-compile: $(SAMBA_DIR)/.samba_compiled

$(SAMBA_DIR)/.samba_compiled: $(SAMBA_DIR)/.samba_configured
	@echo "Compiling $(SAMBA) ..."
	make -C $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER) 
	make -C $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)  install
	@echo "Compiling $(SAMBA) done"
	@touch $@

#
# Update
#
.PHONY: samba-update

samba-update:
	@echo "Updating $(SAMBA) ..."
	@if [ -d "$(SAMBA_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SAMBA_SOURCE); \
	fi
	@echo "Updating $(SAMBA) done"

#
# Status
#
.PHONY: samba-status

samba-status:
	@echo "Statusing $(SAMBA) ..."
	@if [ -d "$(SAMBA_SOURCE)" ]; then\
		$(TOP_STATUS) $(SAMBA_SOURCE); \
	fi
	@echo "Statusing $(SAMBA) done"

#
# Clean
#
.PHONY: samba-clean

samba-clean:
	@rm -f $(SAMBA_DIR)/.samba_configured
	@if [ -d "$(SAMBA_SOURCE)" ]; then\
		make -C $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER) clean; \
	fi

#
# Dist clean
#
.PHONY: samba-distclean

samba-distclean:
	@rm -f $(SAMBA_DIR)/.samba_*

#
# Install
#
.PHONY: samba-install

samba-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)/bin/nmblookup $(TOP_INSTALL_ROOTFS_DIR)/bin
ifeq (x$(CONF_SAMBA_SERVER_SUPPORT_SECURITY), xy)
	cp -f $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)/bin/smbpasswd $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/bin/smbpasswd
endif
ifeq (x$(CONF_SAMBA_SERVER), xy)
	mkdir -p ${TOP_BUILD_ROOTFS_DIR}/usr/sbin/
	cp -f $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)/bin/smbd $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/
	cp -f $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)/bin/nmbd $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/smbd
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/nmbd
ifeq (x$(CONF_SAMBA_INSTALL_SMBCLIENT), xy)
	cp -f $(SAMBA_SOURCE)/$(SAMBA)/$(SOURCE_FOLDER)/bin/smbclient $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/smbclient
endif
endif
