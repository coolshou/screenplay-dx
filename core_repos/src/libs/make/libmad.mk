##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libmad makefile fragments 
##############################################################################

#
# Defines
#
ifndef  LIBMAD_VERSION 
LIBMAD_VERSION := 0.15.1b
endif

LIBMAD             := libmad-$(LIBMAD_VERSION)#
LIBMAD_SERVER_URL  := $(TOP_LIBS_URL)/libmad/$(LIBMAD)
LIBMAD_DIR         := $(TOP_LIBS_DIR)#
LIBMAD_SOURCE      := $(LIBMAD_DIR)/$(LIBMAD)
LIBMAD_CONFIG      := 


#
# Download  the source 
#
.PHONY: libmad-downloaded

libmad-downloaded: $(LIBMAD_DIR)/.libmad_downloaded

$(LIBMAD_DIR)/.libmad_downloaded:
	@echo "Downloading $(LIBMAD) from $(LIBMAD_SERVER_URL) ..."
	@if [ ! -d "$(LIBMAD_SOURCE)" ]; then \
		cd $(LIBMAD_DIR); \
		$(TOP_DOWNLOAD) $(LIBMAD_SERVER_URL); \
	fi
	@echo "Downloading $(LIBMAD) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libmad-unpacked

libmad-unpacked: $(LIBMAD_DIR)/.libmad_unpacked

$(LIBMAD_DIR)/.libmad_unpacked: $(LIBMAD_DIR)/.libmad_downloaded $(LIBMAD_SOURCE)/$(LIBMAD).tar.gz
	@echo "Unpacking the $(LIBMAD) ..."
	if [ -d "$(LIBMAD_SOURCE)/$(LIBMAD)" ]; then \
		rm -fr $(LIBMAD_SOURCE)/$(LIBMAD);\
	fi
	cd $(LIBMAD_SOURCE); tar xzvf  $(LIBMAD).tar.gz
	@echo "Unpacking the $(LIBMAD) done"
	@touch $@


#
# Patch the source
#
.PHONY: libmad-patched

libmad-patched: $(LIBMAD_DIR)/.libmad_patched

$(LIBMAD_DIR)/.libmad_patched: $(LIBMAD_DIR)/.libmad_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libmad-config

libmad-config: 

#
# Configuration
#
.PHONY: libmad-configured

libmad-configured:  libmad-config $(LIBMAD_DIR)/.libmad_configured

$(LIBMAD_DIR)/.libmad_configured: $(LIBMAD_DIR)/.libmad_patched $(LIBMAD_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring the $(LIBMAD) ..."
	cd $(LIBMAD_SOURCE)/$(LIBMAD); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=${BUILD_TARGET} --enable-shared=$(ENABLE_SHLIB)
	@echo "Configuring $(LIBMAD) ..."
	@touch $@

#
# Compile
#
.PHONY: libmad-compile

libmad-compile: $(LIBMAD_DIR)/.libmad_compiled

$(LIBMAD_DIR)/.libmad_compiled: $(LIBMAD_DIR)/.libmad_configured
	@echo "Compiling $(LIBMAD) ..."
	make -C $(LIBMAD_SOURCE)/$(LIBMAD) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(LIBMAD_SOURCE)/$(LIBMAD) install
	@echo "Compiling $(LIBMAD) done"
	@touch $@

#
# Update
#
.PHONY: libmad-update

libmad-update:
	@echo "Updating $(LIBMAD) ..."
	@if [ -d "$(LIBMAD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBMAD_SOURCE); \
	fi
	@echo "Updating $(LIBMAD) done"

#
# Status
#
.PHONY: libmad-status

libmad-status:
	@echo "Statusing $(LIBMAD) ..."
	@if [ -d "$(LIBMAD_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBMAD_SOURCE); \
	fi
	@echo "Statusing $(LIBMAD) done"

#
# Clean
#
.PHONY: libmad-clean

libmad-clean:
	@rm -f $(LIBMAD_DIR)/.libmad_configured
	@if [ -d "$(LIBMAD_SOURCE)" ]; then\
		make -C $(LIBMAD_SOURCE)/$(LIBMAD) clean; \
	fi

#
# Dist clean
#
.PHONY: libmad-distclean

libmad-distclean:
	@rm -f $(LIBMAD_DIR)/.libmad_*

#
# Install
#
.PHONY: libmad-install

libmad-install:
