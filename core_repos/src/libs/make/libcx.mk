##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  steven_kuo@alphanetworks.com
# libcx makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBCX_VERSION 
CONF_LIBCX_VERSION := 1.1.1
endif

LIBCX			:= libcx-$(CONF_LIBCX_VERSION)-devel#
LIBCX_SERVER_URL	:= $(TOP_LIBS_URL)/libcx/$(LIBCX)
LIBCX_DIR		:= $(TOP_LIBS_DIR)#
LIBCX_SOURCE		:= $(LIBCX_DIR)/$(LIBCX)
LIBCX_CONFIG		:= 

#
# Download  the source 
#
.PHONY: libcx-downloaded

libcx-downloaded: $(LIBCX_DIR)/.libcx_downloaded

$(LIBCX_DIR)/.libcx_downloaded:
	@echo "Downloading $(LIBCX) from $(LIBCX_SERVER_URL) ..."
	@if [ ! -d "$(LIBCX_SOURCE)" ]; then \
		cd $(LIBCX_DIR); \
		$(TOP_DOWNLOAD) $(LIBCX_SERVER_URL); \
	fi
	@echo "Downloading $(LIBCX) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libcx-unpacked

libcx-unpacked: $(LIBCX_DIR)/.libcx_unpacked

$(LIBCX_DIR)/.libcx_unpacked: $(LIBCX_DIR)/.libcx_downloaded $(LIBCX_SOURCE)/$(LIBCX).tar.bz2
	@echo "Unpacking $(LIBCX) ..."
	if [ -d "$(LIBCX_SOURCE)/$(LIBCX)" ]; then \
		rm -fr  $(LIBCX_SOURCE)/$(LIBCX); \
	fi
	cd $(LIBCX_SOURCE); tar jxvf $(LIBCX).tar.bz2
	@echo "Unpacking $(LIBCX) done"
	@touch $@


#
# Patch the source
#
.PHONY: libcx-patched

libcx-patched: $(LIBCX_DIR)/.libcx_patched

$(LIBCX_DIR)/.libcx_patched: $(LIBCX_DIR)/.libcx_unpacked
	# Patching...
	cd $(LIBCX_SOURCE)/$(LIBCX); patch -p0 ./src/basic/list.c < ../$(LIBCX).patch; patch -p0 ./src/basic/list.c < ../$(LIBCX).patch2
	@touch $@

#
# config
#
.PHONY: libcx-config

libcx-config: 

#
# Configuration
#
.PHONY: libcx-configured

libcx-configured:  libcx-config $(LIBCX_DIR)/.libcx_configured

$(LIBCX_DIR)/.libcx_configured: $(LIBCX_DIR)/.libcx_patched $(LIBCX_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configring  $(LIBCX) ..."
	cd $(LIBCX_SOURCE)/$(LIBCX);./configure --prefix=$(LIBS_INSTALL_PATH) --includedir=$(LIBS_INSTALL_PATH)include/libcx --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-L$(LIBS_INSTALL_PATH)lib"
	@echo "Configring  $(LIBCX) done" 
	@touch $@

#
# Compile
#
.PHONY: libcx-compile

libcx-compile: $(LIBCX_DIR)/.libcx_compiled

$(LIBCX_DIR)/.libcx_compiled: $(LIBCX_DIR)/.libcx_configured
	@echo "Compiling $(LIBCX) ..." 
	make -C $(LIBCX_SOURCE)/$(LIBCX) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS="-I$(LIBS_INSTALL_PATH)/include"
	make -C $(LIBCX_SOURCE)/$(LIBCX) install
	@echo "Compiling $(LIBCX) done"
	@touch $@
#
# Update
#
.PHONY: libcx-update

libcx-update:
	@echo "Updating $(LIBCX) ..."
	@if [ -d "$(LIBCX_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBCX_SOURCE); \
	fi
	@echo "Updating $(LIBCX) done"

#
# Status
#
.PHONY: libcx-status

libcx-status:
	@echo "Statusing $(LIBCX) ..."
	@if [ -d "$(LIBCX_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBCX_SOURCE); \
	fi
	@echo "Statusing $(LIBCX) done"

#
# Clean
#
.PHONY: libcx-clean

libcx-clean:
	@rm -f $(LIBCX_DIR)/.libcx_configured
	@if [ -d "$(LIBCX_SOURCE)" ]; then\
		make -C $(LIBCX_SOURCE)/$(LIBCX) clean; \
	fi

#
# Dist clean
#
.PHONY: libcx-distclean

libcx-distclean:
	@rm -f $(LIBCX_DIR)/.libcx_*

#
# Install
#
.PHONY: libcx-install

libcx-install:
