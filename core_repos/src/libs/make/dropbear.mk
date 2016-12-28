##############################################################################
# Copyright (C)  2015-- 
# All Rights Reserved -- Company Confidential
##############################################################################

#
# These library is scratched from dropbear
#

ifndef CONF_DROPBEAR_VERSION 
CONF_DROPBEAR_VERSION := 2015.67
endif

DROPBEAR             := dropbear-$(CONF_DROPBEAR_VERSION)#
DROPBEAR_SERVER_URL  := $(TOP_LIBS_URL)/dropbear/$(DROPBEAR)
DROPBEAR_DIR         := $(TOP_LIBS_DIR)#
DROPBEAR_SOURCE      := $(DROPBEAR_DIR)/$(DROPBEAR)
DROPBEAR_CONFIG      := 

#DROPBEAR_CONFIGURE := CC=mips-linux-gnu-gcc CPP=mips-linux-gnu-cpp LD==mips-linux-gnu-ld 
DROPBEAR_CONFIGURE := CROSS_COMPILER=mipsel-linux-gnu- \
	./configure --prefix=$(LIBS_INSTALL_PATH) \
	--host=mipsel-linux-gnu --target=mipsel-linux-gnu \
	--sysconfdir=/etc/ssh \
	--with-zlib=$(LIBS_INSTALL_PATH) \
	--disable-lastlog \
	--disable-utmp --disable-utmpx \
	--disable-wtmp --disable-wtmpx 
	
#	
export DROPBEAR
#
# Download  the source 
#
.PHONY: dropbear-downloaded

dropbear-downloaded: $(DROPBEAR_DIR)/.dropbear_downloaded

$(DROPBEAR_DIR)/.dropbear_downloaded:
	@echo "Downloading $(DROPBEAR) from $(DROPBEAR_SERVER_URL) ..."
	@if [ ! -d "$(DROPBEAR_SOURCE)" ]; then \
		cd $(DROPBEAR_DIR); \
		$(TOP_DOWNLOAD) $(DROPBEAR_SERVER_URL); \
	fi
	@echo "Downloading $(DROPBEAR) done"
	@touch $@

#
# Unpack the source
#
.PHONY: dropbear-unpacked

dropbear-unpacked: dropbear-downloaded $(DROPBEAR_DIR)/.dropbear_unpacked

$(DROPBEAR_DIR)/.dropbear_unpacked: $(DROPBEAR_DIR)/.dropbear_downloaded $(wildcard $(DROPBEAR_SOURCE)/*.tar.bz2)
	@echo "Unpacking $(DROPBEAR) ..."
	if [ -d "$(DROPBEAR_SOURCE)/$(DROPBEAR)" ]; then \
		rm -fr $(DROPBEAR_SOURCE)/$(DROPBEAR); \
	fi
	cd $(DROPBEAR_SOURCE);tar xvf  $(DROPBEAR).tar.bz2
	@echo "Unpacking $(DROPBEAR) done"
	@touch $@


#
# Patch the source
#
.PHONY: dropbear-patched

dropbear-patched: $(DROPBEAR_DIR)/.dropbear_patched

$(DROPBEAR_DIR)/.dropbear_patched: $(DROPBEAR_DIR)/.dropbear_unpacked
	@echo "Patching $(DROPBEAR) ..."
	cd $(DROPBEAR_SOURCE);patch -p0 <$(DROPBEAR).patch
	@echo "Patching $(DROPBEAR) done"
	@touch $@

#
# config
#
.PHONY: dropbear-config

dropbear-config:

#
# Configuration
#
.PHONY: dropbear-configured

dropbear-configured:  dropbear-unpacked $(DROPBEAR_DIR)/.dropbear_configured

$(DROPBEAR_DIR)/.dropbear_configured: $(DROPBEAR_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(DROPBEAR) ..." 
	(declare +x CROSS_COMPILE;cd $(DROPBEAR_SOURCE)/$(DROPBEAR); $(DROPBEAR_CONFIGURE))
	@echo "Configuring $(DROPBEAR) done"
	@touch $@

#
# Compile
#
.PHONY: dropbear-compile

dropbear-compile: $(DROPBEAR_DIR)/.dropbear_compiled

$(DROPBEAR_DIR)/.dropbear_compiled: $(DROPBEAR_DIR)/.dropbear_configured
	@echo "Compiling $(DROPBEAR) ..."
	make -C $(DROPBEAR_SOURCE)/$(DROPBEAR)
	make -C $(DROPBEAR_SOURCE)/$(DROPBEAR) install
	@echo "Compiling $(DROPBEAR) done"
	@touch $@

#
# Update
#
.PHONY: dropbear-update

dropbear-update:
	@echo "Updating $(DROPBEAR) ..."
	@if [ -d "$(DROPBEAR_SOURCE)" ]; then\
		$(TOP_UPDATE) $(DROPBEAR_SOURCE); \
	fi
	@echo "Updating $(DROPBEAR) done"

#
# Status
#
.PHONY: dropbear-status

dropbear-status:
	@echo "Statusing $(DROPBEAR) ..."
	@if [ -d "$(DROPBEAR_SOURCE)" ]; then\
		$(TOP_STATUS) $(DROPBEAR_SOURCE); \
	fi
	@echo "Statusing $(DROPBEAR) done"

#
# Clean
#
.PHONY: dropbear-clean

dropbear-clean:
	@rm -f $(DROPBEAR_DIR)/.dropbear_configured
	@if [ -d "$(DROPBEAR_SOURCE)" ]; then\
		make -C $(DROPBEAR_SOURCE)/$(DROPBEAR) clean; \
	fi

#
# Dist clean
#
.PHONY: dropbear-distclean

dropbear-distclean:
	@rm -f $(DROPBEAR_DIR)/.dropbear_*

#
# Install
#
.PHONY: dropbear-install

dropbear-install:
	cp -f $(LIBS_INSTALL_PATH)/sbin/dropbear $(TOP_INSTALL_ROOTFS_DIR)/sbin
	$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/sbin/dropbear
