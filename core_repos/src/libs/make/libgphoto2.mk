##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# libgphoto2 makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBGPHOTO2_VERSION 
CONF_LIBGPHOTO2_VERSION := 2.4.4
endif

LIBGPHOTO2             := libgphoto2-$(CONF_LIBGPHOTO2_VERSION)#
LIBGPHOTO2_SERVER_URL  := $(TOP_LIBS_URL)/libgphoto2/$(LIBGPHOTO2)
LIBGPHOTO2_DIR         := $(TOP_LIBS_DIR)#
LIBGPHOTO2_SOURCE      := $(LIBGPHOTO2_DIR)/$(LIBGPHOTO2)
LIBGPHOTO2_CONFIG      := 

#
# Download  the source 
#
.PHONY: libgphoto2-downloaded

libgphoto2-downloaded: $(LIBGPHOTO2_DIR)/.libgphoto2_downloaded

$(LIBGPHOTO2_DIR)/.libgphoto2_downloaded:
	@echo "Downloading $(LIBGPHOTO2) from $(LIBGPHOTO2_SERVER_URL) ..."
	@if [ ! -d "$(LIBGPHOTO2_SOURCE)" ]; then \
		cd $(LIBGPHOTO2_DIR); \
		$(TOP_DOWNLOAD) $(LIBGPHOTO2_SERVER_URL); \
	fi
	@echo "Downloading $(LIBGPHOTO2) from $(LIBGPHOTO2_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libgphoto2-unpacked

libgphoto2-unpacked: $(LIBGPHOTO2_DIR)/.libgphoto2_unpacked

$(LIBGPHOTO2_DIR)/.libgphoto2_unpacked: $(LIBGPHOTO2_DIR)/.libgphoto2_downloaded $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2).tar.bz2
	@echo "Unpacking $(LIBGPHOTO2) ..."
	if [ -d "$(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2)" ]; then \
		rm -fr $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2); \
	fi
	cd $(LIBGPHOTO2_SOURCE); tar jxvf $(LIBGPHOTO2).tar.bz2
	@echo "Unpacking $(LIBGPHOTO2) done"
	@touch $@


#
# Patch the source
#
.PHONY: libgphoto2-patched

libgphoto2-patched: $(LIBGPHOTO2_DIR)/.libgphoto2_patched

$(LIBGPHOTO2_DIR)/.libgphoto2_patched: $(LIBGPHOTO2_DIR)/.libgphoto2_unpacked
	# Patching...
	@echo "Patching $(LIBGPHOTO2) ..."
	cd $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2);patch -p0 < ../$(LIBGPHOTO2).patch;patch -p0 < ../$(LIBGPHOTO2).patch2
	@echo "Patching $(LIBGPHOTO2) done"
	@touch $@

#
# config
#
.PHONY: libgphoto2-config

libgphoto2-config: 

#
# Configuration
#
.PHONY: libgphoto2-configured

libgphoto2-configured:  libgphoto2-config $(LIBGPHOTO2_DIR)/.libgphoto2_configured

$(LIBGPHOTO2_DIR)/.libgphoto2_configured: $(LIBGPHOTO2_DIR)/.libgphoto2_patched $(LIBGPHOTO2_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBGPHOTO2) ..."
	cd $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2);./configure  --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)  CFLAGS=" -I$(LIBS_INSTALL_PATH)/include/" LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib/" LIBUSB_LIBS="-lusb -I$(LIBS_INSTALL_PATH)/include/" LIBUSB_CFLAGS="-lusb -L$(LIBS_INSTALL_PATH)/lib/" PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" LIBUSB_CONFIG="$(LIBS_INSTALL_PATH)/bin" --enable-shared=yes 
       	
	@echo "Configuring $(LIBGPHOTO2) done"
	@touch $@

#
# Compile
#
.PHONY: libgphoto2-compile

libgphoto2-compile: $(LIBGPHOTO2_DIR)/.libgphoto2_compiled

$(LIBGPHOTO2_DIR)/.libgphoto2_compiled: $(LIBGPHOTO2_DIR)/.libgphoto2_configured
	@echo "Compiling $(LIBGPHOTO2) ..."
	#make -C $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2) 
	make -C $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2)  install
	@echo "Compiling $(LIBGPHOTO2) done"
	@touch $@

#
# Update
#
.PHONY: libgphoto2-update

libgphoto2-update:
	@echo "Updating $(LIBGPHOTO2) ..."
	@if [ -d "$(LIBGPHOTO2_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBGPHOTO2_SOURCE); \
	fi
	@echo "Updating $(LIBGPHOTO2) done"

#
# Status
#
.PHONY: libgphoto2-status

libgphoto2-status:
	@echo "Statusing $(LIBGPHOTO2) ..."
	@if [ -d "$(LIBGPHOTO2_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBGPHOTO2_SOURCE); \
	fi
	@echo "Statusing $(LIBGPHOTO2) done"

#
# Clean
#
.PHONY: libgphoto2-clean

libgphoto2-clean:
	@rm -f $(LIBGPHOTO2_DIR)/.libgphoto2_configured
	@if [ -d "$(LIBGPHOTO2_SOURCE)" ]; then\
		make -C $(LIBGPHOTO2_SOURCE)/$(LIBGPHOTO2) clean; \
	fi

#
# Dist clean
#
.PHONY: libgphoto2-distclean

libgphoto2-distclean:
	@rm -f $(LIBGPHOTO2_DIR)/.libgphoto2_*

#
# Install
#
.PHONY: libgphoto2-install

libgphoto2-install:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc
	cp $(LIBGPHOTO2_SOURCE)/idlist $(TOP_INSTALL_ROOTFS_DIR)/etc  
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/lib/libgphoto2
	cp -fra $(LIBS_INSTALL_PATH)/lib/libgphoto2/$(CONF_LIBGPHOTO2_VERSION)/*.so $(TOP_INSTALL_ROOTFS_DIR)/lib/libgphoto2 
	cp -fra $(LIBS_INSTALL_PATH)/lib/libgphoto2_port/0.8.0/*.so $(TOP_INSTALL_ROOTFS_DIR)/lib/libgphoto2 
	





