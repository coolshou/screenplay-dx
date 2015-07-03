##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# libid3tag makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_LIBID3TAG_VERSION 
CONF_LIBID3TAG_VERSION := 0.15.1b
endif

LIBID3TAG             := libid3tag-$(CONF_LIBID3TAG_VERSION)#
LIBID3TAG_SERVER_URL  := $(TOP_LIBS_URL)/libid3tag/$(LIBID3TAG)#
LIBID3TAG_DIR         := $(TOP_LIBS_DIR)#
LIBID3TAG_SOURCE      := $(LIBID3TAG_DIR)/$(LIBID3TAG)#
LIBID3TAG_CONFIG      := 

#
# Download  the source 
#
.PHONY: libid3tag-downloaded

libid3tag-downloaded: $(LIBID3TAG_DIR)/.libid3tag_downloaded

$(LIBID3TAG_DIR)/.libid3tag_downloaded:
	@echo "Downloading $(LIBID3TAG) from $(LIBID3TAG_SERVER_URL) ..."
	@if [ ! -d "$(LIBID3TAG_SOURCE)" ]; then \
		cd $(LIBID3TAG_DIR); \
		$(TOP_DOWNLOAD) $(LIBID3TAG_SERVER_URL); \
	fi
	@echo "Downloading $(LIBID3TAG) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libid3tag-unpacked

libid3tag-unpacked: $(LIBID3TAG_DIR)/.libid3tag_unpacked

$(LIBID3TAG_DIR)/.libid3tag_unpacked: $(LIBID3TAG_DIR)/.libid3tag_downloaded $(wildcard $(LIBID3TAG_SOURCE)/*.tar.gz)
	@echo "Unpacking $(LIBID3TAG) ..."
	if [ -d "$(LIBID3TAG_SOURCE)/$(LIBID3TAG)" ]; then \
		rm -fr $(LIBID3TAG_SOURCE)/$(LIBID3TAG); \
	fi
	(cd $(LIBID3TAG_SOURCE); tar xvzf $(LIBID3TAG).tar.gz)
	@echo "Unpacking $(LIBID3TAG) done"
	@touch $@


#
# Patch the source
#
.PHONY: libid3tag-patched

libid3tag-patched: $(LIBID3TAG_DIR)/.libid3tag_patched

$(LIBID3TAG_DIR)/.libid3tag_patched: $(LIBID3TAG_DIR)/.libid3tag_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libid3tag-config

libid3tag-config: 

#
# Configuration
#
.PHONY: libid3tag-configured

libid3tag-configured:  libid3tag-config $(LIBID3TAG_DIR)/.libid3tag_configured

$(LIBID3TAG_DIR)/.libid3tag_configured: $(LIBID3TAG_DIR)/.libid3tag_patched $(LIBID3TAG_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(LIBID3TAG) ..."
	cd $(LIBID3TAG_SOURCE)/$(LIBID3TAG); ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) \
	CPPFLAGS=-I$(LIBS_INSTALL_PATH)/include LDFLAGS=-L$(LIBS_INSTALL_PATH)/lib
	@echo "Configuring $(LIBID3TAG) done"
	@touch $@

#
# Compile
#
.PHONY: libid3tag-compile

libid3tag-compile: $(LIBID3TAG_DIR)/.libid3tag_compiled

$(LIBID3TAG_DIR)/.libid3tag_compiled: $(LIBID3TAG_DIR)/.libid3tag_configured
	@echo "Compiling $(LIBID3TAG) ..."
	make -C $(LIBID3TAG_SOURCE)/$(LIBID3TAG)
	make -C $(LIBID3TAG_SOURCE)/$(LIBID3TAG) install
	@echo "Compiling $(LIBID3TAG) done"
	@touch $@

#
# Update
#
.PHONY: libid3tag-update

libid3tag-update:
	@echo "Updating $(LIBID3TAG) ..."
	@if [ -d "$(LIBID3TAG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBID3TAG_SOURCE); \
	fi
	@echo "Updating $(LIBID3TAG) done"

#
# Status
#
.PHONY: libid3tag-status

libid3tag-status:
	@echo "Statusing $(LIBID3TAG) ..."
	@if [ -d "$(LIBID3TAG_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBID3TAG_SOURCE); \
	fi
	@echo "Statusing $(LIBID3TAG) done"

#
# Clean
#
.PHONY: libid3tag-clean

libid3tag-clean:
	@rm -f $(LIBID3TAG_DIR)/.libid3tag_configured
	@if [ -d "$(LIBID3TAG_SOURCE)" ]; then\
		make -C $(LIBID3TAG_SOURCE)/$(LIBID3TAG) clean; \
	fi

#
# Dist clean
#
.PHONY: libid3tag-distclean

libid3tag-distclean:
	@rm -f $(LIBID3TAG_DIR)/.libid3tag*

#
# Install
#
.PHONY: libid3tag-install

libid3tag-install:
