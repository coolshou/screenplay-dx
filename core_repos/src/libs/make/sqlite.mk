##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  joshua_lee@alphanetworks.com
# sqlite makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_SQLITE_VERSION 
CONF_SQLITE_VERSION := 3.6.11
endif

SQLITE             := sqlite-amalgamation-$(CONF_SQLITE_VERSION)#
SQLITE_SERVER_URL  := $(TOP_LIBS_URL)/sqlite/$(SQLITE)
SQLITE_DIR         := $(TOP_LIBS_DIR)#
SQLITE_SOURCE      := $(SQLITE_DIR)/$(SQLITE)
SQLITE_SOURCE_DIR      := $(SQLITE_SOURCE)/sqlite-$(CONF_SQLITE_VERSION)
SQLITE_CONFIG      := 


#
# Download  the source 
#
.PHONY: sqlite-downloaded

sqlite-downloaded: $(SQLITE_DIR)/.sqlite_downloaded

$(SQLITE_DIR)/.sqlite_downloaded:
	@echo "Downloading $(SQLITE) from $(SQLITE_SERVER_URL) ..."
	@if [ ! -d "$(SQLITE_SOURCE)" ]; then \
		cd $(SQLITE_DIR); \
		$(TOP_DOWNLOAD) $(SQLITE_SERVER_URL); \
	fi
	@echo "Downloading $(SQLITE) done"
	@touch $@

#
# Unpack the source
#
.PHONY: sqlite-unpacked

sqlite-unpacked: $(SQLITE_DIR)/.sqlite_unpacked

$(SQLITE_DIR)/.sqlite_unpacked: $(SQLITE_DIR)/.sqlite_downloaded
	@echo "Unpacking $(SQLITE) ..."
	if [ -d "$(SQLITE_SOURCE_DIR)" ]; then \
		rm -fr $(SQLITE_SOURCE_DIR); \
	fi
	cd $(SQLITE_SOURCE); tar zxvf $(SQLITE).tar.gz
	@echo "Unpacking $(SQLITE) done"
	@touch $@


#
# Patch the source
#
.PHONY: sqlite-patched

sqlite-patched: $(SQLITE_DIR)/.sqlite_patched

$(SQLITE_DIR)/.sqlite_patched: $(SQLITE_DIR)/.sqlite_unpacked
	# Patching...
	(cd $(SQLITE_SOURCE_DIR);sed -i -e "s/sqlite 3.6.11/sqlite_3.6.11/" configure;)
	@touch $@


#
# Configuration
#
.PHONY: sqlite-configured

sqlite-configured:  $(SQLITE_DIR)/.sqlite_configured

$(SQLITE_DIR)/.sqlite_configured: $(SQLITE_DIR)/.sqlite_patched $(TOP_CURRENT_SET)
	@echo "Configuring $(SQLITE) ..."
	cd $(SQLITE_SOURCE_DIR);CFLAGS=$(SQLITE_CFLAGS) LDFLAGS=$(SQLITE_LDFLAGS)  ./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) --enable-readline=no --enable-dynamic-extensions=no --enable-static=no
	@echo "Configuring $(SQLITE) done"
	@touch $@

#
# Compile
#
.PHONY: sqlite-compile

sqlite-compile: sqlite-configured $(SQLITE_DIR)/.sqlite_compile

$(SQLITE_DIR)/.sqlite_compile:
	@echo "Compiling $(SQLITE) ..." 
	-make -C $(SQLITE_SOURCE_DIR) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS=$(SQLITE_CFLAGS) LDFLAGS=$(SQLITE_LDFLAGS) install
	@echo "Compiling $(SQLITE) done" 
	touch $@

#
# Update
#
.PHONY: sqlite-update

sqlite-update:
	@echo "Updating $(SQLITE) ..."
	@if [ -d "$(SQLITE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SQLITE_SOURCE); \
	fi
	@echo "Updating $(SQLITE) done"

#
# Status
#
.PHONY: sqlite-status

sqlite-status:
	@echo "Statusing $(SQLITE) ..."
	@echo "Statusing $(SQLITE) done"

#
# Clean
#
.PHONY: sqlite-clean

sqlite-clean:
	@rm -f $(SQLITE_DIR)/.sqlite_configured
	@if [ -d "$(SQLITE_SOURCE)" ]; then\
		make -C $(SQLITE_SOURCE_DIR) clean; \
	fi

#
# Dist clean
#
.PHONY: sqlite-distclean

sqlite-distclean:
	@rm -f $(SQLITE_DIR)/.sqlite_*

#
# Install
#
.PHONY: sqlite-install

sqlite-install:
ifeq  (x$(CONF_SQLITE_DEBUG), xy)
	-cp -f $(SQLITE_SOURCE_DIR)/.libs/sqlite3 $(TOP_INSTALL_ROOTFS_DIR)/bin
endif
