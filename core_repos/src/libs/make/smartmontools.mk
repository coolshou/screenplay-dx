##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# smartmontools makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_SMARTMONTOOLS_VERSION 
CONF_SMARTMONTOOLS_VERSION := 5.39.1
endif

SMARTMONTOOLS             := smartmontools-$(CONF_SMARTMONTOOLS_VERSION)#
SMARTMONTOOLS_SERVER_URL  := $(TOP_LIBS_URL)/smartmontools/$(SMARTMONTOOLS)
SMARTMONTOOLS_DIR         := $(TOP_LIBS_DIR)#
SMARTMONTOOLS_SOURCE      := $(SMARTMONTOOLS_DIR)/$(SMARTMONTOOLS)
SMARTMONTOOLS_CONFIG      := 

#
# Download  the source 
#
.PHONY: smartmontools-downloaded

smartmontools-downloaded: $(SMARTMONTOOLS_DIR)/.smartmontools_downloaded

$(SMARTMONTOOLS_DIR)/.smartmontools_downloaded:
	@echo "Downloading $(SMARTMONTOOLS) from $(SMARTMONTOOLS_SERVER_URL) ..."
	@if [ ! -d "$(SMARTMONTOOLS_SOURCE)" ]; then \
		cd $(SMARTMONTOOLS_DIR); \
		$(TOP_DOWNLOAD) $(SMARTMONTOOLS_SERVER_URL); \
	fi
	@echo "Downloading $(SMARTMONTOOLS) from $(SMARTMONTOOLS_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: smartmontools-unpacked

smartmontools-unpacked: $(SMARTMONTOOLS_DIR)/.smartmontools_unpacked

$(SMARTMONTOOLS_DIR)/.smartmontools_unpacked: $(SMARTMONTOOLS_DIR)/.smartmontools_downloaded $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS).tar.gz
	@echo "Unpacking $(SMARTMONTOOLS) ..."
	if [ -d "$(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS)" ]; then \
		rm -fr $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS); \
	fi
	cd $(SMARTMONTOOLS_SOURCE); tar xzvf $(SMARTMONTOOLS).tar.gz
	@echo "Unpacking $(SMARTMONTOOLS) done"
	@touch $@


#
# Patch the source
#
.PHONY: smartmontools-patched

smartmontools-patched: $(SMARTMONTOOLS_DIR)/.smartmontools_patched

$(SMARTMONTOOLS_DIR)/.smartmontools_patched: $(SMARTMONTOOLS_DIR)/.smartmontools_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: smartmontools-config

smartmontools-config: 

#
# Configuration
#
.PHONY: smartmontools-configured

smartmontools-configured:  smartmontools-config $(SMARTMONTOOLS_DIR)/.smartmontools_configured

$(SMARTMONTOOLS_DIR)/.smartmontools_configured: $(SMARTMONTOOLS_DIR)/.smartmontools_patched $(SMARTMONTOOLS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(SMARTMONTOOLS) ..."
	#cd $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS);./configure  --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)  CFLAGS=" -I$(LIBS_INSTALL_PATH)/include/" LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib/" LIBUSB_LIBS="-lusb -I$(LIBS_INSTALL_PATH)/include/" LIBUSB_CFLAGS="-lusb -L$(LIBS_INSTALL_PATH)/lib/" PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" LIBUSB_CONFIG="$(LIBS_INSTALL_PATH)/bin" --enable-shared=yes 
	cd $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS);./configure  --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" POPT_LIBS="-L$(LIBS_INSTALL_PATH)/lib/ -lpopt" POPT_CFLAGS=-I$(LIBS_INSTALL_PATH)/include/ 
       	
	@echo "Configuring $(SMARTMONTOOLS) done"
	@touch $@

#
# Compile
#
.PHONY: smartmontools-compile

smartmontools-compile: $(SMARTMONTOOLS_DIR)/.smartmontools_compiled

$(SMARTMONTOOLS_DIR)/.smartmontools_compiled: $(SMARTMONTOOLS_DIR)/.smartmontools_configured
	@echo "Compiling $(SMARTMONTOOLS) ..."
	#make -C $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS) BUILD_INFO=\""(Alpha)\"" 
	make -C $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS)  install
	@echo "Compiling $(SMARTMONTOOLS) done"
	@touch $@

#
# Update
#
.PHONY: smartmontools-update

smartmontools-update:
	@echo "Updating $(SMARTMONTOOLS) ..."
	@if [ -d "$(SMARTMONTOOLS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SMARTMONTOOLS_SOURCE); \
	fi
	@echo "Updating $(SMARTMONTOOLS) done"

#
# Status
#
.PHONY: smartmontools-status

smartmontools-status:
	@echo "Statusing $(SMARTMONTOOLS) ..."
	@if [ -d "$(SMARTMONTOOLS_SOURCE)" ]; then\
		$(TOP_STATUS) $(SMARTMONTOOLS_SOURCE); \
	fi
	@echo "Statusing $(SMARTMONTOOLS) done"

#
# Clean
#
.PHONY: smartmontools-clean

smartmontools-clean:
	@rm -f $(SMARTMONTOOLS_DIR)/.smartmontools_configured
	@if [ -d "$(SMARTMONTOOLS_SOURCE)" ]; then\
		make -C $(SMARTMONTOOLS_SOURCE)/$(SMARTMONTOOLS) clean; \
	fi

#
# Dist clean
#
.PHONY: smartmontools-distclean

smartmontools-distclean:
	@rm -f $(SMARTMONTOOLS_DIR)/.smartmontools_*

#
# Install
#
.PHONY: smartmontools-install

smartmontools-install:
	cp -f $(LIBS_INSTALL_PATH)/sbin/smartctl $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/bin/smartctl

