
TOOLCHAIN_SVERVER_URL   := $(TOP_LIBS_URL)/toolchains/$(CONF_TOOLCHAIN_FILENAME)

#
# Download  the source 
#
.PHONY: toolchain-downloaded

toolchain-downloaded: $(TOP_LIBS_DIR)/.toolchain_downloaded

$(TOP_LIBS_DIR)/.toolchain_downloaded:
	@if [ ! -f $(CROSS)gcc ]; then \
		sudo $(TOP_DOWNLOAD_CAT) $(TOOLCHAIN_SVERVER_URL) | sudo $(TOP_UNPACK_TGZ)  -C $(CONF_TOOLCHAIN_INSTALL_DIR); \
	fi
	@echo "Installing  $(CONF_TOOLCHAIN_FILENAME) done"
	touch $@

#
# Unpack the source
#
.PHONY: toolchain-unpacked

toolchain-unpacked: $(TOP_LIBS_DIR)/.toolchain_unpacked

$(TOP_LIBS_DIR)/.toolchain_unpacked: $(TOP_LIBS_DIR)/.toolchain_downloaded


#
# Patch the source
#
.PHONY: toolchain-patched

toolchain-patched: $(TOP_LIBS_DIR)/.toolchain_patched

$(TOP_LIBS_DIR)/.toolchain_patched: $(TOP_LIBS_DIR)/.toolchain_unpacked

#
# config
#
.PHONY: toolchain-config

toolchain-config: 

#
# Configuration
#
.PHONY: toolchain-configured

toolchain-configured:  toolchain-config $(TOP_LIBS_DIR)/.toolchain_configured

$(TOP_LIBS_DIR)/.toolchain_configured: $(TOP_LIBS_DIR)/.toolchain_patched

#
# Compile
#
.PHONY: toolchain-compile

toolchain-compile: $(TOP_LIBS_DIR)/.toolchain_compiled

$(TOP_LIBS_DIR)/.toolchain_compiled: $(TOP_LIBS_DIR)/.toolchain_configured

#
# Update
#
.PHONY: toolchain-update

toolchain-update:

#
# Status
#
.PHONY: toolchain-status

toolchain-status:

#
# Clean
#
.PHONY: toolchain-clean

toolchain-clean:

#
# Dist clean
#
.PHONY: toolchain-distclean

toolchain-distclean:
		rm -vf $(TOP_LIBS_DIR)/.toolchain_downloaded

#
# Install
#
.PHONY: toolchain-install

toolchain-install:
