##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# tiff makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_TIFF_VERSION 
CONF_TIFF_VERSION := 3.7.1
endif

TIFF             := tiff-$(CONF_TIFF_VERSION)#
TIFF_SERVER_URL  := $(TOP_LIBS_URL)/tiff/$(TIFF)
TIFF_DIR         := $(TOP_LIBS_DIR)#
TIFF_SOURCE      := $(TIFF_DIR)/$(TIFF)
TIFF_CONFIG      := 

#To be compatible with the arm toolchain which renamed the arm-elf-cpp with cpp, 
# add following code to support cross platform
ifneq ($(strip $(wildcard $(CROSS)cpp)),)
	CROSS_CPP 	:=  $(CROSS)cpp
else
	CROSS_CPP 	:=  $(CROSS_PREFIX)/bin/cpp
endif

#
# Download  the source 
#
.PHONY: tiff-downloaded

tiff-downloaded: $(TIFF_DIR)/.tiff_downloaded

$(TIFF_DIR)/.tiff_downloaded:
	@echo "Downloading $(TIFF) from $(TIFF_SERVER_URL) ..."
	@if [ ! -d "$(TIFF_SOURCE)" ]; then \
		cd $(TIFF_DIR); \
		$(TOP_DOWNLOAD) $(TIFF_SERVER_URL); \
	fi
	@echo "Downloading $(TIFF) done"
	@touch $@

#
# Unpack the source
#
.PHONY: tiff-unpacked

tiff-unpacked: $(TIFF_DIR)/.tiff_unpacked

$(TIFF_DIR)/.tiff_unpacked: $(TIFF_DIR)/.tiff_downloaded $(wildcard $(TIFF_SOURCE)/*.tgz)
	@echo "Unpacking $(TIFF) ..."
	if [ -d "$(TIFF_SOURCE)/$(TIFF)" ]; then \
		rm -fr $(TIFF_SOURCE)/$(TIFF); \
	fi
	cd $(TIFF_SOURCE);tar zxvf  $(TIFF).tgz
	@echo "Unpacking $(TIFF) done"
	@touch $@


#
# Patch the source
#
.PHONY: tiff-patched

tiff-patched: $(TIFF_DIR)/.tiff_patched

$(TIFF_DIR)/.tiff_patched: $(TIFF_DIR)/.tiff_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: tiff-config

tiff-config: 

#
# Configuration
#
.PHONY: tiff-configured

tiff-configured:  tiff-config $(TIFF_DIR)/.tiff_configured

$(TIFF_DIR)/.tiff_configured: $(TIFF_DIR)/.tiff_patched $(TIFF_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(TIFF) ..."
	cd $(TIFF_SOURCE)/$(TIFF);./configure --prefix=$(LIBS_INSTALL_PATH)/lib --libdir=$(LIBS_INSTALL_PATH)/lib \
            --includedir=$(LIBS_INSTALL_PATH)/include \
	    --oldincludedir=$(LIBS_INSTALL_PATH)/include \
	    --build=$(BUILD_HOST) \
	    --host=$(BUILD_TARGET) \
	    --target=$(BUILD_TARGET) \
	    --enable-shared=$(ENABLE_SHLIB) \
	    --enable-FEATURE=yes \
	    --disable-libtool-lock \
	    --disable-rpath \
	    --disable-old-jpeg \
	    --disable-jpeg \
            CC=$(CC)\
	    CPP=$(CROSS_CPP) \
	    CXX=$(CROSS)g++ \
	    CXXFLAGS=-I$(CROSS_PREFIX)/include \
	    CXXCPP=$(CROSS_CPP)
	@echo "Configuring $(TIFF) done"
	@touch $@

#
# Compile
#
.PHONY: tiff-compile

tiff-compile: $(TIFF_DIR)/.tiff_compiled

$(TIFF_DIR)/.tiff_compiled: $(TIFF_DIR)/.tiff_configured
	@echo "Compiling $(TIFF) ..."
	make -C $(TIFF_SOURCE)/$(TIFF)  CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(TIFF_SOURCE)/$(TIFF)  install
	@echo "Compiling $(TIFF) done"
	@touch $@

#
# Update
#
.PHONY: tiff-update

tiff-update:
	@echo "Updating $(TIFF) ..."
	@if [ -d "$(TIFF_SOURCE)" ]; then\
		$(TOP_UPDATE) $(TIFF_SOURCE); \
	fi
	@echo "Updating $(TIFF) done"

#
# Status
#
.PHONY: tiff-status

tiff-status:
	@echo "Statusing $(TIFF) ..."
	@if [ -d "$(TIFF_SOURCE)" ]; then\
		$(TOP_STATUS) $(TIFF_SOURCE); \
	fi
	@echo "Statusing $(TIFF) done"

#
# Clean
#
.PHONY: tiff-clean

tiff-clean:
	@rm -f $(TIFF_DIR)/.tiff_configured
	@if [ -d "$(TIFF_SOURCE)" ]; then\
		make -C $(TIFF_SOURCE)/$(TIFF) clean; \
	fi

#
# Dist clean
#
.PHONY: tiff-distclean

tiff-distclean:
	@rm -f $(TIFF_DIR)/.tiff_*

#
# Install
#
.PHONY: tiff-install

tiff-install:
