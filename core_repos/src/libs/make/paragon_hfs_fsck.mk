


PARAGON_HFS_FSCK_SERVER_URL	:= $(TOP_LIBS_URL)/paragon-hfs-fsck/$(CONF_PARAGON_HFS_FSCK_VERSION)
PARAGON_HFS_FSCK_SOURCE	:= $(TOP_LIBS_DIR)/paragon-hfs-fsck


#
# Download  the source 
#
.PHONY: paragon_hfs_fsck-downloaded

paragon_hfs_fsck-downloaded: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_downloaded

$(TOP_LIBS_DIR)/.paragon_hfs_fsck_downloaded:
	@echo "Downloading Paragon-NTFS from $(PARAGON_HFS_FSCK_SERVER_URL) ..."
	@if [ ! -d "$(PARAGON_HFS_FSCK_SOURCE)" ]; then \
		cd $(TOP_LIBS_DIR); \
		$(TOP_DOWNLOAD) $(PARAGON_HFS_FSCK_SERVER_URL) paragon-hfs-fsck; \
	fi
	@echo "Downloading Paragon-NTFS done"
	@touch $@


#
# Unpack the source
#
.PHONY: paragon_hfs_fsck-unpacked

paragon_hfs_fsck-unpacked: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_unpacked

$(TOP_LIBS_DIR)/.paragon_hfs_fsck_unpacked: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_downloaded


#
# Patch the source
#
.PHONY: paragon_hfs_fsck-patched

paragon_hfs_fsck-patched: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_patched

$(TOP_LIBS_DIR)/.paragon_hfs_fsck_patched: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_unpacked

#
# config
#
.PHONY: paragon_hfs_fsck-config

paragon_hfs_fsck-config: 

#
# Configuration
#
.PHONY: paragon_hfs_fsck-configured

paragon_hfs_fsck-configured:  paragon_hfs_fsck-config $(TOP_LIBS_DIR)/.paragon_hfs_fsck_configured

$(TOP_LIBS_DIR)/.paragon_hfs_fsck_configured: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_patched

#
# Compile
#
.PHONY: paragon_hfs_fsck-compile

paragon_hfs_fsck-compile: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_compiled

$(TOP_LIBS_DIR)/.paragon_hfs_fsck_compiled: $(TOP_LIBS_DIR)/.paragon_hfs_fsck_configured

#
# Update
#
.PHONY: paragon_hfs_fsck-update

paragon_hfs_fsck-update:

#
# Status
#
.PHONY: paragon_hfs_fsck-status

paragon_hfs_fsck-status:

#
# Clean
#
.PHONY: paragon_hfs_fsck-clean

paragon_hfs_fsck-clean:

#
# Dist clean
#
.PHONY: paragon_hfs_fsck-distclean

paragon_hfs_fsck-distclean:

#
# Install
#
.PHONY: paragon_hfs_fsck-install

paragon_hfs_fsck-install:
	cp -f $(PARAGON_HFS_FSCK_SOURCE)/chkhfs $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(STRIP) $(TOP_INSTALL_ROOTFS_DIR)/bin/chkhfs




