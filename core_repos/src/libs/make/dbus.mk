##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# mxml makefile fragments 
##############################################################################

#
# Defines
#
DBUS_VERSION := 1.3.0

DBUS             := dbus-$(DBUS_VERSION)#
DBUS_SERVER_URL  := $(TOP_LIBS_URL)/dbus/dbus-$(DBUS_VERSION)
DBUS_DIR         := $(TOP_LIBS_DIR)#
DBUS_SOURCE      := $(DBUS_DIR)/dbus-$(DBUS_VERSION)
DBUS_BUILD       := $(DBUS_SOURCE)/dbus-$(DBUS_VERSION)
DBUS_CONFIG      := 

DBUS_PREFIX	:= /opt

ifeq (x$(ENABLE_SHLIB),xno)
	DBUS_SHARED_FLAGS      := --enable-shared=no
endif

#
# Download  the source 
#
.PHONY: dbus-downloaded

dbus-downloaded: $(DBUS_DIR)/.dbus_downloaded

$(DBUS_DIR)/.dbus_downloaded:
	@echo "Downloading $(DBUS) from $(DBUS_SERVER_URL) ..."
	@if [ ! -d "$(DBUS_SOURCE)" ]; then \
		cd $(DBUS_DIR); \
		$(TOP_DOWNLOAD) $(DBUS_SERVER_URL); \
	fi
	@echo "Downloading $(DBUS) done"
	@touch $@

#
# Unpack the source
#
.PHONY: dbus-unpacked

dbus-unpacked: $(DBUS_DIR)/.dbus_unpacked

$(DBUS_DIR)/.dbus_unpacked: $(DBUS_DIR)/.dbus_downloaded $(wildcard $(DBUS_SOURCE)/*.tar.gz) $(wildcard $(DBUS_SOURCE)/$(DBUS)*.patch)
	@echo "Unpacking $(DBUS) ..."
	if [ -d "$(DBUS_SOURCE)/$(DBUS)" ]; then \
		rm -fr $(DBUS_SOURCE)/$(DBUS); \
	fi
	cd $(DBUS_SOURCE); tar zxvf $(DBUS).tar.gz
	@echo "Unpacking $(DBUS) done"
	@touch $@


#
# Patch the source
#
.PHONY: dbus-patched

dbus-patched: $(DBUS_DIR)/.dbus_patched

$(DBUS_DIR)/.dbus_patched: $(DBUS_DIR)/.dbus_unpacked 
	@echo "Patching $(DBUS) ..."
	cd $(DBUS_SOURCE)/$(DBUS);patch -p1 < ../$(DBUS)-launch-helper-xml-fix.patch
	@echo "Patching $(DBUS) done"
	@touch $@

#
# config
#
.PHONY: dbus-config

dbus-config: 

#
# Configuration
#
.PHONY: dbus-configured

dbus-configured:  dbus-config $(DBUS_DIR)/.dbus_configured

$(DBUS_DIR)/.dbus_configured: $(DBUS_DIR)/.dbus_patched $(DBUS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(DBUS) ..."
	cd $(DBUS_BUILD);$(DBUS_SOURCE)/$(DBUS)/configure \
		--prefix=$(DBUS_PREFIX) \
		--build=$(BUILD_HOST)  \
		--host=$(BUILD_TARGET) \
		--target=$(BUILD_TARGET) \
		$(DBUS_SHARED_FLAGS) \
		ac_cv_have_abstract_sockets=yes \
		LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib"  CFLAGS="-I$(LIBS_INSTALL_PATH)/include" \
		--enable-tests \
		 --with-xml=expat  \
		 --without-x  \
                 --program-prefix="" \
                 --with-dbus-user=dbus \
                 --disable-asserts \
                 --enable-abstract-sockets \
                 --disable-selinux \
                 --disable-xml-docs \
                 --disable-doxygen-docs \
                 --localstatedir=/var \
		 --with-session-socket-dir=/tmp \
                 --with-system-socket=/tmp/system_bus_socket \
                 --with-system-pid-file=/tmp/messagebus.pid
	@echo "Configuring $(DBUS) done"
	@touch $@

#
# Compile
#
.PHONY: dbus-compile

dbus-compile: $(DBUS_DIR)/.dbus_compiled

$(DBUS_DIR)/.dbus_compiled: $(DBUS_DIR)/.dbus_configured 
	@echo "Compiling $(DBUS) ..."
	@make -C $(DBUS_BUILD) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	@make -C $(DBUS_BUILD) install DESTDIR=$(LIBS_INSTALL_PATH)
	@cp -f $(DBUS_BUILD)/dbus/dbus-arch-deps.h $(LIBS_INSTALL_PATH)/$(DBUS_PREFIX)/include/dbus-1.0/dbus
	@echo "Compiling $(DBUS) done"
	@touch $@

#
# Update
#
.PHONY: dbus-update

dbus-update:
	@echo "Updating $(DBUS) ..."
	@if [ -d "$(DBUS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(DBUS_SOURCE); \
	fi
	@echo "Updating $(DBUS) done"

#
# Status
#
.PHONY: dbus-status

dbus-status:
	@echo "Statusing $(DBUS) ..."
	@if [ -d "$(DBUS_SOURCE)" ]; then\
		$(TOP_STATUS) $(DBUS_SOURCE); \
	fi
	@echo "Statusing $(DBUS) done"

#
# Clean
#
.PHONY: dbus-clean

dbus-clean:
	@rm -f $(DBUS_DIR)/.dbus_configured
	@if [ -d "$(DBUS_BUILD)" ]; then\
		make -C $(DBUS_BUILD) clean; \
	fi

#
# Dist clean
#
.PHONY: dbus-distclean

dbus-distclean:
	@rm -f $(DBUS_DIR)/.dbus_*
#@rm -fr $(DBUS_SOURCE)

#
# Install
#
.PHONY: dbus-install

dbus-install:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/$(DBUS_PREFIX)/bin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/$(DBUS_PREFIX)/lib
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/$(DBUS_PREFIX)/etc
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/lib
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc
	cp -af $(LIBS_INSTALL_PATH)/$(DBUS_PREFIX)/bin/dbus-* $(TOP_INSTALL_ROOTFS_DIR)/$(DBUS_PREFIX)/bin 
	cp -af $(LIBS_INSTALL_PATH)/$(DBUS_PREFIX)/lib/libdbus*so* $(TOP_INSTALL_ROOTFS_DIR)/lib
	cp -af $(DBUS_SOURCE)/dbus.conf $(TOP_INSTALL_ROOTFS_DIR)/etc

