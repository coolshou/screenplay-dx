
UCLIBC_SERVER_URL	:= $(TOP_LIBS_URL)/uClibc_binary/$(CONF_UCLIBC_VERSION)
UCLIBC_BIN_DIR		:= $(TOP_LIBS_DIR)/$(CONF_UCLIBC_VERSION)
UCLIBC_TARGET_DIR	:= $(TOP_INSTALL_ROOTFS_DIR)/lib


#
# Download  the source 
#
.PHONY: uclibc-downloaded

uclibc-downloaded: $(TOP_LIBS_DIR)/.uclibc_downloaded

$(TOP_LIBS_DIR)/.uclibc_downloaded:
	@echo "Downloading uClibc package..."
	$(TOP_DOWNLOAD) $(UCLIBC_SERVER_URL)
	@touch $@


#
# Unpack the source
#
.PHONY: uclibc-unpacked

uclibc-unpacked: $(TOP_LIBS_DIR)/.uclibc_unpacked

$(TOP_LIBS_DIR)/.uclibc_unpacked: $(TOP_LIBS_DIR)/.uclibc_downloaded


#
# Patch the source
#
.PHONY: uclibc-patched

uclibc-patched: $(TOP_LIBS_DIR)/.uclibc_patched

$(TOP_LIBS_DIR)/.uclibc_patched: $(TOP_LIBS_DIR)/.uclibc_unpacked

#
# config
#
.PHONY: uclibc-config

uclibc-config: 

#
# Configuration
#
.PHONY: uclibc-configured

uclibc-configured:  uclibc-config $(TOP_LIBS_DIR)/.uclibc_configured

$(TOP_LIBS_DIR)/.uclibc_configured: $(TOP_LIBS_DIR)/.uclibc_patched

#
# Compile
#
.PHONY: uclibc-compile

uclibc-compile: $(TOP_LIBS_DIR)/.uclibc_compiled

$(TOP_LIBS_DIR)/.uclibc_compiled: $(TOP_LIBS_DIR)/.uclibc_configured

#
# Update
#
.PHONY: uclibc-update

uclibc-update:

#
# Status
#
.PHONY: uclibc-status

uclibc-status:

#
# Clean
#
.PHONY: uclibc-clean

uclibc-clean:

#
# Dist clean
#
.PHONY: uclibc-distclean

uclibc-distclean:

#
# Install
#
.PHONY: uclibc-install

uclibc-install:
	echo "Installing uClibc..."
	mkdir -p $(UCLIBC_TARGET_DIR);
	(cd $(UCLIBC_BIN_DIR); tar cf - * ) | (cd $(UCLIBC_TARGET_DIR) && tar xf -);

