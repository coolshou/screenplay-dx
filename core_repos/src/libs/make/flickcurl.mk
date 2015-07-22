##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  divers_dai@alphanetworks.com
# flickcurl makefile fragments 
##############################################################################

#
# Defines
#
ifndef  FLICKCURL_VERSION 
FLICKCURL_VERSION := 1.26
endif

FLICKCURL             := flickcurl-$(FLICKCURL_VERSION)#
FLICKCURL_SERVER_URL  := $(TOP_LIBS_URL)/flickcurl/$(FLICKCURL)#
FLICKCURL_DIR         := $(TOP_LIBS_DIR)#
FLICKCURL_SOURCE      := $(FLICKCURL_DIR)/$(FLICKCURL)#
FLICKCURL_CONFIG      := 

ifndef  CONF_CURL_VERSION
CONF_CURL_VERSION := 7.16.0
endif
CURL             := curl-$(CONF_CURL_VERSION)#
CURL_DIR         := $(TOP_LIBS_DIR)#
CURL_SOURCE      := $(CURL_DIR)/$(CURL)#

ifndef  LIBXML2VERSION
LIBXML2VERSION := 2.6.13
endif

LIBXML2             := libxml2-$(LIBXML2VERSION)#
LIBXML2_SERVER_URL  := $(TOP_LIBS_URL)/libxml2/$(LIBXML2)
LIBXML2_DIR         := $(TOP_LIBS_DIR)#
LIBXML2_SOURCE      := $(LIBXML2_DIR)/$(LIBXML2)



#
# Download  the source 
#
.PHONY: flickcurl-downloaded

flickcurl-downloaded: $(FLICKCURL_DIR)/.flickcurl_downloaded

$(FLICKCURL_DIR)/.flickcurl_downloaded:
	@echo "Downloading $(FLICKCURL) from $(FLICKCURL_SERVER_URL) ..."
	@if [ ! -d "$(FLICKCURL_SOURCE)" ]; then \
		cd $(FLICKCURL_DIR); \
		$(TOP_DOWNLOAD) $(FLICKCURL_SERVER_URL); \
	fi
	@echo "Downloading $(FLICKCURL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: flickcurl-unpacked

flickcurl-unpacked: $(FLICKCURL_DIR)/.flickcurl_unpacked

$(FLICKCURL_DIR)/.flickcurl_unpacked: $(FLICKCURL_DIR)/.flickcurl_downloaded $(FLICKCURL_SOURCE)/$(FLICKCURL).tar.gz
	@echo "Unpacking $(FLICKCURL) ..."
	if [ -d "$(FLICKCURL_SOURCE)/$(FLICKCURL)" ]; then \
		rm -fr $(FLICKCURL_SOURCE)/$(FLICKCURL); \
	fi
	(cd $(FLICKCURL_SOURCE); tar zxvf $(FLICKCURL).tar.gz)
	@echo "Unpacking $(FLICKCURL) done"
	@touch $@


#
# Patch the source
#
.PHONY: flickcurl-patched

flickcurl-patched: $(FLICKCURL_DIR)/.flickcurl_patched

$(FLICKCURL_DIR)/.flickcurl_patched: $(FLICKCURL_DIR)/.flickcurl_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: flickcurl-config

flickcurl-config: 

#
# Configuration
#
.PHONY: flickcurl-configured

flickcurl-configured:  flickcurl-config $(FLICKCURL_DIR)/.flickcurl_configured

$(FLICKCURL_DIR)/.flickcurl_configured: $(FLICKCURL_DIR)/.flickcurl_patched $(FLICKCURL_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FLICKCURL) ..."
	chmod +x $(CURL_SOURCE)/$(CURL)/curl-config
	cd $(FLICKCURL_SOURCE)/$(FLICKCURL);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) ac_cv_func_vsnprintf=no ac_cv_func_malloc_0_nonnull=yes enable_gtk_doc="no" --with-xml2-config="$(LIBXML2_SOURCE)/$(LIBXML2)/xml2-config" --with-curl-config="$(CURL_SOURCE)/$(CURL)/curl-config" --with-raptor=no --disable-shared LDFLAGS="" COMPILKIND=glibc
	@echo "Configuring $(FLICKCURL) done"
	@touch $@

#
# Compile
#
.PHONY: flickcurl-compile

flickcurl-compile: $(FLICKCURL_DIR)/.flickcurl_compiled

$(FLICKCURL_DIR)/.flickcurl_compiled: $(FLICKCURL_DIR)/.flickcurl_configured
	@echo "Compiling $(FLICKCURL) ..."
	make -C $(FLICKCURL_SOURCE)/$(FLICKCURL) LDFLAGS=""
	make -C $(FLICKCURL_SOURCE)/$(FLICKCURL) install
	cp $(FLICKCURL_SOURCE)/$(FLICKCURL)/src/flickcurl_internal.h $(LIBS_INSTALL_PATH)/include/
	@echo "Compiling $(FLICKCURL) done"
	@touch $@

#
# Update
#
.PHONY: flickcurl-update

flickcurl-update:
	@echo "Updating $(FLICKCURL) ..."
	@if [ -d "$(FLICKCURL_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FLICKCURL_SOURCE); \
	fi
	@echo "Updating $(FLICKCURL) done"

#
# Status
#
.PHONY: flickcurl-status

flickcurl-status:
	@echo "Statusing $(FLICKCURL) ..."
	@if [ -d "$(FLICKCURL_SOURCE)" ]; then\
		$(TOP_STATUS) $(FLICKCURL_SOURCE); \
	fi
	@echo "Statusing $(FLICKCURL) done"

#
# Clean
#
.PHONY: flickcurl-clean

flickcurl-clean:
	@rm -f $(FLICKCURL_DIR)/.flickcurl_configured
	@if [ -d "$(FLICKCURL_SOURCE)" ]; then\
		make -C $(FLICKCURL_SOURCE)/$(FLICKCURL) clean; \
	fi

#
# Dist clean
#
.PHONY: flickcurl-distclean

flickcurl-distclean:
	@rm -f $(FLICKCURL_DIR)/.flickcurl_*

#
# Install
#
.PHONY: flickcurl-install

flickcurl-install:
