#
# Defines
#
ifndef CONF_PARTED_VERSION 
PARTED_VERSION := 2.2# 
else
PARTED_VERSION := $(CONF_PARTED_VERSION)
endif

PARTED             := parted-$(PARTED_VERSION)#
PARTED_SERVER_URL  := $(TOP_LIBS_URL)/parted/$(PARTED)#b
PARTED_DIR         := $(TOP_LIBS_DIR)#
PARTED_SOURCE      := $(PARTED_DIR)/$(PARTED)
PARTED_CONFIG      := 

#
# Download  the source 
#
.PHONY: parted-downloaded

parted-downloaded: $(PARTED_DIR)/.parted_downloaded

$(PARTED_DIR)/.parted_downloaded:
	@echo "Downloading $(PARTED) from $(PARTED_SERVER_URL) ..."
	@if [ ! -d "$(PARTED_SOURCE)" ]; then \
		cd $(PARTED_DIR); \
		$(TOP_DOWNLOAD) $(PARTED_SERVER_URL); \
	fi
	@echo "Downloading $(PARTED) from $(PARTED_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: parted-unpacked

parted-unpacked: $(PARTED_DIR)/.parted_unpacked

$(PARTED_DIR)/.parted_unpacked: $(PARTED_DIR)/.parted_downloaded $(PARTED_SOURCE)/$(PARTED).tar.gz
	@echo "Unpacking $(PARTED) ..."
	if [ -d "$(PARTED_SOURCE)/$(PARTED)" ]; then \
		rm -fr $(PARTED_SOURCE)/$(PARTED); \
	fi
	cd $(PARTED_SOURCE); tar xvzf  $(PARTED).tar.gz
	@echo "Unpacking $(PARTED) done"
	@touch $@


#
# Patch the source
#
.PHONY: parted-patched

parted-patched: $(PARTED_DIR)/.parted_patched

$(PARTED_DIR)/.parted_patched: $(PARTED_DIR)/.parted_unpacked
	@touch $@

#
# config
#
.PHONY: parted-config

parted-config: 

#
# Configuration
#
.PHONY: parted-configured

parted-configured:  parted-config $(PARTED_DIR)/.parted_configured

$(PARTED_DIR)/.parted_configured: $(PARTED_DIR)/.parted_patched $(PARTED_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(PARTED) ..."
	cd $(PARTED_SOURCE)/$(PARTED);./configure --disable-shared --enable-shared=no  --without-readline --disable-device-mapper --prefix=$(LIBS_INSTALL_PATH) --host=$(BUILD_TARGET) CFLAGS=-I$(LIBS_INSTALL_PATH)/include LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib"
	@echo "Configuring $(PARTED) done"
	@touch $@

#
# Compile
#
.PHONY: parted-compile

parted-compile: $(PARTED_DIR)/.parted_compiled

$(PARTED_DIR)/.parted_compiled: $(PARTED_DIR)/.parted_configured
	@echo "Compiling $(PARTED) ..."
	make -C $(PARTED_SOURCE)/$(PARTED)/
	@echo "Compiling $(PARTED) done"
	@touch $@

#
# Update
#
.PHONY: parted-update

parted-update:
	@echo "Updating $(PARTED) ..."
	@if [ -d "$(PARTED_SOURCE)" ]; then\
		$(TOP_UPDATE) $(PARTED_SOURCE); \
	fi
	@echo "Updating $(PARTED) done"

#
# Status
#
.PHONY: parted-status

parted-status:
	@echo "Statusing $(PARTED) ..."
	@if [ -d "$(PARTED_SOURCE)" ]; then\
		$(TOP_STATUS) $(PARTED_SOURCE); \
	fi
	@echo "Statusing $(PARTED) done"

#
# Clean
#
.PHONY: parted-clean

parted-clean:
	@rm -f $(PARTED_DIR)/.parted_configured
	@if [ -d "$(PARTED_SOURCE)" ]; then\
		make -C $(PARTED_SOURCE)/$(PARTED)/source clean; \
	fi

#
# Dist clean
#
.PHONY: parted-distclean

parted-distclean:
	@rm -f $(PARTED_DIR)/.parted_*

#
# Install
#
.PHONY: parted-install

parted-install:
	@echo $(TOP_BUILD_ROOTFS_DIR)
	cp -f $(PARTED_SOURCE)/$(PARTED)/parted/parted $(TOP_INSTALL_ROOTFS_DIR)/sbin
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/sbin/parted


