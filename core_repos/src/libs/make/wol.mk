##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# wol makefile fragments 
##############################################################################

#
# Defines
#
CONF_WOL_VERSION := 0.7.1

WOL             := wol-$(CONF_WOL_VERSION)#
WOL_SERVER_URL  := $(TOP_LIBS_URL)/wol/$(WOL)
WOL_DIR         := $(TOP_LIBS_DIR)#
WOL_SOURCE      := $(WOL_DIR)/$(WOL)
WOL_CONFIG      := 

#
# Download  the source 
#
.PHONY: wol-downloaded

wol-downloaded: $(WOL_DIR)/.wol_downloaded

$(WOL_DIR)/.wol_downloaded:
	@echo "Downloading $(WOL) from $(WOL_SERVER_URL) ..."
	@if [ ! -d "$(WOL_SOURCE)" ]; then \
		cd $(WOL_DIR); \
		$(TOP_DOWNLOAD) $(WOL_SERVER_URL); \
	fi
	@echo "Downloading $(WOL) from $(WOL_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: wol-unpacked

wol-unpacked: $(WOL_DIR)/.wol_unpacked

$(WOL_DIR)/.wol_unpacked: $(WOL_DIR)/.wol_downloaded $(WOL_SOURCE)/$(WOL).tar.gz
	@echo "Unpacking $(WOL) ..."
	if [ -d "$(WOL_SOURCE)/$(WOL)" ]; then \
		rm -fr $(WOL_SOURCE)/$(WOL); \
	fi
	cd $(WOL_SOURCE); tar zxvf $(WOL).tar.gz
	@echo "Unpacking $(WOL) done"
	@touch $@


#
# Patch the source
#
.PHONY: wol-patched

wol-patched: $(WOL_DIR)/.wol_patched

$(WOL_DIR)/.wol_patched: $(WOL_DIR)/.wol_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: wol-config

wol-config: 

#
# Configuration
#
.PHONY: wol-configured

wol-configured:  wol-config $(WOL_DIR)/.wol_configured

$(WOL_DIR)/.wol_configured: $(WOL_DIR)/.wol_patched $(WOL_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(WOL) ..."
	cd $(WOL_SOURCE)/$(WOL);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=no --enable-static=yes --disable-nls --disable-rpath 
	cd $(WOL_SOURCE)/$(WOL);sed -i -e "s/define malloc/undef malloc/" config.h;
	cd $(WOL_SOURCE)/$(WOL);sed -i -e "s/define realloc/undef realloc/" config.h;
	@echo "Configuring $(WOL) done"
	@touch $@

#
# Compile
#
.PHONY: wol-compile

wol-compile: $(WOL_DIR)/.wol_compiled

$(WOL_DIR)/.wol_compiled: $(WOL_DIR)/.wol_configured
	@echo "Compiling $(WOL) ..."
	#make -C $(WOL_SOURCE)/$(WOL) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(WOL_SOURCE)/$(WOL) 
	make -C $(WOL_SOURCE)/$(WOL)  install
	@echo "Compiling $(WOL) done"
	@touch $@

#
# Update
#
.PHONY: wol-update

wol-update:
	@echo "Updating $(WOL) ..."
	@if [ -d "$(WOL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(WOL_SOURCE); \
	fi
	@echo "Updating $(WOL) done"

#
# Status
#
.PHONY: wol-status

wol-status:
	@echo "Statusing $(WOL) ..."
	@if [ -d "$(WOL_SOURCE)" ]; then\
		$(TOP_STATUS) $(WOL_SOURCE); \
	fi
	@echo "Statusing $(WOL) done"

#
# Clean
#
.PHONY: wol-clean

wol-clean:
	@rm -f $(WOL_DIR)/.wol_configured
	@if [ -d "$(WOL_SOURCE)" ]; then\
		make -C $(WOL_SOURCE)/$(WOL) clean; \
	fi

#
# Dist clean
#
.PHONY: wol-distclean

wol-distclean:
	@rm -f $(WOL_DIR)/.wol_*

#
# Install
#
.PHONY: wol-install

wol-install:
	make -C $(WOL_SOURCE)/$(WOL) install
