##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  carey_chou@alphanetworks.com
# glib makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_GLIB_VERSION 
CONF_GLIB_VERSION := 2.18.0
endif

GLIB             := glib-$(CONF_GLIB_VERSION)#
GLIB_SERVER_URL  := $(TOP_LIBS_URL)/glib/$(GLIB)
GLIB_DIR         := $(TOP_LIBS_DIR)#
GLIB_SOURCE      := $(GLIB_DIR)/$(GLIB)
GLIB_CONFIG      := 

#
# Download  the source 
#
.PHONY: glib-downloaded

glib-downloaded: $(GLIB_DIR)/.glib_downloaded

$(GLIB_DIR)/.glib_downloaded:
	@echo "Downloading $(GLIB) from $(GLIB_SERVER_URL) ..."
	@if [ ! -d "$(GLIB_SOURCE)" ]; then \
		cd $(GLIB_DIR); \
		$(TOP_DOWNLOAD) $(GLIB_SERVER_URL); \
	fi
	@echo "Downloading $(GLIB) from $(GLIB_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: glib-unpacked

glib-unpacked: $(GLIB_DIR)/.glib_unpacked

$(GLIB_DIR)/.glib_unpacked: $(GLIB_DIR)/.glib_downloaded $(GLIB_SOURCE)/$(GLIB).tar.bz2
	@echo "Unpacking $(GLIB) ..."
	if [ -d "$(GLIB_SOURCE)/$(GLIB)" ]; then \
		rm -fr $(GLIB_SOURCE)/$(GLIB); \
	fi
	cd $(GLIB_SOURCE); tar jxvf $(GLIB).tar.bz2
	@echo "Unpacking $(GLIB) done"
	@touch $@


#
# Patch the source
#
.PHONY: glib-patched

glib-patched: $(GLIB_DIR)/.glib_patched

$(GLIB_DIR)/.glib_patched: $(GLIB_DIR)/.glib_unpacked
	# Patching...
	#cd $(GLIB_SOURCE); cp mipsel-linux.cache $(GLIB)/
	@touch $@

#
# config
#
.PHONY: glib-config

glib-config: 

#
# Configuration
#
.PHONY: glib-configured

glib-configured:  glib-config $(GLIB_DIR)/.glib_configured

$(GLIB_DIR)/.glib_configured: $(GLIB_DIR)/.glib_patched $(GLIB_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(GLIB) ..."
	cd $(GLIB_SOURCE)/$(GLIB); echo glib_cv_stack_grows=no > ARCH-linux.cache
	cd $(GLIB_SOURCE)/$(GLIB); echo glib_cv_uscore=no >> ARCH-linux.cache
	cd $(GLIB_SOURCE)/$(GLIB); echo ac_cv_func_posix_getpwuid_r=yes >> ARCH-linux.cache
	cd $(GLIB_SOURCE)/$(GLIB); echo ac_cv_func_posix_getgrgid_r=yes >> ARCH-linux.cache
	cd $(GLIB_SOURCE)/$(GLIB);./configure  --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)  --cache-file=ARCH-linux.cache 
	@echo "Configuring $(GLIB) done" 
	@touch $@

#
# Compile
#
.PHONY: glib-compile

glib-compile: $(GLIB_DIR)/.glib_compiled

$(GLIB_DIR)/.glib_compiled: $(GLIB_DIR)/.glib_configured
	@echo "Compiling $(GLIB) ..."
	#make -C $(GLIB_SOURCE)/$(GLIB) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(GLIB_SOURCE)/$(GLIB) 
	make -C $(GLIB_SOURCE)/$(GLIB)  install
	@echo "Compiling $(GLIB) done"
	@touch $@

#
# Update
#
.PHONY: glib-update

glib-update:
	@echo "Updating $(GLIB) ..."
	@if [ -d "$(GLIB_SOURCE)" ]; then\
		$(TOP_UPDATE) $(GLIB_SOURCE); \
	fi
	@echo "Updating $(GLIB) done"

#
# Status
#
.PHONY: glib-status

glib-status:
	@echo "Statusing $(GLIB) ..."
	@if [ -d "$(GLIB_SOURCE)" ]; then\
		$(TOP_STATUS) $(GLIB_SOURCE); \
	fi
	@echo "Statusing $(GLIB) done"

#
# Clean
#
.PHONY: glib-clean

glib-clean:
	@rm -f $(GLIB_DIR)/.glib_configured
	@if [ -d "$(GLIB_SOURCE)" ]; then\
		make -C $(GLIB_SOURCE)/$(GLIB) clean; \
	fi

#
# Dist clean
#
.PHONY: glib-distclean

glib-distclean:
	@rm -f $(GLIB_DIR)/.glib_*

#
# Install
#
.PHONY: glib-install

glib-install:
	@cp -af $(LIBS_INSTALL_PATH)/lib/libglib*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib  
	@cp -af $(LIBS_INSTALL_PATH)/lib/libgio*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib  
	@cp -af $(LIBS_INSTALL_PATH)/lib/libgobject*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib  
	@cp -af $(LIBS_INSTALL_PATH)/lib/libgmodule*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib  
	@cp -af $(LIBS_INSTALL_PATH)/lib/libgthread*.so* $(TOP_INSTALL_ROOTFS_DIR)/lib  
