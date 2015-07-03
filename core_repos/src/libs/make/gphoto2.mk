##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# gphoto2 makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_GPHOTO2_VERSION 
CONF_GPHOTO2_VERSION := 2.4.4
endif

GPHOTO2             := gphoto2-$(CONF_GPHOTO2_VERSION)#
GPHOTO2_SERVER_URL  := $(TOP_LIBS_URL)/gphoto2/$(GPHOTO2)
GPHOTO2_DIR         := $(TOP_LIBS_DIR)#
GPHOTO2_SOURCE      := $(GPHOTO2_DIR)/$(GPHOTO2)
GPHOTO2_CONFIG      := 

#
# Download  the source 
#
.PHONY: gphoto2-downloaded

gphoto2-downloaded: $(GPHOTO2_DIR)/.gphoto2_downloaded

$(GPHOTO2_DIR)/.gphoto2_downloaded:
	@echo "Downloading $(GPHOTO2) from $(GPHOTO2_SERVER_URL) ..."
	@if [ ! -d "$(GPHOTO2_SOURCE)" ]; then \
		cd $(GPHOTO2_DIR); \
		$(TOP_DOWNLOAD) $(GPHOTO2_SERVER_URL); \
	fi
	@echo "Downloading $(GPHOTO2) from $(GPHOTO2_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: gphoto2-unpacked

gphoto2-unpacked: $(GPHOTO2_DIR)/.gphoto2_unpacked

$(GPHOTO2_DIR)/.gphoto2_unpacked: $(GPHOTO2_DIR)/.gphoto2_downloaded $(GPHOTO2_SOURCE)/$(GPHOTO2).tar.gz
	@echo "Unpacking $(GPHOTO2) ..."
	if [ -d "$(GPHOTO2_SOURCE)/$(GPHOTO2)" ]; then \
		rm -fr $(GPHOTO2_SOURCE)/$(GPHOTO2); \
	fi
	cd $(GPHOTO2_SOURCE); tar xzvf $(GPHOTO2).tar.gz
	@echo "Unpacking $(GPHOTO2) done"
	@touch $@


#
# Patch the source
#
.PHONY: gphoto2-patched

gphoto2-patched: $(GPHOTO2_DIR)/.gphoto2_patched

$(GPHOTO2_DIR)/.gphoto2_patched: $(GPHOTO2_DIR)/.gphoto2_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: gphoto2-config

gphoto2-config: 

#
# Configuration
#
.PHONY: gphoto2-configured

gphoto2-configured:  gphoto2-config $(GPHOTO2_DIR)/.gphoto2_configured

$(GPHOTO2_DIR)/.gphoto2_configured: $(GPHOTO2_DIR)/.gphoto2_patched $(GPHOTO2_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(GPHOTO2) ..."
	#cd $(GPHOTO2_SOURCE)/$(GPHOTO2);./configure  --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)  CFLAGS=" -I$(LIBS_INSTALL_PATH)/include/" LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib/" LIBUSB_LIBS="-lusb -I$(LIBS_INSTALL_PATH)/include/" LIBUSB_CFLAGS="-lusb -L$(LIBS_INSTALL_PATH)/lib/" PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" LIBUSB_CONFIG="$(LIBS_INSTALL_PATH)/bin" --enable-shared=yes 
	cd $(GPHOTO2_SOURCE)/$(GPHOTO2);./configure  --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" POPT_LIBS="-L$(LIBS_INSTALL_PATH)/lib/ -lpopt" POPT_CFLAGS=-I$(LIBS_INSTALL_PATH)/include/ 
       	
	@echo "Configuring $(GPHOTO2) done"
	@touch $@

#
# Compile
#
.PHONY: gphoto2-compile

gphoto2-compile: $(GPHOTO2_DIR)/.gphoto2_compiled

$(GPHOTO2_DIR)/.gphoto2_compiled: $(GPHOTO2_DIR)/.gphoto2_configured
	@echo "Compiling $(GPHOTO2) ..."
	#make -C $(GPHOTO2_SOURCE)/$(GPHOTO2) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(GPHOTO2_SOURCE)/$(GPHOTO2) 
	make -C $(GPHOTO2_SOURCE)/$(GPHOTO2)  install
	@echo "Compiling $(GPHOTO2) done"
	@touch $@

#
# Update
#
.PHONY: gphoto2-update

gphoto2-update:
	@echo "Updating $(GPHOTO2) ..."
	@if [ -d "$(GPHOTO2_SOURCE)" ]; then\
		$(TOP_UPDATE) $(GPHOTO2_SOURCE); \
	fi
	@echo "Updating $(GPHOTO2) done"

#
# Status
#
.PHONY: gphoto2-status

gphoto2-status:
	@echo "Statusing $(GPHOTO2) ..."
	@if [ -d "$(GPHOTO2_SOURCE)" ]; then\
		$(TOP_STATUS) $(GPHOTO2_SOURCE); \
	fi
	@echo "Statusing $(GPHOTO2) done"

#
# Clean
#
.PHONY: gphoto2-clean

gphoto2-clean:
	@rm -f $(GPHOTO2_DIR)/.gphoto2_configured
	@if [ -d "$(GPHOTO2_SOURCE)" ]; then\
		make -C $(GPHOTO2_SOURCE)/$(GPHOTO2) clean; \
	fi

#
# Dist clean
#
.PHONY: gphoto2-distclean

gphoto2-distclean:
	@rm -f $(GPHOTO2_DIR)/.gphoto2_*

#
# Install
#
.PHONY: gphoto2-install

gphoto2-install:
	cp -f $(LIBS_INSTALL_PATH)/bin/gphoto2 $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/bin/gphoto2
	





