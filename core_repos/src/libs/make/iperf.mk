##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# iperf makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_IPERF_VERSION 
CONF_IPERF_VERSION := 2.0.4
endif

IPERF             := iperf-$(CONF_IPERF_VERSION)#
IPERF_SERVER_URL  := $(TOP_LIBS_URL)/iperf/$(IPERF)#
IPERF_DIR         := $(TOP_LIBS_DIR)#
IPERF_SOURCE      := $(IPERF_DIR)/$(IPERF)#

#
# Download  the source 
#
.PHONY: iperf-downloaded

iperf-downloaded: $(IPERF_DIR)/.iperf_downloaded

$(IPERF_DIR)/.iperf_downloaded:
	@echo "Downloading $(IPERF) from $(IPERF_SERVER_URL) ..."
	@echo "CMD: $(TOP_DOWNLOAD) $(IPERF_SERVER_URL) ..."
	@if [ ! -d "$(IPERF_SOURCE)" ]; then \
		cd $(IPERF_DIR); \
		$(TOP_DOWNLOAD) $(IPERF_SERVER_URL); \
	fi
	@echo "Downloading $(IPERF) done"
	@touch $@

#
# Unpack the source
#
.PHONY: iperf-unpacked

iperf-unpacked: $(IPERF_DIR)/.iperf_unpacked

$(IPERF_DIR)/.iperf_unpacked: $(IPERF_DIR)/.iperf_downloaded
	@touch $@


#
# Patch the source
#
.PHONY: iperf-patched

iperf-patched: $(IPERF_DIR)/.iperf_patched

$(IPERF_DIR)/.iperf_patched: $(IPERF_DIR)/.iperf_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: iperf-config

iperf-config: 

#
# Configuration
#
.PHONY: iperf-configured

iperf-configured:  iperf-config $(IPERF_DIR)/.iperf_configured

$(IPERF_DIR)/.iperf_configured: $(IPERF_DIR)/.iperf_patched
	@echo "Configuring $(IPERF) ..."
#cd $(IPERF_DIR)/$(IPERF);./configure ac_cv_func_malloc_0_nonnull=yes --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) --without-random --without-ssl --disable-ldap LDFLAGS="-lc -pthread" 
	cd $(IPERF_DIR)/$(IPERF);./configure ac_cv_func_malloc_0_nonnull=yes --prefix=$(TOP_INSTALL_ROOTFS_DIR) --build=$(BUILD_HOST) --host=$(BUILD_TARGET)
	@echo "Configuring $(IPERF) done"
	@touch $@

#
# Compile
#
.PHONY: iperf-compile

iperf-compile: $(IPERF_DIR)/.iperf_compiled

$(IPERF_DIR)/.iperf_compiled: $(IPERF_DIR)/.iperf_configured
	@echo "Compiling $(IPERF) ..."
	make -C $(IPERF_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) LDFLAGS="-lc -pthread"
	@echo "Compiling $(IPERF) done"
	@touch $@

#
# Update
#
.PHONY: iperf-update

iperf-update:
	@echo "Updating $(IPERF) ..."
	@if [ -d "$(IPERF_SOURCE)" ]; then\
		$(TOP_UPDATE) $(IPERF_SOURCE); \
	fi
	@echo "Updating $(IPERF) done"

#
# Status
#
.PHONY: iperf-status

iperf-status:
	@echo "Statusing $(IPERF) ..."
	@if [ -d "$(IPERF_SOURCE)" ]; then\
		$(TOP_STATUS) $(IPERF_SOURCE); \
	fi
	@echo "Statusing $(IPERF) done"

#
# Clean
#
.PHONY: iperf-clean

iperf-clean:
	@rm -f $(IPERF_DIR)/.iperf_configured
	@if [ -d "$(IPERF_SOURCE)" ]; then\
		make -C $(IPERF_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: iperf-distclean

iperf-distclean:
	@rm -f $(IPERF_DIR)/.iperf*

#
# Install
#
.PHONY: iperf-install

iperf-install:
	@if [ -d "$(IPERF_SOURCE)" ]; then\
		make -C $(IPERF_SOURCE) install; \
	fi
