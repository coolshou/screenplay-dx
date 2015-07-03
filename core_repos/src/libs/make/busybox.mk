##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# busybox makefile fragments 
##############################################################################

#
# Defines
#
BUSYBOX             := busybox-$(CONF_BUSYBOX_VERSION)#
BUSYBOX_SERVER_URL  := $(TOP_LIBS_URL)/busybox/$(BUSYBOX)
BUSYBOX_DIR         := $(TOP_LIBS_DIR)#
BUSYBOX_SOURCE      := $(BUSYBOX_DIR)/$(BUSYBOX)
ifeq (x$(CONF_BUSYBOX_1_10_0), xy)
BUSYBOX_CONFIG      := $(TOP_CONFIG_DIR)/busybox-1.10.0-config
endif

#
# Download  the source 
#
.PHONY: busybox-downloaded

busybox-downloaded: $(BUSYBOX_DIR)/.busybox_downloaded

$(BUSYBOX_DIR)/.busybox_downloaded:
	@echo "Downloading $(BUSYBOX) from $(BUSYBOX_SERVER_URL) ..."
	@if [ ! -d "$(BUSYBOX_SOURCE)" ]; then \
		cd $(BUSYBOX_DIR); \
		$(TOP_DOWNLOAD) $(BUSYBOX_SERVER_URL); \
	fi
	@echo "Downloading $(BUSYBOX) done"
	@touch $@

#
# Unpack the source
#
.PHONY: busybox-unpacked

busybox-unpacked: $(BUSYBOX_DIR)/.busybox_unpacked

$(BUSYBOX_DIR)/.busybox_unpacked: $(BUSYBOX_DIR)/.busybox_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: busybox-patched

busybox-patched: $(BUSYBOX_DIR)/.busybox_patched

$(BUSYBOX_DIR)/.busybox_patched: $(BUSYBOX_DIR)/.busybox_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: busybox-config

busybox-config: busybox-patched 
	@if [ -f $(BUSYBOX_CONFIG) ]; then \
		cp -pf $(BUSYBOX_CONFIG) $(BUSYBOX_SOURCE)/.config; \
	fi
	if [ x$(CONF_BUSYBOX_1_10_0_CONFIG_FOR_NETWORKING) == xy ]; then \
		cp -pf $(BUSYBOX_CONFIG)-networking $(BUSYBOX_SOURCE)/.config; \
 	fi	
	if [ x$(CONF_WIN7_WAKEONLAN) == xy ]; then \
		sed -i -e "s/\# CONFIG_ETHER_WAKE is not set/CONFIG_ETHER_WAKE=y/" $(BUSYBOX_SOURCE)/.config; \
	fi
	if [ x$(CONF_CONSOLE_SECURE) == xy ]; then \
		sed -i -e "s/\# CONFIG_LOGIN is not set/CONFIG_LOGIN=y/" $(BUSYBOX_SOURCE)/.config;  \
		sed -i -e "s/\# CONFIG_CHPASSWD is not set/CONFIG_CHPASSWD=y/" $(BUSYBOX_SOURCE)/.config; \
	fi

#
# Configuration
#
.PHONY: busybox-configured

busybox-configured:  busybox-config $(BUSYBOX_DIR)/.busybox_configured

$(BUSYBOX_DIR)/.busybox_configured: $(BUSYBOX_DIR)/.busybox_patched $(BUSYBOX_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(BUSYBOX) ..."
	make -C $(BUSYBOX_SOURCE) oldconfig
	make -C $(BUSYBOX_SOURCE) dep
	@echo "Configuring $(BUSYBOX) done"
	@touch $@

#
# Compile
#
.PHONY: busybox-compile

busybox-compile: busybox-configured $(BUSYBOX_DIR)/.busybox_compiled

$(BUSYBOX_DIR)/.busybox_compiled:
	@echo "Compiling $(BUSYBOX) ..." 
	-make -C $(BUSYBOX_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)  CROSS_COMPILE="$(CROSS)" -C $(BUSYBOX_SOURCE)
	@echo "Compiling $(BUSYBOX) done" 
	touch	$@

#
# Update
#
.PHONY: busybox-update

busybox-update:
	@echo "Updating $(BUSYBOX) ..."
	@if [ -d "$(BUSYBOX_SOURCE)" ]; then\
		$(TOP_UPDATE) $(BUSYBOX_SOURCE); \
	fi
	@echo "Updating $(BUSYBOX) done"

#
# Status
#
.PHONY: busybox-status

busybox-status:
	@echo "Statusing $(BUSYBOX) ..."
	@if [ -d "$(BUSYBOX_SOURCE)" ]; then\
		$(TOP_STATUS) $(BUSYBOX_SOURCE); \
	fi
	@echo "Statusing $(BUSYBOX) done"

#
# Clean
#
.PHONY: busybox-clean

busybox-clean:
	@rm -f $(BUSYBOX_DIR)/.busybox_configured
	@if [ -d "$(BUSYBOX_SOURCE)" ]; then\
		make -C $(BUSYBOX_SOURCE) clean; \
	fi
	$(BUSYBOX_DIR)/.busybox_compiled

#
# Dist clean
#
.PHONY: busybox-distclean

busybox-distclean:
	@rm -f $(BUSYBOX_DIR)/.busybox_*
#@rm -fr $(BUSYBOX_SOURCE)

#
# Install
#
.PHONY: busybox-install

busybox-install:
	-make -C $(BUSYBOX_SOURCE)  CC=$(CC) CROSS_COMPILE="$(CROSS)" PREFIX="$(TOP_INSTALL_ROOTFS_DIR)" \
	                       EXTRA_CFLAGS="$(TARGET_CFLAGS)"	CONFIG_PREFIX=$(TOP_INSTALL_ROOTFS_DIR) install
	(cd $(TOP_INSTALL_ROOTFS_DIR)/bin; rm -f sh; ln -s busybox sh) 
	# Just in case
	-chmod a+x $(TOP_INSTALL_ROOTFS_DIR)/usr/share/udhcpc/default.script

