##############################################################################
# Copyright (C) tw.idv.coolshou 2015-- 
# All Rights Reserved -- 
# Author:  jimmy
# DirectFB makefile fragments 
##############################################################################

#
# Defines
#
ifndef  DIRECTFB_VERSION 
CONF_DIRECTFB_VERSION := 1.2.10
endif

DIRECTFB             := DirectFB-$(CONF_DIRECTFB_VERSION)
DIRECTFB_SERVER_URL  := $(TOP_LIBS_URL)/directfb/$(DIRECTFB)/
DIRECTFB_DIR         := $(TOP_LIBS_DIR)
DIRECTFB_SOURCE      := $(DIRECTFB_DIR)/$(DIRECTFB)
DIRECTFB_CONFIG      := 

#	CFLAGS=-I$(LIBS_INSTALL_PATH)/include 
#	LDFLAGS=-L$(LIBS_INSTALL_PATH)/lib 

DIRECTFB_CONFIGURE := CROSS=mips-linux-gnu- CROSS_COMPILER_FLAGS=-EL \
	LDFLAGS="-L$(LIBS_INSTALL_PATH)lib" \
	CFLAGS="-I$(LIBS_INSTALL_PATH)include" \
	FREETYPE_CFLAGS="-I$(LIBS_INSTALL_PATH)include/freetype2/" \
	FREETYPE_LIBS="-L$(LIBS_INSTALL_PATH)libs" \
	./configure --prefix=$(LIBS_INSTALL_PATH) \
	--build=$(BUILD_HOST) \
	--host=$(BUILD_TARGET) --target=$(BUILD_TARGET) \
	--enable-video4linux2 \
	--with-gfxdrivers=none --with-inputdrivers=all \
	--enable-png --enable-jpeg --enable-tiff --enable-zlib \
	--enable-sdl=no --enable-gif=no \
	--disable-x11 --disable-osx --disable-sysfs --disable-vnc \
	--enable-debug --sysconfdir=/etc --enable-fbdev \
	--without-tests --without-tools
	
#
# Download  the source 
#
.PHONY: directfb-downloaded

directfb-downloaded: $(DIRECTFB_DIR)/.directfb_downloaded

$(DIRECTFB_DIR)/.directfb_downloaded:
	touch $@

#
# Unpack the source
#
.PHONY: directfb-unpacked

directfb-unpacked:  $(DIRECTFB_DIR)/.directfb_unpacked

$(DIRECTFB_DIR)/.directfb_unpacked: $(DIRECTFB_DIR)/.directfb_downloaded
	@if [ ! -d "$(DIRECTFB_SOURCE)$(DIRECTFB)" ]; then \
		cd $(DIRECTFB_SOURCE); \
		tar -zxvf $(DIRECTFB_SOURCE)/$(DIRECTFB).tar.gz;	\
	fi
	@touch $@


#
# Patch the source
#
.PHONY: directfb-patched

directfb-patched:  $(DIRECTFB_DIR)/.directfb_patched

$(DIRECTFB_DIR)/.directfb_patched: $(DIRECTFB_DIR)/.directfb_unpacked
	cd $(DIRECTFB_SOURCE)/$(DIRECTFB); patch -p1 < $(DIRECTFB_SOURCE)/makefile_am.patch
	cd $(DIRECTFB_SOURCE)/$(DIRECTFB); patch -p1 < $(DIRECTFB_SOURCE)/makefile_in.patch
	touch $@


#
# config
#
.PHONY: directfb-config

directfb-config: 

#
# Configuration
#
.PHONY: directfb-configured

directfb-configured:  $(DIRECTFB_DIR)/.directfb_configured

$(DIRECTFB_DIR)/.directfb_configured: $(DIRECTFB_DIR)/.directfb_patched
	@echo "Configured $(DIRECTFB) ..."
	(declare +x CROSS_COMPILE;cd $(DIRECTFB_SOURCE)/$(DIRECTFB); $(DIRECTFB_CONFIGURE))
	@echo "Configured $(DIRECTFB) done"
	@touch $@

#
# Compile
#
.PHONY: directfb-compile

directfb-compile:  $(DIRECTFB_DIR)/.directfb_compiled

$(DIRECTFB_DIR)/.directfb_compiled: $(DIRECTFB_DIR)/.directfb_configured
	@echo "Compiling $(DIRECTFB) ..."
	make -C $(DIRECTFB_SOURCE)/$(DIRECTFB)
	make -C $(DIRECTFB_SOURCE)/$(DIRECTFB) install
	@echo "Compiling $(DIRECTFB) done"
	@touch $@

#
# Update
#
.PHONY: directfb-update

directfb-update:
	@echo "Updating $(DIRECTFB) done"

#
# Status
#
.PHONY: directfb-status

ftpd-status:
	@echo "Statusing $(DIRECTFB) done"

#
# Clean
#
.PHONY: directfb-clean

directfb-clean:
	@if [ -d "$(DIRECTFB_SOURCE)" ]; then\
		make -C $(DIRECTFB_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: directfb-distclean

directfb-distclean:
	rm -f $(TOP_LIBS_DIR)/.directfb*

#
# Install
#
.PHONY: directfb-install

directfb-install:


