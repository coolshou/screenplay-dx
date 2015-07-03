##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# twonkymedia makefile fragments 
##############################################################################

#
# Defines
#

ifndef CONF_TWONKYMEDIA_SERVER_VERSION
ifeq (x$(CONF_PLATFORM_SMP8634), xy)
	CONF_TWONKYMEDIA_SERVER_VERSION := 4.4.1-SMP8634
endif
ifeq (x$(CONF_PLATFORM_SMP8654), xy)
	CONF_TWONKYMEDIA_SERVER_VERSION := 4.4.1-SMP8654
endif
ifeq (x$(CONF_PLATFORM_X86), xy)
	CONF_TWONKYMEDIA_SERVER_VERSION := 5.0.0-X86
endif
endif

TWONKYMEDIA_SERVER		:= twonkymedia_server-$(CONF_TWONKYMEDIA_SERVER_VERSION)#
TWONKYMEDIA_SERVER_URL		:= $(TOP_LIBS_URL)/twonkymedia_server/$(TWONKYMEDIA_SERVER)
TWONKYMEDIA_SERVER_DIR		:= $(TOP_LIBS_DIR)#
TWONKYMEDIA_SERVER_SOURCE	:= $(TWONKYMEDIA_SERVER_DIR)/$(TWONKYMEDIA_SERVER)

TWONKYMEDIA_SERVER_CONFIG	:=

RESOURCE_SRC_DIR        	:= $(TOP_LIBS_DIR)/$(CONF_RESOURCE)/resource

#
# Download the source
#
twonkymedia_server-downloaded: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-downloaded

$(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-downloaded:
	echo $(CONF_TWONKYMEDIA_SERVER_VERSION)
	@echo "Downloading $(TWONKYMEDIA_SERVER) from $(TWONKYMEDIA_SERVER_URL) ..."
	@if [ ! -d "$(TWONKYMEDIA_SERVER_SOURCE)" ]; then \
		cd $(TWONKYMEDIA_SERVER_DIR); \
		$(TOP_DOWNLOAD) $(TWONKYMEDIA_SERVER_URL); \
	fi
	@echo "Downloading $(TWONKYMEDIA_SERVER) done"
	@touch $@


#
# Unpack the source
#

.PHONY: twonkymedia_server-unpacked

twonkymedia_server-unpacked: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-unpacked

$(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-unpacked: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-downloaded
	@touch $@

#
# Patch the source
#
.PHONY: twonkymedia_server-patched

twonkymedia_server-patched: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-patched

$(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-patched: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-unpacked
	@touch $@


#
# config
#
.PHONY: twonkymedia_server-config

twonkymedia_server-config: 


#
# Configuration
#
.PHONY: twonkymedia_server-configured

twonkymedia_server-configured:


#
# Compile
#
.PHONY: twonkymedia_server-compile

twonkymedia_server-compile: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-compile

$(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-compile: $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-patched
	@touch $@


#
# Update
#
.PHONY: twonkymedia_server-update

twonkymedia_server-update:
	@echo "Updating $(TWONKYMEDIA_SERVER) ..."
	@if [ -d "$(TWONKYMEDIA_SERVER_SOURCE)" ]; then\
		$(TOP_UPDATE) $(TWONKYMEDIA_SERVER_SOURCE); \
	fi
	@echo "Updating $(TWONKYMEDIA_SERVER) done"


#
# Status
#
.PHONY: twonkymedia_server-status

twonkymedia_server-status:
	@echo "Statusing $(TWONKYMEDIA_SERVER) ..."
	@if [ -d "$(TWONKYMEDIA_SERVER_SOURCE)" ]; then\
		$(TOP_STATUS) $(TWONKYMEDIA_SERVER_SOURCE); \
	fi
	@echo "Statusing $(TWONKYMEDIA_SERVER) done"


#
# Clean
#
.PHONY: twonkymedia_server-clean

twonkymedia_server-clean:


#
# Dist clean
#
.PHONY: twonkymedia_server-distclean

twonkymedia_server-distclean:
	@rm -f $(TWONKYMEDIA_SERVER_DIR)/.twonkymedia_server-*


#
# Install
#
.PHONY: twonkymedia_server-install

twonkymedia_server-install:
	-mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr
	-mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local
	-mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky
	-cp $(TWONKYMEDIA_SERVER_SOURCE)/* $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky -rf 
	-chmod 700 $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/twonkym* $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/cgi-bin/* $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/plugins/*
	-ln -s /tmp/TwonkyVision $(TOP_INSTALL_ROOTFS_DIR)/usr/local/TwonkyVision
ifeq (x$(CONF_PLATFORM_X86), xy)
	-ln -s $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky $(TOP_INSTALL_ROOTFS_DIR)/usr/local/TwonkyVision
else
	-ln -s /tmp/TwonkyVision $(TOP_INSTALL_ROOTFS_DIR)/usr/local/TwonkyVision
endif


	if [ -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_48x48.jpg ]; then \
		cp -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_48x48.jpg $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/resources/twonkyicon-48x48.jpg; \
	fi
	if [ -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_48x48.png ]; then \
		cp -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_48x48.png $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/resources/twonkyicon-48x48.png; \
	fi
	if [ -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_120x120.jpg ]; then \
		cp -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_120x120.jpg $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/resources/twonkyicon-120x120.jpg; \
	fi
	if [ -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_120x120.png ]; then \
		cp -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_120x120.png $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/resources/twonkyicon-120x120.png; \
	fi
	if [ -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_80x80.jpg ]; then \
		cp -f $(RESOURCE_SRC_DIR)/image/icon_logo4wmc_80x80.jpg $(TOP_INSTALL_ROOTFS_DIR)/usr/local/twky/resources/twonkyicon-80x80.jpg; \
	fi


