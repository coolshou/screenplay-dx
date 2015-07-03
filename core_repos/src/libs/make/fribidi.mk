##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  kernel_wu@alphanetworks.com
# fribidi makefile fragments 
##############################################################################

#Use default version execept extra defined 
ifndef  CONF_FRIBIDI_VERSION
CONF_FRIBIDI_VERSION := 0.10.9
endif



#We don't need to output .a so close when run configure
ifeq (x$(ENABLE_SHLIB),xyes) 
	FRIBIDI_STATIC_SWITCH := no
endif


#
# Defines
#
FRIBIDI             := fribidi-$(CONF_FRIBIDI_VERSION)#
FRIBIDI_PKG	    := $(FRIBIDI).tar.gz
FRIBIDI_SERVER_URL  := $(TOP_LIBS_URL)/fribidi/$(FRIBIDI)/#
FRIBIDI_DIR         := $(TOP_LIBS_DIR)#
FRIBIDI_SOURCE      := $(FRIBIDI_DIR)/$(FRIBIDI)
FRIBIDI_CONFIG      := 


#
# Download  the source 
#
.PHONY: fribidi-downloaded

fribidi-downloaded: $(FRIBIDI_DIR)/.fribidi_downloaded

$(FRIBIDI_DIR)/.fribidi_downloaded:
	@echo "Downloading $(FRIBIDI) from $(FRIBIDI_SERVER_URL) ..."
	@if [ ! -d "$(FRIBIDI_SOURCE)" ]; then \
		cd $(FRIBIDI_DIR); \
		$(TOP_DOWNLOAD) $(FRIBIDI_SERVER_URL); \
	fi
	@echo "Downloading $(FRIBIDI) from $(FRIBIDI_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: fribidi-unpacked

fribidi-unpacked: $(FRIBIDI_DIR)/.fribidi_unpacked

$(FRIBIDI_DIR)/.fribidi_unpacked: $(FRIBIDI_DIR)/.fribidi_downloaded $(FRIBIDI_SOURCE)/$(FRIBIDI_PKG)
	@echo "Unpacking $(FRIBIDI) ..."
	if [ -d "$(FRIBIDI_SOURCE)" ]; then \
		rm -fr $(FRIBIDI_SOURCE)/$(FRIBIDI); \
	fi
	cd $(FRIBIDI_SOURCE); tar zxvf $(FRIBIDI_PKG)
	@echo "Unpacking $(FRIBIDI) done"
	@touch $@


#
# Patch the source
#
.PHONY: fribidi-patched

fribidi-patched: $(FRIBIDI_DIR)/.fribidi_patched

$(FRIBIDI_DIR)/.fribidi_patched: $(FRIBIDI_DIR)/.fribidi_unpacked
	# Patching...
# Patching...
	@touch $@

#
# config
#
.PHONY: fribidi-config

fribidi-config: 

#
# Configuration
#
.PHONY: fribidi-configured

fribidi-configured:  fribidi-config $(FRIBIDI_DIR)/.fribidi_configured

$(FRIBIDI_DIR)/.fribidi_configured: $(FRIBIDI_DIR)/.fribidi_patched $(FRIBIDI_CONFIG) $(TOP_CURRENT_SET)
	cd $(FRIBIDI_SOURCE)/$(FRIBIDI);./configure CC=$(CC) AR=$(CROSS)ar ./configure --prefix=$(LIBS_INSTALL_PATH) --libdir=$(LIBS_INSTALL_PATH)/lib --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) --enable-static=$(FRIBIDI_STATIC_SWITCH)
	@touch $@

#
# Compile
#
.PHONY: fribidi-compile

fribidi-compile: $(FRIBIDI_DIR)/.fribidi_compiled

$(FRIBIDI_DIR)/.fribidi_compiled: $(FRIBIDI_DIR)/.fribidi_configured
	@echo "Compiling $(FRIBIDI) ..."
	test -z "$(LIBS_INSTALL_PATH)/include/fribidi" || mkdir -p -- "$(LIBS_INSTALL_PATH)/include/fribidi"
	cp -avrf $(FRIBIDI_SOURCE)/$(FRIBIDI)/*.i    $(LIBS_INSTALL_PATH)/include/fribidi
	cp -avrf $(FRIBIDI_SOURCE)/$(FRIBIDI)/*.h    $(LIBS_INSTALL_PATH)/include/fribidi
	cd $(FRIBIDI_SOURCE)/$(FRIBIDI) && make && make install-libLTLIBRARIES && touch $@ && echo "Compiling $(FRIBIDI) done"

#
# Update
#
.PHONY: fribidi-update

fribidi-update:
	@echo "Updating $(FRIBIDI) ..."
	@if [ -d "$(FRIBIDI_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FRIBIDI_SOURCE); \
	fi
	@echo "Updating $(FRIBIDI) done"

#
# Status
#
.PHONY: fribidi-status

fribidi-status:
	@echo "Statusing $(FRIBIDI) ..."
	@if [ -d "$(FRIBIDI_SOURCE)" ]; then\
		$(TOP_STATUS) $(FRIBIDI_SOURCE); \
	fi
	@echo "Statusing $(FRIBIDI) done"

#
# Clean
#
.PHONY: fribidi-clean

fribidi-clean:
	@rm -f $(FRIBIDI_DIR)/.fribidi_configured
	@rm -f $(FRIBIDI_DIR)/.fribidi_compiled
	@if [ -d "$(FRIBIDI_SOURCE)/$(FRIBIDI)" ]; then\
		make -C $(FRIBIDI_SOURCE)/$(FRIBIDI)  clean; \
	fi
	@rm -f $(LIBS_INSTALL_PATH)/lib/libfribidi.*
	@rm -rf $(LIBS_INSTALL_PATH)/include/fribidi

#
# Dist clean
#
.PHONY: fribidi-distclean

fribidi-distclean:
	@rm -f $(FRIBIDI_DIR)/.fribidi_*

#
# Install
#
.PHONY: fribidi-install

fribidi-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	test -z "$(TOP_INSTALL_ROOTFS_DIR)/lib" || mkdir -p -- "$(TOP_INSTALL_ROOTFS_DIR)/lib"
	cp -avf $(LIBS_INSTALL_PATH)/lib/libfribidi* $(TOP_INSTALL_ROOTFS_DIR)/lib
	 



        
