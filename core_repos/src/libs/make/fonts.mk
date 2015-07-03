##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# fonts makefile fragments 
##############################################################################

#
# Defines
#
ifeq (x$(CONF_PLATFORM_X86), xy)
PLATFORM_PATH=x86
endif
ifeq (x$(CONF_PLATFORM_SMP8634), xy)
PLATFORM_PATH=smp863x
endif
ifeq (x$(CONF_PLATFORM_SMP8654), xy)
PLATFORM_PATH=smp865x
endif
ifeq (x$(CONF_PLATFORM_SMP8655), xy)
PLATFORM_PATH=smp865x
endif

ifeq (x$(PLATFORM_PATH), x)
PLATFORM_PATH=x86
endif

ifeq (x$(CONF_FONTS_LIB_TYPE_ARCHIVE), xy)
FONT_LIB_TARGET   := *.*a*
endif
ifeq (x$(CONF_FONTS_LIB_TYPE_SO), xy)
FONT_LIB_TARGET   := *.*so*
endif
ifeq (x$(CONF_FONTS_LIB_TYPE_ALL), xy)
FONT_LIB_TARGET   := *
endif

ifeq (x$(CONF_PRODUCT_EXT_IOM),xy)
CUSTOMDIR	:=IOM/
else
CUSTOMDIR	:=
endif

FONTS_SERVER_URL  := $(TOP_LIBS_URL)/fonts/$(CONF_FONTS_VERSION)#
FONTS_DIR         := $(TOP_LIBS_DIR)#
FONTS_SOURCE      := $(FONTS_DIR)/$(CONF_FONTS_VERSION)#
FONTS_CONFIG      := 
TOP_FONT_DIR                := $(TOP)/src/osd/font#


#
# Download  the source 
#
.PHONY: fonts-downloaded

fonts-downloaded: $(FONTS_DIR)/.fonts_downloaded

$(FONTS_DIR)/.fonts_downloaded:
	@echo "Downloading $(FONTS_SOURCE) from $(FONTS_SERVER_URL) ..."
	@if [ ! -d "$(FONTS_SOURCE)" ]; then \
		cd $(FONTS_DIR); \
		$(TOP_DOWNLOAD) $(FONTS_SERVER_URL); \
	fi
	@echo "Downloading $(FONTS_SOURCE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: fonts-unpacked

fonts-unpacked: $(FONTS_DIR)/.fonts_unpacked

$(FONTS_DIR)/.fonts_unpacked: $(FONTS_DIR)/.fonts_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: fonts-patched

fonts-patched: $(FONTS_DIR)/.fonts_patched

$(FONTS_DIR)/.fonts_patched: $(FONTS_DIR)/.fonts_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: fonts-config

fonts-config: 

#
# Configuration
#
.PHONY: fonts-configured

fonts-configured:  fonts-config $(FONTS_DIR)/.fonts_configured

$(FONTS_DIR)/.fonts_configured: $(FONTS_DIR)/.fonts_patched $(FONTS_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ..
	@touch $@

#
# Compile
#
.PHONY: fonts-compile

fonts-compile: $(FONTS_DIR)/.fonts_compiled

$(FONTS_DIR)/.fonts_compiled:$(FONTS_DIR)/.fonts_configured
	@echo "Compiling FONT: $(CONF_FONTS_VERSION) ..."
	mkdir -p $(LIBS_INSTALL_PATH)/lib/
ifeq ($(CONF_FONTS_VERSION), arphic)
ifeq ($(CONF_DRAW_OSD_TEXT_BY_ALE), y)
	@ echo -en "\n\\033[0;33m ... Remove original built freetype from $(LIBS_INSTALL_PATH)/lib/libfreetype.* .....\\033[0m\n"
	$(RM) -v $(LIBS_INSTALL_PATH)/lib/libfreetype.*
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/libs/$(PLATFORM_PATH)/osd/$(FONT_LIB_TARGET) .....\\033[0m\n"
	cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/osd/$(FONT_LIB_TARGET)    $(LIBS_INSTALL_PATH)/lib/
else
	@ echo -en "\n\\033[0;33m ... Remove original built freetype from $(LIBS_INSTALL_PATH)/lib/libfreetype.* .....\\033[0m\n"
	$(RM) -v $(LIBS_INSTALL_PATH)/lib/libfreetype.*
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/libs/$(PLATFORM_PATH)/$(FONT_LIB_TARGET) .....\\033[0m\n"
	cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/$(FONT_LIB_TARGET)    $(LIBS_INSTALL_PATH)/lib/
endif
endif
ifeq ($(CONF_FONTS_VERSION), arphic_mbf)
	@ echo -en "\n\\033[0;33m ... Remove original built freetype from $(LIBS_INSTALL_PATH)/lib/libfreetype.* .....\\033[0m\n"
	$(RM) -v $(LIBS_INSTALL_PATH)/lib/libfreetype.*
ifeq ($(CONF_DRAW_OSD_TEXT_BY_ALE), y)
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/osd/$(FONT_LIB_TARGET) .....\\033[0m\n"
	cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/osd/$(FONT_LIB_TARGET)    $(LIBS_INSTALL_PATH)/lib/
else
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/$(FONT_LIB_TARGET) .....\\033[0m\n"
	cp -avf $(FONTS_SOURCE)/libs/freetype/$(CONF_FREETYPE_VERSION)/$(PLATFORM_PATH)/$(FONT_LIB_TARGET)    $(LIBS_INSTALL_PATH)/lib/
endif
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/libs/mbf/$(PLATFORM_PATH)/$(FONT_LIB_TARGET) .....\\033[0m\n"
	cp -avf $(FONTS_SOURCE)/libs/mbf/$(PLATFORM_PATH)/$(FONT_LIB_TARGET)    $(LIBS_INSTALL_PATH)/lib/
	@ echo -en "\n\\033[0;33m ... cp -avf $(FONTS_SOURCE)/include/* .....\\033[0m\n"
	cp -avrf $(FONTS_SOURCE)/include/*    $(LIBS_INSTALL_PATH)/include/
endif
	@echo "Compiling FONT $(CONF_FONTS_VERSION) done"
	@touch $@


#
# Update
#
.PHONY: fonts-update

fonts-update:
	@echo "Updating $(CONF_FONTS_VERSION) ..."
	@if [ -d "$(FONTS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FONTS_SOURCE); \
	fi
	@echo "Updating $(CONF_FONTS_VERSION) done"

#
# Status
#
.PHONY: fonts-status

fonts-status:
	@echo "Statusing $(CONF_FONTS_VERSION) ..."
	@if [ -d "$(FONTS_SOURCE)" ]; then\
		$(TOP_STATUS) $(FONTS_SOURCE); \
	fi
	@echo "Statusing $(CONF_FONTS_VERSION) done"

#
# Clean
#
.PHONY: fonts-clean

fonts-clean:

#
# Dist clean
#
.PHONY: fonts-distclean

fonts-distclean:
	@rm -f $(FONTS_DIR)/.fonts_*

#
# Install
#
.PHONY: fonts-install

fonts-install:
	@ echo -en "\n\\033[0;33m ... Install font  .....\\033[0m\n"
	@if [ ! -d "$(TOP_INSTALL_ROOTFS_FONT_DIR)" ]; then \
		mkdir -p $(TOP_INSTALL_ROOTFS_FONT_DIR); \
	fi
ifeq ($(CONF_FONTS_VERSION), arphic)
	cp -vf $(FONTS_SOURCE)/fonts/CJK_GothicMedium/*.vcp    $(TOP_INSTALL_ROOTFS_FONT_DIR)
	cp -vf $(FONTS_SOURCE)/fonts/CJK_GothicMedium/*.xml    $(TOP_INSTALL_ROOTFS_FONT_DIR)
endif
ifeq ($(CONF_FONTS_VERSION), arphic_mbf)
	cp -vf $(FONTS_SOURCE)/fonts/Heiti/$(CUSTOMDIR)*.mbf    $(TOP_INSTALL_ROOTFS_FONT_DIR)
	cp -vf $(FONTS_SOURCE)/fonts/Heiti/$(CUSTOMDIR)*.ttf    $(TOP_INSTALL_ROOTFS_FONT_DIR)
	cp -vf $(FONTS_SOURCE)/fonts/Heiti/$(CUSTOMDIR)*.xml    $(TOP_INSTALL_ROOTFS_FONT_DIR)
endif
ifeq ($(CONF_FONTS_VERSION), freetype)
# TBD
endif
	@ echo -en "\n\\033[0;33m ... Install font done .....\\033[0m\n"
