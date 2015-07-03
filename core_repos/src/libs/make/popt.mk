##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# popt makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_POPT_VERSION 
CONF_POPT_VERSION := 1.10.4
endif

POPT             := popt-$(CONF_POPT_VERSION)#
POPT_SERVER_URL  := $(TOP_LIBS_URL)/popt/$(POPT)
POPT_DIR         := $(TOP_LIBS_DIR)#
POPT_SOURCE      := $(POPT_DIR)/$(POPT)
POPT_CONFIG      := 

#
# Download  the source 
#
.PHONY: popt-downloaded

popt-downloaded: $(POPT_DIR)/.popt_downloaded

$(POPT_DIR)/.popt_downloaded:
	@echo "Downloading $(POPT) from $(POPT_SERVER_URL) ..."
	@if [ ! -d "$(POPT_SOURCE)" ]; then \
		cd $(POPT_DIR); \
		$(TOP_DOWNLOAD) $(POPT_SERVER_URL); \
	fi
	@echo "Downloading $(POPT) from $(POPT_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: popt-unpacked

popt-unpacked: $(POPT_DIR)/.popt_unpacked

$(POPT_DIR)/.popt_unpacked: $(POPT_DIR)/.popt_downloaded $(POPT_SOURCE)/$(POPT).tar.gz
	@echo "Unpacking $(POPT) ..."
	if [ -d "$(POPT_SOURCE)/$(POPT)" ]; then \
		rm -fr $(POPT_SOURCE)/$(POPT); \
	fi
	cd $(POPT_SOURCE); tar zxvf $(POPT).tar.gz
	@echo "Unpacking $(POPT) done"
	@touch $@


#
# Patch the source
#
.PHONY: popt-patched

popt-patched: $(POPT_DIR)/.popt_patched

$(POPT_DIR)/.popt_patched: $(POPT_DIR)/.popt_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: popt-config

popt-config: 

#
# Configuration
#
.PHONY: popt-configured

popt-configured:  popt-config $(POPT_DIR)/.popt_configured

$(POPT_DIR)/.popt_configured: $(POPT_DIR)/.popt_patched $(POPT_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(POPT) ..."
	cd $(POPT_SOURCE)/$(POPT);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=no --enable-static=yes 
	@echo "Configuring $(POPT) done"
	@touch $@

#
# Compile
#
.PHONY: popt-compile

popt-compile: $(POPT_DIR)/.popt_compiled

$(POPT_DIR)/.popt_compiled: $(POPT_DIR)/.popt_configured
	@echo "Compiling $(POPT) ..."
	#make -C $(POPT_SOURCE)/$(POPT) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(POPT_SOURCE)/$(POPT) 
	make -C $(POPT_SOURCE)/$(POPT)  install
	@echo "Compiling $(POPT) done"
	@touch $@

#
# Update
#
.PHONY: popt-update

popt-update:
	@echo "Updating $(POPT) ..."
	@if [ -d "$(POPT_SOURCE)" ]; then\
		$(TOP_UPDATE) $(POPT_SOURCE); \
	fi
	@echo "Updating $(POPT) done"

#
# Status
#
.PHONY: popt-status

popt-status:
	@echo "Statusing $(POPT) ..."
	@if [ -d "$(POPT_SOURCE)" ]; then\
		$(TOP_STATUS) $(POPT_SOURCE); \
	fi
	@echo "Statusing $(POPT) done"

#
# Clean
#
.PHONY: popt-clean

popt-clean:
	@rm -f $(POPT_DIR)/.popt_configured
	@if [ -d "$(POPT_SOURCE)" ]; then\
		make -C $(POPT_SOURCE)/$(POPT) clean; \
	fi

#
# Dist clean
#
.PHONY: popt-distclean

popt-distclean:
	@rm -f $(POPT_DIR)/.popt_*

#
# Install
#
.PHONY: popt-install

popt-install:
