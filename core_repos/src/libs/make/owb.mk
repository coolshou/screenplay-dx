##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# owb makefile fragments 
##############################################################################

#
# Defines
#


ifndef  CONF_OWB_VERSION 
CONF_OWB_VERSION := 16jun10#Sigma_OWB_src[1].16jun10
endif

SIGMA_SDK_SOURCE	:= $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)

OWB               := OWB
OWB_SUPPORT	  := OWB-Support
OWB_DIR         := $(SIGMA_SDK_SOURCE)/owb
OWB_SOURCE      := Sigma_OWB_src[1].$(CONF_OWB_VERSION)
OWB_SOURCE_DIR	:= $(OWB_DIR)/owb

#To be compatible with the arm toolchain which renamed the arm-elf-cpp with cpp, 
# add following code to support cross platform
ifneq ($(strip $(wildcard $(CROSS)cpp)),)
	CROSS_CPP 	:=  $(CROSS)cpp
else
	CROSS_CPP 	:=  $(CROSS_PREFIX)/bin/cpp
endif

CONFIGTOOL_PATH := $(SIGMA_SDK_SOURCE)/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/directfb/bin/:$(PATH)
export PATH=$(CONFIGTOOL_PATH)

#
# Download  the source 
#
.PHONY: owb-downloaded

owb-downloaded: $(TOP_LIBS_DIR)/.owb_downloaded

$(TOP_LIBS_DIR)/.owb_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: owb-unpacked

owb-unpacked: $(TOP_LIBS_DIR)/.owb_unpacked

$(TOP_LIBS_DIR)/.owb_unpacked: $(OWB_DIR)/$(OWB_SOURCE).tbz
	@echo "Unpacking $(CONF_OWB_VERSION) ..."
	if [ -d "$(OWB_SOURCE_DIR)/$(OWB)" ]; then \
		rm -fr $(OWB_SOURCE_DIR)/$(OWB); \
	fi
	if [ -d "$(OWB_SOURCE_DIR)/$(OWB_SUPPORT)" ]; then \
		rm -fr $(OWB_SOURCE_DIR)/$(OWB_SUPPORT); \
	fi
	mkdir -p $(OWB_SOURCE_DIR)
	cd $(OWB_DIR);tar vxf $(OWB_SOURCE).tbz -C $(OWB_SOURCE_DIR)
	@echo "Unpacking $(OWB_SOURCE) done"
	@touch $@


#
# Patch the source
#
.PHONY: owb-patched

owb-patched: $(TOP_LIBS_DIR)/.owb_patched

$(TOP_LIBS_DIR)/.owb_patched: $(TOP_LIBS_DIR)/.owb_unpacked
	# Patching...
	cd $(OWB_DIR); patch -p0 < owb-support-makefile_001.patch
	cd $(OWB_DIR); patch -p0 < owb-cmakelists_001.patch
	cd $(OWB_DIR); patch -p0 < owb-cmake-checkplatformfonts_001.patch
	cd $(OWB_DIR); patch -p0 < webkittools-owblauncher-cmakelists_001.patch
#	cd $(OWB_DIR); patch -p0 < sdl-include-SDL_001.patch
#	cd $(OWB_DIR); patch -p0 < sdl-src-SDL_001.patch
#	cd $(OWB_DIR); patch -p0 < sdl-src-audio-SDLaudio_001.patch
#	cd $(OWB_DIR); patch -p0 < sdl-src-video-SDLsysvideo_001.patch
#	cd $(OWB_DIR); patch -p0 < sdl-src-video-directfb-SDLdfbVideo_001.patch

	@touch $@

#
# config
#
.PHONY: owb-config

owb-config: 

#
# Configuration
#
.PHONY: owb-configured

owb-configured:  owb-config $(TOP_LIBS_DIR)/.owb_configured

$(TOP_LIBS_DIR)/.owb_configured: $(TOP_LIBS_DIR)/.owb_patched $(TOP_CURRENT_SET)
	@echo "Configuring $(OWB) ..."
	@echo "Configuring $(OWB) done"
	@touch $@

#
# Compile
#
.PHONY: owb-compile


owb-compile: $(TOP_LIBS_DIR)/.owb_compiled

$(TOP_LIBS_DIR)/.owb_compiled: $(TOP_LIBS_DIR)/.owb_configured
	@echo "Compiling $(OWB) ..."
	make OWB_SOURCE_DIR=$(OWB_SOURCE_DIR) SIGMA_RUA_SDK=$(CONF_SIGMA_RUA_SDK) -C $(OWB_SOURCE_DIR)/$(OWB_SUPPORT)
	@echo "Compiling $(OWB) done"
	@touch $@

#
# Update
#
.PHONY: owb-update

owb-update:
	@echo "Updating $(OWB) ..."
	@if [ -d "$(OWB_SOURCE_DIR)" ]; then\
		$(TOP_UPDATE) $(OWB_SOURCE_DIR); \
	fi
	@echo "Updating $(OWB) done"

#
# Status
#
.PHONY: owb-status

owb-status:
	@echo "Statusing $(OWB) ..."
	@if [ -d "$(OWB_SOURCE_DIR)" ]; then\
		$(TOP_STATUS) $(OWB_SOURCE_DIR); \
	fi
	@echo "Statusing $(OWB) done"

#
# Clean
#
.PHONY: owb-clean

owb-clean:
	@rm -f $(TOP_LIBS_DIR)/.owb_configured
	@if [ -d "$(OWB_SOURCE_DIR)/$(OWB_SUPPORT)" ]; then\
		make -C $(OWB_SOURCE_DIR)/$(OWB_SUPPORT) clean; \
	fi

#
# Dist clean
#
.PHONY: owb-distclean

owb-distclean:
	@rm -f $(TOP_LIBS_DIR)/.owb_*

#
# Install
#
.PHONY: owb-install

owb-install:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/owb/
	cp -rf $(OWB_DIR)/mrua/ $(TOP_INSTALL_ROOTFS_DIR)/owb/
	mv $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/usr/local/lib/*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib/
#	mv $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/usr/local/bin/* $(TOP_INSTALL_ROOTFS_DIR)/bin/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/sigmaset/mrua/usr/local/share/fonts
	cp $(OWB_DIR)/decker.ttf $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/sigmaset/mrua/usr/local/share/fonts
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/usr/local/lib/adobe/
	cp $(OWB_DIR)/libflashplayer.so $(TOP_INSTALL_ROOTFS_DIR)/owb/mrua/usr/local/lib/adobe/

