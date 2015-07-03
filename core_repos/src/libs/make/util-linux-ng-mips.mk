##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# util-linux-ng-mips makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_UTIL_LINUX_NG_VERSION 
CONF_UTIL_LINUX_NG_VERSION := 2.17.2
endif

UTIL_LINUX_NG             := util-linux-ng-$(CONF_UTIL_LINUX_NG_VERSION)#
UTIL_LINUX_NG_MIPS        := util-linux-ng-$(CONF_UTIL_LINUX_NG_VERSION)-mips
UTIL_LINUX_NG_SERVER_URL  := $(TOP_LIBS_URL)/util-linux-ng/$(UTIL_LINUX_NG)#
UTIL_LINUX_NG_DIR         := $(TOP_LIBS_DIR)#
UTIL_LINUX_NG_SOURCE_MIPS      := $(UTIL_LINUX_NG_DIR)/$(UTIL_LINUX_NG_MIPS)#
UTIL_LINUX_NG_CONFIG      := 

UTIL_LINUX_NG_CONFIGURE_MIPS := --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-static-programs=mount --without-ncurses

#
# Download  the source 
#
.PHONY: util-linux-ng-mips-downloaded

util-linux-ng-mips-downloaded: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_downloaded

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_downloaded:
	@echo "Downloading $(UTIL_LINUX_NG) from $(UTIL_LINUX_NG_SERVER_URL) ..."
	@if [ ! -d "$(UTIL_LINUX_NG_SOURCE_MIPS)" ]; then \
		cd $(UTIL_LINUX_NG_DIR); \
		$(TOP_DOWNLOAD) $(UTIL_LINUX_NG_SERVER_URL) $(UTIL_LINUX_NG_SOURCE_MIPS); \
	fi
	@echo "Downloading $(UTIL_LINUX_NG) done"
	@touch $@

#
# Unpack the source
#
.PHONY: util-linux-ng-mips-unpacked

util-linux-ng-mips-unpacked: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_unpacked

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_unpacked: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_downloaded $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG).tar.gz
	@echo "Unpacking $(UTIL_LINUX_NG) ..."
	if [ -d "$(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG)" ]; then \
		rm -fr $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG); \
	fi
	(cd $(UTIL_LINUX_NG_SOURCE_MIPS); tar zxvf $(UTIL_LINUX_NG).tar.gz)
	@echo "Unpacking $(UTIL_LINUX_NG) done"
	@touch $@

#
# Configuration
#
.PHONY: util-linux-ng-mips-configured

util-linux-ng-mips-configured:  util-linux-ng-mips-config $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_configured

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_configured: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_unpacked
	@echo "Configuring $(UTIL_LINUX_NG) ..."
	cd $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG); ./configure $(UTIL_LINUX_NG_CONFIGURE_MIPS)
	@echo "Configuring $(UTIL_LINUX_NG) done"
	@touch $@

#
# Compile
#
.PHONY: util-linux-ng-mips-compile

util-linux-ng-mips-compile: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_compiled

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_compiled: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_configured
	@echo "Compiling $(UTIL_LINUX_NG) ..."
	make -C $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG)/mount/
	@echo "Compiling $(UTIL_LINUX_NG) done"
	@touch $@

#
# Update
#
.PHONY: util-linux-ng-mips-update

util-linux-ng-mips-update:
	@echo "Updating $(UTIL_LINUX_NG) ..."
	@if [ -d "$(UTIL_LINUX_NG_SOURCE_MIPS)" ]; then\
		$(TOP_UPDATE) $(UTIL_LINUX_NG_SOURCE_MIPS); \
	fi
	@echo "Updating $(UTIL_LINUX_NG) done"

#
# Status
#
.PHONY: util-linux-ng-mips-status

util-linux-ng-mips-status:
	@echo "Statusing $(UTIL_LINUX_NG) ..."
	@if [ -d "$(UTIL_LINUX_NG_SOURCE_MIPS)" ]; then\
		$(TOP_STATUS) $(UTIL_LINUX_NG_SOURCE_MIPS); \
	fi
	@echo "Statusing $(UTIL_LINUX_NG) done"

#
# Clean
#
.PHONY: util-linux-ng-mips-clean

util-linux-ng-mips-clean:
	@rm -f $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips_configured
	@if [ -d "$(UTIL_LINUX_NG_SOURCE_MIPS)" ]; then\
		make -C $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG) clean; \
	fi

#
# Dist clean
#
.PHONY: util-linux-ng-mips-distclean

util-linux-ng-mips-distclean:
	@rm -f $(UTIL_LINUX_NG_DIR)/.util-linux-ng-mips*

#
# Install
#
.PHONY: util-linux-ng-mips-install

util-linux-ng-mips-install:
	cp $(UTIL_LINUX_NG_SOURCE_MIPS)/$(UTIL_LINUX_NG)/mount/mount.static $(TOP_INSTALL_ROOTFS_DIR)/bin/mymount
