

CONF_PARAGON_NTFS_TOOLS_VERSION=20100908#

PARAGON_NTFS_TOOLS_SERVER_URL	:= $(TOP_LIBS_URL)/paragon_ntfs_tools/$(CONF_PARAGON_NTFS_TOOLS_VERSION)
PARAGON_NTFS_TOOLS_SOURCE	:= $(TOP_LIBS_DIR)/paragon_ntfs_tools


#
# Download  the source 
#
.PHONY: paragon_ntfs_tools-downloaded

paragon_ntfs_tools-downloaded: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_downloaded

$(TOP_LIBS_DIR)/.paragon_ntfs_tools_downloaded:
	@echo "Downloading Paragon NTFS tools from $(PARAGON_NTFS_TOOLS_SERVER_URL) ..."
	@if [ ! -d "$(PARAGON_NTFS_TOOLS_SOURCE)" ]; then \
		cd $(TOP_LIBS_DIR); \
		$(TOP_DOWNLOAD) $(PARAGON_NTFS_TOOLS_SERVER_URL) paragon_ntfs_tools; \
	fi
	@echo "Downloading Paragon NTFS tools done"
	@touch $@


#
# Unpack the source
#
.PHONY: paragon_ntfs_tools-unpacked

paragon_ntfs_tools-unpacked: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_unpacked

$(TOP_LIBS_DIR)/.paragon_ntfs_tools_unpacked: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_downloaded


#
# Patch the source
#
.PHONY: paragon_ntfs_tools-patched

paragon_ntfs_tools-patched: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_patched

$(TOP_LIBS_DIR)/.paragon_ntfs_tools_patched: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_unpacked

#
# config
#
.PHONY: paragon_ntfs_tools-config

paragon_ntfs_tools-config: 

#
# Configuration
#
.PHONY: paragon_ntfs_tools-configured

paragon_ntfs_tools-configured:  paragon_ntfs_tools-config $(TOP_LIBS_DIR)/.paragon_ntfs_tools_configured

$(TOP_LIBS_DIR)/.paragon_ntfs_tools_configured: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_patched

#
# Compile
#
.PHONY: paragon_ntfs_tools-compile

paragon_ntfs_tools-compile: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_compiled

$(TOP_LIBS_DIR)/.paragon_ntfs_tools_compiled: $(TOP_LIBS_DIR)/.paragon_ntfs_tools_configured

#
# Update
#
.PHONY: paragon_ntfs_tools-update

paragon_ntfs_tools-update:

#
# Status
#
.PHONY: paragon_ntfs_tools-status

paragon_ntfs_tools-status:

#
# Clean
#
.PHONY: paragon_ntfs_tools-clean

paragon_ntfs_tools-clean:

#
# Dist clean
#
.PHONY: paragon_ntfs_tools-distclean

paragon_ntfs_tools-distclean:

#
# Install
#
.PHONY: paragon_ntfs_tools-install

paragon_ntfs_tools-install:
	cp -f $(PARAGON_NTFS_TOOLS_SOURCE)/* $(TOP_INSTALL_ROOTFS_DIR)/bin




