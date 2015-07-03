##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  sh_yang@alphanetworks.com
# lltd makefile fragments 
##############################################################################

#
# Defines
#
LLTD             := lltd-$(LLTD_VERSION)#
LLTD_SERVER_URL  := $(TOP_LIBS_URL)/lltd/$(LLTD)#b
LLTD_DIR         := $(TOP_LIBS_DIR)#
LLTD_SOURCE      := $(LLTD_DIR)/$(LLTD)
LLTD_CONFIG      := 

#ifeq (x$(ENABLE_SHLIB),xyes)
#        LLTD_SHARED_FLAGS      := --shared
#endif

#
# Download  the source 
#
.PHONY: lltd-downloaded

lltd-downloaded: $(LLTD_DIR)/.lltd_downloaded

$(LLTD_DIR)/.lltd_downloaded:
	@echo "Downloading $(LLTD) from $(LLTD_SERVER_URL) ..."
	@if [ ! -d "$(LLTD_SOURCE)" ]; then \
		cd $(LLTD_DIR); \
		$(TOP_DOWNLOAD) $(LLTD_SERVER_URL); \
	fi
	@echo "Downloading $(LLTD) from $(LLTD_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: lltd-unpacked

lltd-unpacked: $(LLTD_DIR)/.lltd_unpacked

$(LLTD_DIR)/.lltd_unpacked: $(LLTD_DIR)/.lltd_downloaded $(LLTD_SOURCE)/LLTD-PortingKit.tar.gz
	@echo "Unpacking $(LLTD) ..."
	if [ -d "$(LLTD_SOURCE)/$(LLTD)" ]; then \
		rm -fr $(LLTD_SOURCE)/$(LLTD); \
	fi
	cd $(LLTD_SOURCE); tar zxvf LLTD-PortingKit.tar.gz
	cd $(LLTD_SOURCE); mv LLTD-PortingKit/Sample\ Code LLTD-PortingKit/Sample_Code
	@echo "Unpacking $(LLTD) done"
	@touch $@


#
# Patch the source
#
.PHONY: lltd-patched

lltd-patched: $(LLTD_DIR)/.lltd_patched

$(LLTD_DIR)/.lltd_patched: $(LLTD_DIR)/.lltd_unpacked
	# Patching...
# Patching...
	@touch $@

#
# config
#
.PHONY: lltd-config

lltd-config: 

#
# Configuration
#
.PHONY: lltd-configured

lltd-configured:  lltd-config $(LLTD_DIR)/.lltd_configured

$(LLTD_DIR)/.lltd_configured: $(LLTD_DIR)/.lltd_patched $(LLTD_CONFIG) $(TOP_CURRENT_SET)
	@touch $@
	cd $(LLTD_SOURCE)/LLTD-PortingKit; patch -p1 < ../LLTD-PortingKit.patch
	cd $(LLTD_SOURCE)/LLTD-PortingKit; patch -p1 < ../1000.lld2d.conf.patch
ifeq ($(CONF_PLATFORM_SMP8654), y)
	cd $(LLTD_SOURCE)/LLTD-PortingKit; patch -p1 < ../1001.mapping.c.patch
endif
	cd $(LLTD_SOURCE)/LLTD-PortingKit; patch -p1 < ../1002.link_speed.patch

#
# Compile
#
.PHONY: lltd-compile

lltd-compile: $(LLTD_DIR)/.lltd_compiled

$(LLTD_DIR)/.lltd_compiled: $(LLTD_DIR)/.lltd_configured
	@echo "Compiling $(LLTD) ..."
	make -C $(LLTD_SOURCE)/LLTD-PortingKit/Sample_Code/native-linux/
	@echo "Compiling $(LLTD) done"
	@touch $@

#
# Update
#
.PHONY: lltd-update

lltd-update:
	@echo "Updating $(LLTD) ..."
	@if [ -d "$(LLTD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LLTD_SOURCE); \
	fi
	@echo "Updating $(LLTD) done"

#
# Status
#
.PHONY: lltd-status

lltd-status:
	@echo "Statusing $(LLTD) ..."
	@if [ -d "$(LLTD_SOURCE)" ]; then\
		$(TOP_STATUS) $(LLTD_SOURCE); \
	fi
	@echo "Statusing $(LLTD) done"

#
# Clean
#
.PHONY: lltd-clean

lltd-clean:
	@rm -f $(LLTD_DIR)/.lltd_configured
	@if [ -d "$(LLTD_SOURCE)" ]; then\
		make -C $(LLTD_SOURCE)/$(LLTD)/build_unix clean; \
	fi

#
# Dist clean
#
.PHONY: lltd-distclean

lltd-distclean:
	@rm -f $(LLTD_DIR)/.lltd_*

#
# Install
#
.PHONY: lltd-install

lltd-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(LLTD_SOURCE)/LLTD-PortingKit/Sample_Code/native-linux/lld2d $(TOP_INSTALL_ROOTFS_DIR)/bin 
	cp -f $(LLTD_SOURCE)/LLTD-PortingKit/Sample_Code/src/lld2d.conf $(TOP_INSTALL_ROOTFS_DIR)/etc
