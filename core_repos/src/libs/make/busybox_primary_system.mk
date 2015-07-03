#
# Defines
#
BUSYBOX_SERVER_URL  := $(TOP_LIBS_URL)/busybox/$(BUSYBOX)
BUSYBOX_DIR         := $(TOP_LIBS_DIR)#

BUSYBOX             := busybox-$(CONF_BUSYBOX_VERSION)#
BUSYBOX_SOURCE      := $(BUSYBOX_DIR)/$(BUSYBOX)
ifeq (x$(CONF_BUSYBOX_1_10_0), xy)
BUSYBOX_CONFIG      := $(TOP_CONFIG_DIR)/busybox-1.10.0-config
endif


#
# Download  the source 
#
.PHONY: busybox_primary_system-downloaded

busybox_primary_system-downloaded: $(BUSYBOX_DIR)/.busybox_primary_system_downloaded

$(BUSYBOX_DIR)/.busybox_primary_system_downloaded:
	@echo "Downloading $(BUSYBOX) from $(BUSYBOX_SERVER_URL) ..."
	@if [ ! -d "$(BUSYBOX_SOURCE)_primary_system" ]; then \
		cd $(BUSYBOX_DIR); \
		$(TOP_DOWNLOAD) $(BUSYBOX_SERVER_URL) $(BUSYBOX)_primary_system; \
	fi
	@echo "Downloading $(BUSYBOX) done"
	@touch $@

#
# Unpack the source
#
.PHONY: busybox_primary_system-unpacked

busybox_primary_system-unpacked: $(BUSYBOX_DIR)/.busybox_primary_system_unpacked

$(BUSYBOX_DIR)/.busybox_primary_system_unpacked: $(BUSYBOX_DIR)/.busybox_primary_system_downloaded
	# Unpacking...
	@touch $@


#
# Patch the source
#
.PHONY: busybox_primary_system-patched

busybox_primary_system-patched: $(BUSYBOX_DIR)/.busybox_primary_system_patched

$(BUSYBOX_DIR)/.busybox_primary_system_patched: $(BUSYBOX_DIR)/.busybox_primary_system_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: busybox_primary_system-config

busybox_primary_system-config: busybox_primary_system-patched 
	@if [ -f $(BUSYBOX_CONFIG)-primary_system ]; then \
		cp -pf $(BUSYBOX_CONFIG)-primary_system $(BUSYBOX_SOURCE)_primary_system/.config; \
	fi
	if [ x$(CONF_BUSYBOX_PRIMARY_SYSTEM_1_10_0_CONFIG_GENERIC_WITH_MODULES) == xy ]; then \
		cp -pf $(BUSYBOX_CONFIG)-primary_system_with_modules $(BUSYBOX_SOURCE)_primary_system/.config; \
	fi

#
# Configuration
#
.PHONY: busybox_primary_system-configured

busybox_primary_system-configured:  busybox_primary_system-config $(BUSYBOX_DIR)/.busybox_primary_system_configured

$(BUSYBOX_DIR)/.busybox_primary_system_configured: $(BUSYBOX_DIR)/.busybox_primary_system_patched $(BUSYBOX_CONFIG)-primary_system $(TOP_CURRENT_SET)
	@echo "Configuring $(BUSYBOX) ..."
	make -C $(BUSYBOX_SOURCE)_primary_system oldconfig
	make -C $(BUSYBOX_SOURCE)_primary_system dep
	@echo "Configuring $(BUSYBOX) done"
	@touch $@

#
# Compile
#
.PHONY: busybox_primary_system-compile

busybox_primary_system-compile: busybox_primary_system-configured $(BUSYBOX_DIR)/.busybox_primary_system_compiled

$(BUSYBOX_DIR)/.busybox_primary_system_compiled:
	@echo "Compiling $(BUSYBOX) ..." 
	-make -C $(BUSYBOX_SOURCE)_primary_system CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)  CROSS_COMPILE="$(CROSS)" -C $(BUSYBOX_SOURCE)_primary_system
	@echo "Compiling $(BUSYBOX) done" 
	touch	$@

#
# Update
#
.PHONY: busybox_primary_system-update

busybox_primary_system-update:
	@echo "Updating $(BUSYBOX) ..."
	@if [ -d "$(BUSYBOX_SOURCE)_primary_system" ]; then\
		$(TOP_UPDATE) $(BUSYBOX_SOURCE)_primary_system; \
	fi
	@echo "Updating $(BUSYBOX) done"

#
# Status
#
.PHONY: busybox_primary_system-status

busybox_primary_system-status:
	@echo "Statusing $(BUSYBOX) ..."
	@if [ -d "$(BUSYBOX_SOURCE)_primary_system" ]; then\
		$(TOP_STATUS) $(BUSYBOX_SOURCE)_primary_system; \
	fi
	@echo "Statusing $(BUSYBOX) done"

#
# Clean
#
.PHONY: busybox_primary_system-clean

busybox_primary_system-clean:
	@rm -f $(BUSYBOX_DIR)/.busybox_primary_system_configured
	@if [ -d "$(BUSYBOX_SOURCE)_primary_system" ]; then\
		make -C $(BUSYBOX_SOURCE)_primary_system clean; \
	fi
	$(BUSYBOX_DIR)/.busybox_primary_system_compiled

#
# Dist clean
#
.PHONY: busybox_primary_system-distclean

busybox_primary_system-distclean:
	@rm -f $(BUSYBOX_DIR)/.busybox_primary_system_*
#@rm -fr $(BUSYBOX_SOURCE)_primary_system

#
# Install
#
.PHONY: busybox_primary_system-install

busybox_primary_system-install:
	-make -C $(BUSYBOX_SOURCE)_primary_system  CC=$(CC) CROSS_COMPILE="$(CROSS)" PREFIX="$(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)" \
	                       EXTRA_CFLAGS="$(TARGET_CFLAGS)"	CONFIG_PREFIX=$(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) install

