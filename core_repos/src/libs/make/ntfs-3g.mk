##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  joshua_lee@alphanetworks.com
# ntfs-3g makefile fragments 
##############################################################################

ifndef	CONF_NTFS_3G_VERSION
CONF_NTFS_3G_VERSION := 2009.2.1
endif

#
# Defines
#

NTFS-3G             := ntfs-3g-$(CONF_NTFS_3G_VERSION)#
NTFS-3G_SERVER_URL  := $(TOP_LIBS_URL)/ntfs-3g/$(NTFS-3G)
NTFS-3G_DIR         := $(TOP_LIBS_DIR)#
NTFS-3G_SOURCE      := $(NTFS-3G_DIR)/$(NTFS-3G)
NTFS-3G_CONFIG      := 

NTFS-3G_CONFIGURE   := CFLAGS=$(NTFS-3G_CFLAGS) LDFLAGS=$(NTFS-3G_LDFLAGS) \
	./configure --prefix=$(LIBS_INSTALL_PATH) \
	--build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) \
	--enable-shared=$(ENABLE_SHLIB) --disable-library --disable-ldconfig 

#--prefix=$(TOP_LIBS_DIR) \
#	--exec-prefix=$(TOP_INSTALL_ROOTFS_DIR) \
#	--program-prefix='' \

#
# Download  the source 
#
.PHONY: ntfs-3g-downloaded

ntfs-3g-downloaded: $(NTFS-3G_DIR)/.ntfs-3g_downloaded

$(NTFS-3G_DIR)/.ntfs-3g_downloaded:
	@echo "Downloading $(NTFS-3G) from $(NTFS-3G_SERVER_URL) ..."
	@touch $@

#
# Unpack the source
#
.PHONY: ntfs-3g-unpacked

ntfs-3g-unpacked: $(NTFS-3G_DIR)/.ntfs-3g_unpacked

$(NTFS-3G_DIR)/.ntfs-3g_unpacked: $(NTFS-3G_DIR)/.ntfs-3g_downloaded
	@echo "Unpacking $(NTFS-3G) ..."
	if [ -d "$(NTFS-3G_SOURCE)/$(NTFS-3G)" ]; then \
		rm -fr $(NTFS-3G_SOURCE)/$(NTFS-3G); \
	fi
	cd $(NTFS-3G_SOURCE); tar zxvf $(NTFS-3G).tgz
	@echo "Unpacking $(NTFS-3G) done"
	@touch $@


#
# Patch the source
#
.PHONY: ntfs-3g-patched

ntfs-3g-patched: $(NTFS-3G_DIR)/.ntfs-3g_patched

$(NTFS-3G_DIR)/.ntfs-3g_patched: $(NTFS-3G_DIR)/.ntfs-3g_unpacked
	# Patching...
	@touch $@


#
# Configuration
#
.PHONY: ntfs-3g-configured

ntfs-3g-configured:  $(NTFS-3G_DIR)/.ntfs-3g_configured

$(NTFS-3G_DIR)/.ntfs-3g_configured: $(NTFS-3G_DIR)/.ntfs-3g_patched $(TOP_CURRENT_SET)
	@echo "Configuring $(NTFS-3G) ..."
	cd $(NTFS-3G_SOURCE)/$(NTFS-3G);${NTFS-3G_CONFIGURE}
	@echo "Configuring $(NTFS-3G) done"
	@touch $@

#
# Compile
#
.PHONY: ntfs-3g-compile

ntfs-3g-compile: ntfs-3g-configured $(NTFS-3G_DIR)/.ntfs-3g_compile

$(NTFS-3G_DIR)/.ntfs-3g_compile:
	@echo "Compiling $(NTFS-3G) ..." 
	-make -C $(NTFS-3G_SOURCE)/$(NTFS-3G) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS=$(NTFS-3G_CFLAGS) LDFLAGS=$(NTFS-3G_LDFLAGS)
	@echo "Compiling $(NTFS-3G) done" 
	touch $@

#
# Update
#
.PHONY: ntfs-3g-update

ntfs-3g-update:
	@echo "Updating $(NTFS-3G) ..."
	@if [ -d "$(NTFS-3G_SOURCE)" ]; then\
		$(TOP_UPDATE) $(NTFS-3G_SOURCE); \
	fi
	@echo "Updating $(NTFS-3G) done"

#
# Status
#
.PHONY: ntfs-3g-status

ntfs-3g-status:
	@echo "Statusing $(NTFS-3G) ..."
	@echo "Statusing $(NTFS-3G) done"

#
# Clean
#
.PHONY: ntfs-3g-clean

ntfs-3g-clean:
	@rm -f $(NTFS-3G_DIR)/.ntfs-3g_configured
	@if [ -d "$(NTFS-3G_SOURCE)" ]; then\
		make -C $(NTFS-3G_SOURCE)/$(NTFS-3G) clean; \
	fi

#
# Dist clean
#
.PHONY: ntfs-3g-distclean

ntfs-3g-distclean:
	@rm -f $(NTFS-3G_DIR)/.ntfs-3g_*

#
# Install
#
.PHONY: ntfs-3g-install

ntfs-3g-install:
	#-make -C $(NTFS-3G_SOURCE)/$(NTFS-3G)  CC=$(CC) CROSS_COMPILE="$(CROSS)" DESTDIR=$(TOP_INSTALL_ROOTFS_DIR) install
	#cp -f $(NTFS-3G_SOURCE)/$(NTFS-3G)/src/ntfs-3g $(TOP_INSTALL_ROOTFS_DIR)/bin
	cd $(TOP_INSTALL_ROOTFS_DIR)/bin; ln -fs ntfs-3g mount.ntfs-3g
	#cp -f $(NTFS-3G_SOURCE)/$(NTFS-3G)/src/ntfs-3g.probe $(TOP_INSTALL_ROOTFS_DIR)/bin

