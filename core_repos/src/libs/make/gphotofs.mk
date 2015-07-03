##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# gphotofs makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_GPHOTOFS_VERSION 
CONF_GPHOTOFS_VERSION := 0.4.0
endif

GPHOTOFS             := gphotofs-$(CONF_GPHOTOFS_VERSION)#
GPHOTOFS_SERVER_URL  := $(TOP_LIBS_URL)/gphotofs/$(GPHOTOFS)
GPHOTOFS_DIR         := $(TOP_LIBS_DIR)#
GPHOTOFS_SOURCE      := $(GPHOTOFS_DIR)/$(GPHOTOFS)
GPHOTOFS_CONFIG      := 

#
# Download  the source 
#
.PHONY: gphotofs-downloaded

gphotofs-downloaded: $(GPHOTOFS_DIR)/.gphotofs_downloaded

$(GPHOTOFS_DIR)/.gphotofs_downloaded:
	@echo "Downloading $(GPHOTOFS) from $(GPHOTOFS_SERVER_URL) ..."
	@if [ ! -d "$(GPHOTOFS_SOURCE)" ]; then \
		cd $(GPHOTOFS_DIR); \
		$(TOP_DOWNLOAD) $(GPHOTOFS_SERVER_URL); \
	fi
	@echo "Downloading $(GPHOTOFS) from $(GPHOTOFS_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: gphotofs-unpacked

gphotofs-unpacked: $(GPHOTOFS_DIR)/.gphotofs_unpacked

$(GPHOTOFS_DIR)/.gphotofs_unpacked: $(GPHOTOFS_DIR)/.gphotofs_downloaded $(GPHOTOFS_SOURCE)/$(GPHOTOFS).tar.bz2
	@echo "Unpacking $(GPHOTOFS) ..."
	if [ -d "$(GPHOTOFS_SOURCE)/$(GPHOTOFS)" ]; then \
		rm -fr $(GPHOTOFS_SOURCE)/$(GPHOTOFS); \
	fi
	cd $(GPHOTOFS_SOURCE); tar jxvf $(GPHOTOFS).tar.bz2
	@echo "Unpacking $(GPHOTOFS) done"
	@touch $@


#
# Patch the source
#
.PHONY: gphotofs-patched

gphotofs-patched: $(GPHOTOFS_DIR)/.gphotofs_patched

$(GPHOTOFS_DIR)/.gphotofs_patched: $(GPHOTOFS_DIR)/.gphotofs_unpacked
	# Patching...
	cd $(GPHOTOFS_SOURCE);patch -p0 < gphoto_lc_cytype.patch 
ifeq (x$(CONF_PTP_EXPORT_ONLY_IMAGE),xy)
	cd $(GPHOTOFS_SOURCE);patch -p0 < filter_out_non_image.patch 
endif
	@touch $@

#
# config
#
.PHONY: gphotofs-config

gphotofs-config: 

#
# Configuration
#
.PHONY: gphotofs-configured

gphotofs-configured:  gphotofs-config $(GPHOTOFS_DIR)/.gphotofs_configured

$(GPHOTOFS_DIR)/.gphotofs_configured: $(GPHOTOFS_DIR)/.gphotofs_patched $(GPHOTOFS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(GPHOTOFS) ..."
	cd $(GPHOTOFS_SOURCE)/$(GPHOTOFS);./configure  --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) POPT_LIBS="-lpopt -I$(LIBS_INSTALL_PATH)/include/" POPT_CFLAGS="-L$(LIBS_INSTALL_PATH)/lib/" PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" CFLAGS=" -I$(LIBS_INSTALL_PATH)/include/ -I$(LIBS_INSTALL_PATH)/include/glib-2.0 -I$(LIBS_INSTALL_PATH)/lib/glib-2.0/include" 
	@echo "Configuring $(GPHOTOFS) done"
	@touch $@

#
# Compile
#
.PHONY: gphotofs-compile

gphotofs-compile: $(GPHOTOFS_DIR)/.gphotofs_compiled

$(GPHOTOFS_DIR)/.gphotofs_compiled: $(GPHOTOFS_DIR)/.gphotofs_configured
	@echo "Compiling $(GPHOTOFS) ..."
	#make -C $(GPHOTOFS_SOURCE)/$(GPHOTOFS) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(GPHOTOFS_SOURCE)/$(GPHOTOFS) 
	make -C $(GPHOTOFS_SOURCE)/$(GPHOTOFS)  install
	@echo "Compiling $(GPHOTOFS) done"
	@touch $@

#
# Update
#
.PHONY: gphotofs-update

gphotofs-update:
	@echo "Updating $(GPHOTOFS) ..."
	@if [ -d "$(GPHOTOFS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(GPHOTOFS_SOURCE); \
	fi
	@echo "Updating $(GPHOTOFS) done"

#
# Status
#
.PHONY: gphotofs-status

gphotofs-status:
	@echo "Statusing $(GPHOTOFS) ..."
	@if [ -d "$(GPHOTOFS_SOURCE)" ]; then\
		$(TOP_STATUS) $(GPHOTOFS_SOURCE); \
	fi
	@echo "Statusing $(GPHOTOFS) done"

#
# Clean
#
.PHONY: gphotofs-clean

gphotofs-clean:
	@rm -f $(GPHOTOFS_DIR)/.gphotofs_configured
	@if [ -d "$(GPHOTOFS_SOURCE)" ]; then\
		make -C $(GPHOTOFS_SOURCE)/$(GPHOTOFS) clean; \
	fi

#
# Dist clean
#
.PHONY: gphotofs-distclean

gphotofs-distclean:
	@rm -f $(GPHOTOFS_DIR)/.gphotofs_*

#
# Install
#
.PHONY: gphotofs-install

gphotofs-install:
	cp -f $(LIBS_INSTALL_PATH)/bin/gphotofs $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/bin/gphotofs
