


PARAGON_NTFS_SERVER_URL	:= $(TOP_LIBS_URL)/paragon-ntfs/$(CONF_PARAGON_NTFS_VERSION)
PARAGON_NTFS_SOURCE	:= $(TOP_LIBS_DIR)/paragon-ntfs


#
# Download  the source 
#
.PHONY: paragon_ntfs-downloaded

paragon_ntfs-downloaded: $(TOP_LIBS_DIR)/.paragon_ntfs_downloaded

$(TOP_LIBS_DIR)/.paragon_ntfs_downloaded:
	@echo "Downloading Paragon-NTFS from $(PARAGON_NTFS_SERVER_URL) ..."
	@if [ ! -d "$(PARAGON_NTFS_SOURCE)" ]; then \
		cd $(TOP_LIBS_DIR); \
		$(TOP_DOWNLOAD) $(PARAGON_NTFS_SERVER_URL) paragon-ntfs; \
	fi
	@echo "Downloading Paragon-NTFS done"
	@touch $@


#
# Unpack the source
#
.PHONY: paragon_ntfs-unpacked

paragon_ntfs-unpacked: $(TOP_LIBS_DIR)/.paragon_ntfs_unpacked

$(TOP_LIBS_DIR)/.paragon_ntfs_unpacked: $(TOP_LIBS_DIR)/.paragon_ntfs_downloaded


#
# Patch the source
#
.PHONY: paragon_ntfs-patched

paragon_ntfs-patched: $(TOP_LIBS_DIR)/.paragon_ntfs_patched

$(TOP_LIBS_DIR)/.paragon_ntfs_patched: $(TOP_LIBS_DIR)/.paragon_ntfs_unpacked

#
# config
#
.PHONY: paragon_ntfs-config

paragon_ntfs-config: 

#
# Configuration
#
.PHONY: paragon_ntfs-configured

paragon_ntfs-configured:  paragon_ntfs-config $(TOP_LIBS_DIR)/.paragon_ntfs_configured

$(TOP_LIBS_DIR)/.paragon_ntfs_configured: $(TOP_LIBS_DIR)/.paragon_ntfs_patched

#
# Compile
#
.PHONY: paragon_ntfs-compile

paragon_ntfs-compile: $(TOP_LIBS_DIR)/.paragon_ntfs_compiled

$(TOP_LIBS_DIR)/.paragon_ntfs_compiled: $(TOP_LIBS_DIR)/.paragon_ntfs_configured

#
# Update
#
.PHONY: paragon_ntfs-update

paragon_ntfs-update:

#
# Status
#
.PHONY: paragon_ntfs-status

paragon_ntfs-status:

#
# Clean
#
.PHONY: paragon_ntfs-clean

paragon_ntfs-clean:

#
# Dist clean
#
.PHONY: paragon_ntfs-distclean

paragon_ntfs-distclean:

#
# Install
#
.PHONY: paragon_ntfs-install

paragon_ntfs-install:
	cp -f $(PARAGON_NTFS_SOURCE)/ufsd.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules 
	mkdir -p $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/etc
	cp -f $(PARAGON_NTFS_SOURCE)/ufsd.ko $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/etc




