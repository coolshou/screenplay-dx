##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# transmission makefile fragments 
##############################################################################

#
# Defines
#
ifndef  TRANSMISSION_VERSION 
TRANSMISSION_VERSION := 2.03
endif

TRANSMISSION             := transmission-$(TRANSMISSION_VERSION)#
TRANSMISSION_SERVER_URL  := $(TOP_LIBS_URL)/transmission/$(TRANSMISSION)
TRANSMISSION_DIR         := $(TOP_LIBS_DIR)#
TRANSMISSION_SOURCE      := $(TRANSMISSION_DIR)/$(TRANSMISSION)
TRANSMISSION_BUILD_DIR   := $(TRANSMISSION_SOURCE)/$(TRANSMISSION)/build
TRANSMISSION_CONFIG      := 


#
# Download  the source 
#
.PHONY: transmission-downloaded

transmission-downloaded: $(TRANSMISSION_DIR)/.transmission_downloaded

$(TRANSMISSION_DIR)/.transmission_downloaded:
	@echo "Downloading $(TRANSMISSION) from $(TRANSMISSION_SERVER_URL) ..."
	@if [ ! -d "$(TRANSMISSION_SOURCE)" ]; then \
		cd $(TRANSMISSION_DIR); \
		$(TOP_DOWNLOAD) $(TRANSMISSION_SERVER_URL); \
	fi
	@echo "Downloading $(TRANSMISSION) done"
	@touch $@

#
# Unpack the source
#
.PHONY: transmission-unpacked

transmission-unpacked: $(TRANSMISSION_DIR)/.transmission_unpacked

$(TRANSMISSION_DIR)/.transmission_unpacked: $(TRANSMISSION_DIR)/.transmission_downloaded $(wildcard $(TRANSMISSION_SOURCE)/*.tar.bz2)
	@echo "Unpacking $(TRANSMISSION) ..."
	if [ -d "$(TRANSMISSION_SOURCE)/$(TRANSMISSION)" ]; then \
		rm -fr $(TRANSMISSION_SOURCE)/$(TRANSMISSION); \
	fi
	cd $(TRANSMISSION_SOURCE);tar xvjf  $(TRANSMISSION).tar.bz2
	@echo "Unpacking $(TRANSMISSION) done"
	@touch $@


#
# Patch the source
#
.PHONY: transmission-patched

transmission-patched: $(TRANSMISSION_DIR)/.transmission_patched

$(TRANSMISSION_DIR)/.transmission_patched: $(TRANSMISSION_DIR)/.transmission_unpacked
# Patching...
	@echo "Patching $(TRANSMISSION) ..."
#	cd $(TRANSMISSION_SOURCE)/$(TRANSMISSION);patch -p1 < ../$(TRANSMISSION).patch
	cd $(TRANSMISSION_SOURCE);patch -p0 < $(TRANSMISSION).patch
	@echo "Patching $(TRANSMISSION) done"
	@touch $@

#
# config
#
.PHONY: transmission-config

transmission-config: 

#
# Configuration
#
.PHONY: transmission-configured

transmission-configured:  transmission-config $(TRANSMISSION_DIR)/.transmission_configured

$(TRANSMISSION_DIR)/.transmission_configured: $(TRANSMISSION_DIR)/.transmission_patched $(TRANSMISSION_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(TRANSMISSION) ..."
	cd $(TRANSMISSION_SOURCE)/$(TRANSMISSION); ./configure --prefix=$(LIBS_INSTALL_PATH) --exec-prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) \
	    --enable-static=no --enable-daemon --enable-nls --disable-cli --disable-gtk --enable-shared=yes \
	    LIBEVENT_CFLAGS="-I$(LIBEVENT_SOURCE)/$(LIBEVENT)" LIBEVENT_LIBS="-L$(LIBEVENT_SOURCE)/$(LIBEVENT) -levent" \
	    OPENSSL_CFLAGS="-I$(OPENSSL_SOURCE)/$(OPENSSL)/include" OPENSSL_LIBS="-L$(OPENSSL_SOURCE)/$(OPENSSL) -lssl -lcrypto" \
	    LIBCURL_CFLAGS="-I$(CURL_SOURCE)/$(CURL)/include" LIBCURL_LIBS="-L$(CURL_SOURCE)/$(CURL)/lib -lcurl" \
	    ZLIB_CFLAGS="-I$(ZLIB_SOURCE)/$(ZLIB)" ZLIB_LDFLAGS="-L$(ZLIB_SOURCE)/$(ZLIB)"
	@echo "Configuring $(TRANSMISSION) done"
	@touch $@

#
# Compile
#
.PHONY: transmission-compile

transmission-compile: $(TRANSMISSION_DIR)/.transmission_compiled

$(TRANSMISSION_DIR)/.transmission_compiled: $(TRANSMISSION_DIR)/.transmission_configured
	@echo "Compiling $(TRANSMISSION) ..."
	make -C $(TRANSMISSION_SOURCE)/$(TRANSMISSION) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) LDFLAGS="$(LDFLAGS)"
	make -C $(TRANSMISSION_SOURCE)/$(TRANSMISSION) install
	@echo "Compiling $(TRANSMISSION) done"
	@touch $@

#
# Update
#
.PHONY: transmission-update

transmission-update:
	@echo "Updating $(TRANSMISSION) ..."
	@if [ -d "$(TRANSMISSION_SOURCE)" ]; then\
		$(TOP_UPDATE) $(TRANSMISSION_SOURCE); \
	fi
	@echo "Updating $(TRANSMISSION) done"

#
# Status
#
.PHONY: transmission-status

transmission-status:
	@echo "Statusing $(TRANSMISSION) ..."
	@if [ -d "$(TRANSMISSION_SOURCE)" ]; then\
		$(TOP_STATUS) $(TRANSMISSION_SOURCE); \
	fi
	@echo "Statusing $(TRANSMISSION) done"

#
# Clean
#
.PHONY: transmission-clean

transmission-clean:
	@rm -f $(TRANSMISSION_DIR)/.transmission_configured
	@if [ -d "$(TRANSMISSION_SOURCE)" ]; then\
		make -C $(TRANSMISSION_SOURCE)/$(TRANSMISSION) clean; \
	fi

#
# Dist clean
#
.PHONY: transmission-distclean

transmission-distclean:
	@rm -f $(TRANSMISSION_DIR)/.transmission_*

#
# Install
#
.PHONY: transmission-install

transmission-install:
