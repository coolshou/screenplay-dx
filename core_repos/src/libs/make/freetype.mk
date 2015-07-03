##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# freetype makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_FREETYPE_VERSION 
CONF_FREETYPE_VERSION := 2.1.3
endif

FREETYPE             := freetype-$(CONF_FREETYPE_VERSION)#
FREETYPE_SERVER_URL  := $(TOP_LIBS_URL)/freetype/$(FREETYPE)
FREETYPE_DIR         := $(TOP_LIBS_DIR)#
FREETYPE_SOURCE      := $(FREETYPE_DIR)/$(FREETYPE)
FREETYPE_CONFIG      := 


#
# Download  the source 
#
.PHONY: freetype-downloaded

freetype-downloaded: $(FREETYPE_DIR)/.freetype_downloaded

$(FREETYPE_DIR)/.freetype_downloaded:
	@echo "Downloading $(FREETYPE) from $(FREETYPE_SERVER_URL) ..."
	@if [ ! -d "$(FREETYPE_SOURCE)" ]; then \
		cd $(FREETYPE_DIR); \
		$(TOP_DOWNLOAD) $(FREETYPE_SERVER_URL); \
	fi
	@echo "Downloading $(FREETYPE) done" 
	@touch $@

#
# Unpack the source
#
.PHONY: freetype-unpacked

freetype-unpacked: $(FREETYPE_DIR)/.freetype_unpacked

$(FREETYPE_DIR)/.freetype_unpacked: $(FREETYPE_DIR)/.freetype_downloaded $(wildcard $(FREETYPE_SOURCE)/*.tar.*)
	@echo "Unpacking $(FREETYPE) ..."
	if [ -d "$(FREETYPE_SOURCE)/$(FREETYPE)" ]; then \
		rm -fr $(FREETYPE_SOURCE)/$(FREETYPE); \
	fi
	@cd $(FREETYPE_SOURCE); \
	if [ -f $(FREETYPE).tar.bz2 ]; then \
		tar jxvf  $(FREETYPE).tar.bz2 ; \
	elif [ -f  $(FREETYPE).tar.gz ]; then \
		tar zxvf  $(FREETYPE).tar.gz ; \
	else \
		(echo "No standard Freetype Library"; error) ; \
	fi
	@echo "Unpacking $(FREETYPE) done" 
	@touch $@


#
# Patch the source
#
.PHONY: freetype-patched

freetype-patched: $(FREETYPE_DIR)/.freetype_patched

$(FREETYPE_DIR)/.freetype_patched: $(FREETYPE_DIR)/.freetype_unpacked
	# Patching...
	if [ -f $(FREETYPE_SOURCE)/freetype-2.3.7-ftobjs.c.patch ]; then \
		cd  $(FREETYPE_SOURCE)/; patch -p0 < freetype-2.3.7-ftobjs.c.patch; \
	fi
	if [ -f $(FREETYPE_SOURCE)/freetype-2.3.7-stobjs.c.patch ]; then \
		cd  $(FREETYPE_SOURCE)/; patch -p0 < freetype-2.3.7-stobjs.c.patch; \
	fi
	@touch $@

#
# config
#
.PHONY: freetype-config

freetype-config: 

#
# Configuration
#
.PHONY: freetype-configured

freetype-configured:  freetype-config $(FREETYPE_DIR)/.freetype_configured

$(FREETYPE_DIR)/.freetype_configured: $(FREETYPE_DIR)/.freetype_patched $(FREETYPE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FREETYPE) ..."
	cd $(FREETYPE_SOURCE)/$(FREETYPE);CC=$(CC) AR=$(CROSS)ar RANLIB=$(CROSS)ranlib ./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB)
	@echo "Configuring $(FREETYPE) done"
	@touch $@

#
# Compile
#
.PHONY: freetype-compile

freetype-compile: $(FREETYPE_DIR)/.freetype_compiled

$(FREETYPE_DIR)/.freetype_compiled: $(FREETYPE_DIR)/.freetype_configured
	@echo "Compiling $(FREETYPE) ..."
	make -C $(FREETYPE_SOURCE)/$(FREETYPE)
	make -C $(FREETYPE_SOURCE)/$(FREETYPE) install
	cp $(LIBS_INSTALL_PATH)/lib/libfreetype.a $(LIBS_INSTALL_PATH)/lib/liborgfreetype.a
	@echo "Compiling $(FREETYPE) done"
	@touch $@

#
# Update
#
.PHONY: freetype-update

freetype-update:
	@echo "Updating $(FREETYPE) ..."
	@if [ -d "$(FREETYPE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FREETYPE_SOURCE); \
	fi
	@echo "Updating $(FREETYPE) done"

#
# Status
#
.PHONY: freetype-status

freetype-status:
	@echo "Statusing $(FREETYPE) ..."
	@if [ -d "$(FREETYPE_SOURCE)" ]; then\
		$(TOP_STATUS) $(FREETYPE_SOURCE); \
	fi
	@echo "Statusing $(FREETYPE) done"

#
# Clean
#
.PHONY: freetype-clean

freetype-clean:
	@rm -f $(FREETYPE_DIR)/.freetype_configured
	@if [ -d "$(FREETYPE_SOURCE)" ]; then\
		make -C $(FREETYPE_SOURCE)/$(FREETYPE) clean; \
	fi

#
# Dist clean
#
.PHONY: freetype-distclean

freetype-distclean:
	@rm -f $(FREETYPE_DIR)/.freetype_*

#
# Install
#
.PHONY: freetype-install

freetype-install:
