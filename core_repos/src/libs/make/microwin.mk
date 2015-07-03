##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# microwin makefile fragments 
##############################################################################

#
# Defines
#

MICROWIN             := microwin-$(CONF_MICROWIN_VERSION)#
MICROWIN_SERVER_URL  := $(TOP_LIBS_URL)/microwin/$(MICROWIN)
MICROWIN_DIR         := $(TOP_LIBS_DIR)#
MICROWIN_SOURCE      := $(MICROWIN_DIR)/$(MICROWIN)
MICROWIN_CONFIG      := $(TOP_CONFIG_DIR)/$(CONF_MICROWIN_CONFIG)


#
# Download  the source 
#
.PHONY: microwin-downloaded

microwin-downloaded: $(MICROWIN_DIR)/.microwin_downloaded

$(MICROWIN_DIR)/.microwin_downloaded:
	@echo "Downloading $(MICROWIN) from $(MICROWIN_SERVER_URL) ..."
	@if [ ! -d "$(MICROWIN_SOURCE)" ]; then \
		cd $(MICROWIN_DIR); \
		$(TOP_DOWNLOAD) $(MICROWIN_SERVER_URL); \
	fi
	@echo "Downloading $(MICROWIN) done"
	@touch $@

#
# Unpack the source
#
.PHONY: microwin-unpacked

microwin-unpacked: $(MICROWIN_DIR)/.microwin_unpacked

$(MICROWIN_DIR)/.microwin_unpacked: $(MICROWIN_DIR)/.microwin_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: microwin-patched

microwin-patched: $(MICROWIN_DIR)/.microwin_patched

$(MICROWIN_DIR)/.microwin_patched: $(MICROWIN_DIR)/.microwin_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: microwin-config

microwin-config: 

#
# Configuration
#
.PHONY: microwin-configured

microwin-configured:  microwin-config $(MICROWIN_DIR)/.microwin_configured

$(MICROWIN_DIR)/.microwin_configured: $(MICROWIN_DIR)/.microwin_patched $(MICROWIN_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(MICROWIN) ..."
	@if [ -f $(MICROWIN_CONFIG) ]; then \
		cp -pf $(MICROWIN_CONFIG) $(MICROWIN_SOURCE)/src/config; \
	fi
ifeq (x$(PLATFORM_X86),xy)
	sed -i -e "s/^ARCH.*/ARCH=LINUX-NATIVE/" $(MICROWIN_SOURCE)/src/config
	sed -i -e "s/^X11.*/X11=Y/" $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_DMA_FONT_FREETYPE), y)
	sed -i -e "s/^HAVE_FREETYPE_SUPPORT.*/HAVE_FREETYPE_SUPPORT=Y/" $(MICROWIN_SOURCE)/src/config 
else
	sed -i -e "s/^HAVE_FREETYPE_SUPPORT.*/HAVE_FREETYPE_SUPPORT=N/" $(MICROWIN_SOURCE)/src/config 
endif
ifeq ($(CONF_DMA_HD_UI_SUPPORT), y)
	echo "JPG_DECODE_BUF_WIDTH=1280" >> $(MICROWIN_SOURCE)/src/config
	echo "JPG_DECODE_BUF_HEIGHT=720" >> $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_DMA_FONT_FREETYPE2), y)
	sed -i -e "s/^HAVE_FREETYPE_2_SUPPORT.*/HAVE_FREETYPE_2_SUPPORT=Y/" $(MICROWIN_SOURCE)/src/config
else
	sed -i -e "s/^HAVE_FREETYPE_2_SUPPORT.*/HAVE_FREETYPE_2_SUPPORT=N/" $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_DMA_ARPHIC_FONT), y)
	echo "USE_ARPHIC_FONT=Y" >> $(MICROWIN_SOURCE)/src/config
endif
	echo "INCFT2LIB=$(LIBS_INSTALL_PATH)/include" >> $(MICROWIN_SOURCE)/src/config
	echo "LIBFT2LIB=$(LIBS_INSTALL_PATH)/lib/libfreetype.a" >> $(MICROWIN_SOURCE)/src/config
	echo "ALPHA_BLENDING_FOR_PNG = Y" >> $(MICROWIN_SOURCE)/src/config
	echo "HAVE_PNG_SUPPORT = Y" >> $(MICROWIN_SOURCE)/src/config
ifeq ($(CONF_GFX), y)
	echo "EM86XX = Y" >> $(MICROWIN_SOURCE)/src/config
	echo "EM86XX_SDK = $(RUA_DIR)" >> $(MICROWIN_SOURCE)/src/config
	echo "SIGMA86_CHIP_NO = $(CONF_SIGMA_CHIP_NO)" >> $(MICROWIN_SOURCE)/src/config
	echo "SAMPLES_LIB = $(TOP_MP_DIR)/libhal.a $(TOP_MP_DIR)/mediaplayer.a" >> $(MICROWIN_SOURCE)/src/config
	echo "HAVE_DEVICE_MEM_SUPPORT=Y" >> $(MICROWIN_SOURCE)/src/config
else
	echo "EM86XX = N" >> $(MICROWIN_SOURCE)/src/config
	echo "REDSONIC_EM8475 = N" >> $(MICROWIN_SOURCE)/src/config
	echo "REDSONIC_EM8620 = Y" >> $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_GFX_WAIT_FOR_COMMAND), y)
	echo "WAIT_FOR_COMMANDS = Y" >> $(MICROWIN_SOURCE)/src/config
else	
	echo "WAIT_FOR_COMMANDS = N" >> $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_DMA_DEPTH32), y)
	sed -i -e "s/^SCREEN_PIXTYPE.*/SCREEN_PIXTYPE = MWPF_TRUECOLOR8888/" $(MICROWIN_SOURCE)/src/config
endif
ifeq ($(CONF_DMA_DEPTH16), y)
	sed -i -e "s/^SCREEN_PIXTYPE.*/SCREEN_PIXTYPE = MWPF_TRUECOLOR565/" $(MICROWIN_SOURCE)/src/config
endif
	sed -i -e "s/^SCREEN_WIDTH.*/SCREEN_WIDTH=$(CONF_OSD_WIDTH)/" $(MICROWIN_SOURCE)/src/config
	sed -i -e "s/^SCREEN_HEIGHT.*/SCREEN_HEIGHT=$(CONF_OSD_HEIGHT)/" $(MICROWIN_SOURCE)/src/config
	echo "DESKTOP_WIDTH = $(CONF_OSD_WIDTH)" >> $(MICROWIN_SOURCE)/src/config
	echo "DESKTOP_HEIGHT = $(CONF_OSD_HEIGHT)" >> $(MICROWIN_SOURCE)/src/config


	@echo "Configuring $(MICROWIN) done"
	@touch $@

#
# Compile
#
.PHONY: microwin-compile

microwin-compile: microwin-configured $(MICROWIN_DIR)/.microwin_compiled 

$(MICROWIN_DIR)/.microwin_compiled:
	@echo "Compiling $(MICROWIN) ..."
	make -C $(MICROWIN_SOURCE)/src  TOOLSPREFIX=$(CROSS)
	make -C $(MICROWIN_SOURCE)/src  INSTALL_PREFIX=$(LIBS_INSTALL_PATH) install
	@echo "Compiling $(MICROWIN) done"
	touch $@

#
# Update
#
.PHONY: microwin-update

microwin-update:
	@echo "Updating $(MICROWIN) ..."
	@if [ -d "$(MICROWIN_SOURCE)" ]; then\
		$(TOP_UPDATE) $(MICROWIN_SOURCE); \
	fi
	@echo "Updating $(MICROWIN) done"

#
# Status
#
.PHONY: microwin-status

microwin-status:
	@echo "Statusing $(MICROWIN) ..."
	@if [ -d "$(MICROWIN_SOURCE)" ]; then\
		$(TOP_STATUS) $(MICROWIN_SOURCE); \
	fi
	@echo "Statusing $(MICROWIN) done"

#
# Clean
#
.PHONY: microwin-clean

microwin-clean:
	-rm -rf $(MICROWIN_SOURCE)/mwcompiled $(MICROWIN_DIR)/.microwin_configured
	@if [ -d "$(MICROWIN_SOURCE)" ]; then\
		make -C $(MICROWIN_SOURCE)/src clean; \
	fi

#
# Dist clean
#
.PHONY: microwin-distclean

microwin-distclean:
	@rm -f $(MICROWIN_DIR)/.microwin_*

#
# Install
#
.PHONY: microwin-install

microwin-install:
