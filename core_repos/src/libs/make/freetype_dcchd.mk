##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# freetype makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_FREETYPE_DCCHD_VERSION 
CONF_FREETYPE_DCCHD_VERSION := 2.3.7
endif

FREETYPE_DCCHD             := freetype-$(CONF_FREETYPE_DCCHD_VERSION)#
FREETYPE_DCCHD_SERVER_URL  := $(TOP_LIBS_URL)/freetype/$(FREETYPE_DCCHD)
FREETYPE_DCCHD_DIR         := $(TOP_LIBS_DIR)#
FREETYPE_DCCHD_SOURCE      := $(FREETYPE_DCCHD_DIR)/$(FREETYPE_DCCHD)
FREETYPE_DCCHD_CONFIG      := 


#
# Download  the source 
#
.PHONY: freetype_dcchd-downloaded

freetype_dcchd-downloaded: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_downloaded

$(FREETYPE_DCCHD_DIR)/.freetype_dcchd_downloaded:
	@echo "Downloading $(FREETYPE_DCCHD) from $(FREETYPE_DCCHD_SERVER_URL) ..."
	@if [ ! -d "$(FREETYPE_DCCHD_SOURCE)" ]; then \
		cd $(FREETYPE_DCCHD_DIR); \
		$(TOP_DOWNLOAD) $(FREETYPE_DCCHD_SERVER_URL); \
	fi
	@echo "Downloading $(FREETYPE_DCCHD) done" 
	@touch $@

#
# Unpack the source
#
.PHONY: freetype_dcchd-unpacked

freetype_dcchd-unpacked: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_unpacked

$(FREETYPE_DCCHD_DIR)/.freetype_dcchd_unpacked: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_downloaded $(wildcard $(FREETYPE_DCCHD_SOURCE)/*.tar.*)
	@echo "Unpacking $(FREETYPE_DCCHD) ..."
	if [ -d "$(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD)" ]; then \
		rm -fr $(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD); \
	fi
	@cd $(FREETYPE_DCCHD_SOURCE); \
	if [ -f $(FREETYPE_DCCHD).tar.bz2 ]; then \
		tar jxvf  $(FREETYPE_DCCHD).tar.bz2 ; \
	elif [ -f  $(FREETYPE_DCCHD).tar.gz ]; then \
		tar zxvf  $(FREETYPE_DCCHD).tar.gz ; \
	else \
		(echo "No standard Freetype Library"; error) ; \
	fi
	@echo "Unpacking $(FREETYPE_DCCHD) done" 
	@touch $@


#
# Patch the source
#
.PHONY: freetype_dcchd-patched

freetype_dcchd-patched: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_patched

$(FREETYPE_DCCHD_DIR)/.freetype_dcchd_patched: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_unpacked
	# Patching...
	if [ -f $(FREETYPE_DCCHD_SOURCE)/freetype-2.3.7-ftobjs.c.patch ]; then \
		cd  $(FREETYPE_DCCHD_SOURCE)/; patch -p0 < freetype-2.3.7-ftobjs.c.patch; \
	fi
	if [ -f $(FREETYPE_DCCHD_SOURCE)/freetype-2.3.7-stobjs.c.patch ]; then \
		cd  $(FREETYPE_DCCHD_SOURCE)/; patch -p0 < freetype-2.3.7-stobjs.c.patch; \
	fi
	@touch $@

#
# config
#
.PHONY: freetype_dcchd-config

freetype_dcchd-config: 

#
# Configuration
#
.PHONY: freetype_dcchd-configured

freetype_dcchd-configured:  freetype_dcchd-config $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_configured

$(FREETYPE_DCCHD_DIR)/.freetype_dcchd_configured: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_patched $(FREETYPE_DCCHD_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FREETYPE_DCCHD) ..."
	cd $(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD);CC=$(CC) AR=$(CROSS)ar RANLIB=$(CROSS)ranlib ./configure --prefix=$(LIBS_INSTALL_PATH)/dcchd  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB)
	@echo "Configuring $(FREETYPE_DCCHD) done"
	@touch $@

#
# Compile
#
.PHONY: freetype_dcchd-compile

freetype_dcchd-compile: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_compiled

$(FREETYPE_DCCHD_DIR)/.freetype_dcchd_compiled: $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_configured
	@echo "Compiling $(FREETYPE_DCCHD) ..."
	make -C $(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD)
	make -C $(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD) install
	@echo "Compiling $(FREETYPE_DCCHD) done"
	@touch $@

#
# Update
#
.PHONY: freetype_dcchd-update

freetype_dcchd-update:
	@echo "Updating $(FREETYPE_DCCHD) ..."
	@if [ -d "$(FREETYPE_DCCHD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FREETYPE_DCCHD_SOURCE); \
	fi
	@echo "Updating $(FREETYPE_DCCHD) done"

#
# Status
#
.PHONY: freetype_dcchd-status

freetype_dcchd-status:
	@echo "Statusing $(FREETYPE_DCCHD) ..."
	@if [ -d "$(FREETYPE_DCCHD_SOURCE)" ]; then\
		$(TOP_STATUS) $(FREETYPE_DCCHD_SOURCE); \
	fi
	@echo "Statusing $(FREETYPE_DCCHD) done"

#
# Clean
#
.PHONY: freetype_dcchd-clean

freetype_dcchd-clean:
	@rm -f $(FREETYPE_DCCHD_DIR)/.freetype_dcchd_configured
	@if [ -d "$(FREETYPE_DCCHD_SOURCE)" ]; then\
		make -C $(FREETYPE_DCCHD_SOURCE)/$(FREETYPE_DCCHD) clean; \
	fi

#
# Dist clean
#
.PHONY: freetype_dcchd-distclean

freetype_dcchd-distclean:
	@rm -f $(FREETYPE_DCCHD_DIR)/.freetype_*

#
# Install
#
.PHONY: freetype_dcchd-install

freetype_dcchd-install:
