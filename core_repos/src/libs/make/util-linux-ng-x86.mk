##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# util-linux-ng-x86 makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_UTIL_LINUX_NG_VERSION 
CONF_UTIL_LINUX_NG_VERSION := 2.17.2
endif

UTIL_LINUX_NG             := util-linux-ng-$(CONF_UTIL_LINUX_NG_VERSION)#
UTIL_LINUX_NG_X86        := util-linux-ng-$(CONF_UTIL_LINUX_NG_VERSION)-x86
UTIL_LINUX_NG_SERVER_URL  := $(TOP_LIBS_URL)/util-linux-ng/$(UTIL_LINUX_NG)#
UTIL_LINUX_NG_DIR         := $(TOP_LIBS_DIR)#
UTIL_LINUX_NG_SOURCE      := $(UTIL_LINUX_NG_DIR)/$(UTIL_LINUX_NG_X86)#
UTIL_LINUX_NG_CONFIG      := 

UTIL_LINUX_NG_CONFIGURE_X86 := --build=$(BUILD_HOST) --host=x86 --without-ncurses CC=gcc CFLAGS="" LDFLAGS="" CPP=""

#
# Download  the source 
#
.PHONY: util-linux-ng-x86-downloaded

util-linux-ng-x86-downloaded: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_downloaded

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_downloaded:
	@echo "Downloading $(UTIL_LINUX_NG) from $(UTIL_LINUX_NG_SERVER_URL) ..."
	@if [ ! -d "$(UTIL_LINUX_NG_SOURCE)" ]; then \
		cd $(UTIL_LINUX_NG_DIR); \
		$(TOP_DOWNLOAD) $(UTIL_LINUX_NG_SERVER_URL) $(UTIL_LINUX_NG_SOURCE); \
	fi
	@echo "Downloading $(UTIL_LINUX_NG) done"
	@touch $@

#
# Unpack the source
#
.PHONY: util-linux-ng-x86-unpacked

util-linux-ng-x86-unpacked: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_unpacked

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_unpacked: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_downloaded $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG).tar.gz
	@echo "Unpacking $(UTIL_LINUX_NG) ..."
	if [ -d "$(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG)" ]; then \
		rm -fr $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG); \
	fi
	(cd $(UTIL_LINUX_NG_SOURCE); tar zxvf $(UTIL_LINUX_NG).tar.gz)
	@echo "Unpacking $(UTIL_LINUX_NG) done"
	@touch $@

#
# Configuration
#
.PHONY: util-linux-ng-x86-configured

util-linux-ng-x86-configured:  util-linux-ng-x86-config $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_configured

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_configured: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_unpacked
	@echo "Configuring $(UTIL_LINUX_NG) ..."
	cd $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG); ./configure $(UTIL_LINUX_NG_CONFIGURE_X86)
	@echo "Configuring $(UTIL_LINUX_NG) done"
	@touch $@

#
# Compile
#
.PHONY: util-linux-ng-x86-compile

util-linux-ng-x86-compile: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_compiled

$(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_compiled: $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_configured
	@echo "Compiling $(UTIL_LINUX_NG) ..."
	make -C $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG)/mount/
	cp $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG)/mount/losetup $(TOP_TOOLS_DIR)
	@echo "Compiling $(UTIL_LINUX_NG) done"
	@touch $@

#
# Update
#
.PHONY: util-linux-ng-x86-update

util-linux-ng-x86-update:
	@echo "Updating $(UTIL_LINUX_NG) ..."
	@if [ -d "$(UTIL_LINUX_NG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(UTIL_LINUX_NG_SOURCE); \
	fi
	@echo "Updating $(UTIL_LINUX_NG) done"

#
# Status
#
.PHONY: util-linux-ng-x86-status

util-linux-ng-x86-status:
	@echo "Statusing $(UTIL_LINUX_NG) ..."
	@if [ -d "$(UTIL_LINUX_NG_SOURCE)" ]; then\
		$(TOP_STATUS) $(UTIL_LINUX_NG_SOURCE); \
	fi
	@echo "Statusing $(UTIL_LINUX_NG) done"

#
# Clean
#
.PHONY: util-linux-ng-x86-clean

util-linux-ng-x86-clean:
	@rm -f $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86_configured
	@if [ -d "$(UTIL_LINUX_NG_SOURCE)" ]; then\
		make -C $(UTIL_LINUX_NG_SOURCE)/$(UTIL_LINUX_NG) clean; \
	fi

#
# Dist clean
#
.PHONY: util-linux-ng-x86-distclean

util-linux-ng-x86-distclean:
	@rm -f $(UTIL_LINUX_NG_DIR)/.util-linux-ng-x86*

#
# Install
#
.PHONY: util-linux-ng-x86-install

util-linux-ng-x86-install:
