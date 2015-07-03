##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# pcre makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_PCRE_VERSION 
CONF_PCRE_VERSION := 8.02
endif

PCRE             := pcre-$(CONF_PCRE_VERSION)#
PCRE_SERVER_URL  := $(TOP_LIBS_URL)/pcre/$(PCRE)
PCRE_DIR         := $(TOP_LIBS_DIR)#
PCRE_SOURCE      := $(PCRE_DIR)/$(PCRE)
PCRE_CONFIG      := 

#
# Download  the source 
#
.PHONY: pcre-downloaded

pcre-downloaded: $(PCRE_DIR)/.pcre_downloaded

$(PCRE_DIR)/.pcre_downloaded:
	@echo "Downloading $(PCRE) from $(PCRE_SERVER_URL) ..."
	@if [ ! -d "$(PCRE_SOURCE)" ]; then \
		cd $(PCRE_DIR); \
		$(TOP_DOWNLOAD) $(PCRE_SERVER_URL); \
	fi
	@echo "Downloading $(PCRE) from $(PCRE_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: pcre-unpacked

pcre-unpacked: $(PCRE_DIR)/.pcre_unpacked

$(PCRE_DIR)/.pcre_unpacked: $(PCRE_DIR)/.pcre_downloaded $(PCRE_SOURCE)/$(PCRE).tar.gz
	@echo "Unpacking $(PCRE) ..."
	if [ -d "$(PCRE_SOURCE)/$(PCRE)" ]; then \
		rm -fr $(PCRE_SOURCE)/$(PCRE); \
	fi
	cd $(PCRE_SOURCE); tar zxvf $(PCRE).tar.gz
	@echo "Unpacking $(PCRE) done"
	@touch $@


#
# Patch the source
#
.PHONY: pcre-patched

pcre-patched: $(PCRE_DIR)/.pcre_patched

$(PCRE_DIR)/.pcre_patched: $(PCRE_DIR)/.pcre_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: pcre-config

pcre-config: 

#
# Configuration
#
.PHONY: pcre-configured

pcre-configured:  pcre-config $(PCRE_DIR)/.pcre_configured

$(PCRE_DIR)/.pcre_configured: $(PCRE_DIR)/.pcre_patched $(PCRE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(PCRE) ..."
	cd $(PCRE_SOURCE)/$(PCRE);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=no --enable-static=yes 
	@echo "Configuring $(PCRE) done"
	@touch $@

#
# Compile
#
.PHONY: pcre-compile

pcre-compile: $(PCRE_DIR)/.pcre_compiled

$(PCRE_DIR)/.pcre_compiled: $(PCRE_DIR)/.pcre_configured
	@echo "Compiling $(PCRE) ..."
	#make -C $(PCRE_SOURCE)/$(PCRE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(PCRE_SOURCE)/$(PCRE) 
	make -C $(PCRE_SOURCE)/$(PCRE)  install
	@echo "Compiling $(PCRE) done"
	@touch $@

#
# Update
#
.PHONY: pcre-update

pcre-update:
	@echo "Updating $(PCRE) ..."
	@if [ -d "$(PCRE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(PCRE_SOURCE); \
	fi
	@echo "Updating $(PCRE) done"

#
# Status
#
.PHONY: pcre-status

pcre-status:
	@echo "Statusing $(PCRE) ..."
	@if [ -d "$(PCRE_SOURCE)" ]; then\
		$(TOP_STATUS) $(PCRE_SOURCE); \
	fi
	@echo "Statusing $(PCRE) done"

#
# Clean
#
.PHONY: pcre-clean

pcre-clean:
	@rm -f $(PCRE_DIR)/.pcre_configured
	@if [ -d "$(PCRE_SOURCE)" ]; then\
		make -C $(PCRE_SOURCE)/$(PCRE) clean; \
	fi

#
# Dist clean
#
.PHONY: pcre-distclean

pcre-distclean:
	@rm -f $(PCRE_DIR)/.pcre_*

#
# Install
#
.PHONY: pcre-install

pcre-install:
