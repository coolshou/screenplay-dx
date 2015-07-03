##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# fuse makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_FUSE_VERSION 
CONF_FUSE_VERSION := 2.7.4
endif

FUSE             := fuse-$(CONF_FUSE_VERSION)#
FUSE_SERVER_URL  := $(TOP_LIBS_URL)/fuse/$(FUSE)
FUSE_DIR         := $(TOP_LIBS_DIR)#
FUSE_SOURCE      := $(FUSE_DIR)/$(FUSE)
FUSE_CONFIG      := 

#
# Download  the source 
#
.PHONY: fuse-downloaded

fuse-downloaded: $(FUSE_DIR)/.fuse_downloaded

$(FUSE_DIR)/.fuse_downloaded:
	@echo "Downloading $(FUSE) from $(FUSE_SERVER_URL) ..."
	@if [ ! -d "$(FUSE_SOURCE)" ]; then \
		cd $(FUSE_DIR); \
		$(TOP_DOWNLOAD) $(FUSE_SERVER_URL); \
	fi
	@echo "Downloading $(FUSE) from $(FUSE_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: fuse-unpacked

fuse-unpacked: $(FUSE_DIR)/.fuse_unpacked

$(FUSE_DIR)/.fuse_unpacked: $(FUSE_DIR)/.fuse_downloaded $(FUSE_SOURCE)/$(FUSE).tar.gz
	@echo "Unpacking $(FUSE) ..."
	if [ -d "$(FUSE_SOURCE)/$(FUSE)" ]; then \
		rm -fr $(FUSE_SOURCE)/$(FUSE); \
	fi
	cd $(FUSE_SOURCE); tar zxvf $(FUSE).tar.gz
	@echo "Unpacking $(FUSE) done"
	@touch $@


#
# Patch the source
#
.PHONY: fuse-patched

fuse-patched: $(FUSE_DIR)/.fuse_patched

$(FUSE_DIR)/.fuse_patched: $(FUSE_DIR)/.fuse_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: fuse-config

fuse-config: 

#
# Configuration
#
.PHONY: fuse-configured

fuse-configured:  fuse-config $(FUSE_DIR)/.fuse_configured

$(FUSE_DIR)/.fuse_configured: $(FUSE_DIR)/.fuse_patched $(FUSE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FUSE) ..."
	cd $(FUSE_SOURCE)/$(FUSE);./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --disable-util --disable-example --with-libiconv-prefix=$(LIBS_INSTALL_PATH)/lib PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" --enable-shared=no
	@echo "Configuring $(FUSE) done"
	@touch $@

#
# Compile
#
.PHONY: fuse-compile

fuse-compile: $(FUSE_DIR)/.fuse_compiled

$(FUSE_DIR)/.fuse_compiled: $(FUSE_DIR)/.fuse_configured
	@echo "Compiling $(FUSE) ..."
	#make -C $(FUSE_SOURCE)/$(FUSE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(FUSE_SOURCE)/$(FUSE) 
	make -C $(FUSE_SOURCE)/$(FUSE)  install
	@echo "Compiling $(FUSE) done"
	@touch $@

#
# Update
#
.PHONY: fuse-update

fuse-update:
	@echo "Updating $(FUSE) ..."
	@if [ -d "$(FUSE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FUSE_SOURCE); \
	fi
	@echo "Updating $(FUSE) done"

#
# Status
#
.PHONY: fuse-status

fuse-status:
	@echo "Statusing $(FUSE) ..."
	@if [ -d "$(FUSE_SOURCE)" ]; then\
		$(TOP_STATUS) $(FUSE_SOURCE); \
	fi
	@echo "Statusing $(FUSE) done"

#
# Clean
#
.PHONY: fuse-clean

fuse-clean:
	@rm -f $(FUSE_DIR)/.fuse_configured
	@if [ -d "$(FUSE_SOURCE)" ]; then\
		make -C $(FUSE_SOURCE)/$(FUSE) clean; \
	fi

#
# Dist clean
#
.PHONY: fuse-distclean

fuse-distclean:
	@rm -f $(FUSE_DIR)/.fuse_*

#
# Install
#
.PHONY: fuse-install

fuse-install:
