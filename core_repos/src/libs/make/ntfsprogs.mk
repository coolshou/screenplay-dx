#
# Defines
#
ifndef  NTFSPROGS_VERSION 
NTFSPROGS_VERSION := 2.0.0
endif

NTFSPROGS             := ntfsprogs-$(NTFSPROGS_VERSION)#
NTFSPROGS_SERVER_URL  := $(TOP_LIBS_URL)/ntfsprogs/$(NTFSPROGS)
NTFSPROGS_DIR         := $(TOP_LIBS_DIR)#
NTFSPROGS_SOURCE      := $(NTFSPROGS_DIR)/$(NTFSPROGS)
NTFSPROGS_CONFIG      := 
NTFSPROGS_LDFLAGS     := -L$(LIBS_INSTALL_PATH)/lib 

#
# Download  the source 
#
.PHONY: ntfsprogs-downloaded

ntfsprogs-downloaded: $(NTFSPROGS_DIR)/.ntfsprogs_downloaded

$(NTFSPROGS_DIR)/.ntfsprogs_downloaded:
	@echo "Downloading $(NTFSPROGS) from $(NTFSPROGS_SERVER_URL) ..."
	@if [ ! -d "$(NTFSPROGS_SOURCE)" ]; then \
		cd $(NTFSPROGS_DIR); \
		$(TOP_DOWNLOAD) $(NTFSPROGS_SERVER_URL); \
	fi
	@echo "Downloading $(NTFSPROGS) done"
	@touch $@

#
# Unpack the source
#
.PHONY: ntfsprogs-unpacked

ntfsprogs-unpacked: $(NTFSPROGS_DIR)/.ntfsprogs_unpacked

$(NTFSPROGS_DIR)/.ntfsprogs_unpacked: $(NTFSPROGS_DIR)/.ntfsprogs_downloaded
	@echo "Unpacking $(NTFSPROGS) ..."
	if [ -d "$(NTFSPROGS_SOURCE)/$(NTFSPROGS)" ]; then \
		rm -fr $(NTFSPROGS_SOURCE)/$(NTFSPROGS); \
	fi
	cd $(NTFSPROGS_SOURCE); tar zxvf $(NTFSPROGS).tar.gz
	@echo "Unpacking $(NTFSPROGS) done"
	@touch $@


#
# Patch the source
#
.PHONY: ntfsprogs-patched

ntfsprogs-patched: $(NTFSPROGS_DIR)/.ntfsprogs_patched

$(NTFSPROGS_DIR)/.ntfsprogs_patched: $(NTFSPROGS_DIR)/.ntfsprogs_unpacked
	# Patching...
	@touch $@


#
# Configuration
#
.PHONY: ntfsprogs-configured

ntfsprogs-configured:  $(NTFSPROGS_DIR)/.ntfsprogs_configured

$(NTFSPROGS_DIR)/.ntfsprogs_configured: $(NTFSPROGS_DIR)/.ntfsprogs_patched $(TOP_CURRENT_SET)
	@echo "Configuring $(NTFSPROGS) ..."
	cd $(NTFSPROGS_SOURCE)/$(NTFSPROGS);CFLAGS=$(NTFSPROGS_CFLAGS) LDFLAGS=$(NTFSPROGS_LDFLAGS)  ./configure --prefix=$(TOP_LIBS_DIR) --exec-prefix=$(TOP_INSTALL_ROOTFS_DIR) --program-prefix='' --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) --disable-library --disable-ldconfig --disable-ntfsmount 
	@echo "Configuring $(NTFSPROGS) done"
	@touch $@

#
# Compile
#
.PHONY: ntfsprogs-compile

ntfsprogs-compile:  $(NTFSPROGS_DIR)/.ntfsprogs_compiled
$(NTFSPROGS_DIR)/.ntfsprogs_compiled:  $(NTFSPROGS_DIR)/.ntfsprogs_configured
	@echo "Compiling $(NTFSPROGS) ..." 
	-make -C $(NTFSPROGS_SOURCE)/$(NTFSPROGS) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS=$(NTFSPROGS_CFLAGS) LDFLAGS=$(NTFSPROGS_LDFLAGS)
	@echo "Compiling $(NTFSPROGS) done" 
	@touch $@

#
# Update
#
.PHONY: ntfsprogs-update

ntfsprogs-update:
	@echo "Updating $(NTFSPROGS) ..."
	@if [ -d "$(NTFSPROGS_SOURCE)" ]; then\
		$(TOP_UPDATE) $(NTFSPROGS_SOURCE); \
	fi
	@echo "Updating $(NTFSPROGS) done"

#
# Status
#
.PHONY: ntfsprogs-status

ntfsprogs-status:
	@echo "Statusing $(NTFSPROGS) ..."
	@echo "Statusing $(NTFSPROGS) done"

#
# Clean
#
.PHONY: ntfsprogs-clean

ntfsprogs-clean:
	@rm -f $(NTFSPROGS_DIR)/.ntfsprogs_configured
	@if [ -d "$(NTFSPROGS_SOURCE)" ]; then\
		make -C $(NTFSPROGS_SOURCE)/$(NTFSPROGS) clean; \
	fi

#
# Dist clean
#
.PHONY: ntfsprogs-distclean

ntfsprogs-distclean:
	@rm -f $(NTFSPROGS_DIR)/.ntfsprogs_*

#
# Install
#
.PHONY: ntfsprogs-install

ntfsprogs-install:
	-cp -af $(NTFSPROGS_SOURCE)/$(NTFSPROGS)/libntfs/.libs/*so* $(TOP_INSTALL_ROOTFS_DIR)/lib
	-cp -f  $(NTFSPROGS_SOURCE)/$(NTFSPROGS)/ntfsprogs/.libs/mkntfs $(TOP_INSTALL_ROOTFS_DIR)/bin
