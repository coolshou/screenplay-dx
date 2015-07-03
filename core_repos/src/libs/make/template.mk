
#
# Download  the source 
#
.PHONY: xxx-downloaded

xxx-downloaded: $(TOP_LIBS_DIR)/.xxx_downloaded

$(TOP_LIBS_DIR)/.xxx_downloaded:

#
# Unpack the source
#
.PHONY: xxx-unpacked

xxx-unpacked: $(TOP_LIBS_DIR)/.xxx_unpacked

$(TOP_LIBS_DIR)/.xxx_unpacked: $(TOP_LIBS_DIR)/.xxx_downloaded


#
# Patch the source
#
.PHONY: xxx-patched

xxx-patched: $(TOP_LIBS_DIR)/.xxx_patched

$(TOP_LIBS_DIR)/.xxx_patched: $(TOP_LIBS_DIR)/.xxx_unpacked

#
# config
#
.PHONY: xxx-config

xxx-config: 

#
# Configuration
#
.PHONY: xxx-configured

xxx-configured:  xxx-config $(TOP_LIBS_DIR)/.xxx_configured

$(TOP_LIBS_DIR)/.xxx_configured: $(TOP_LIBS_DIR)/.xxx_patched

#
# Compile
#
.PHONY: xxx-compile

xxx-compile: $(TOP_LIBS_DIR)/.xxx_compiled

$(TOP_LIBS_DIR)/.xxx_compiled: $(TOP_LIBS_DIR)/.xxx_configured

#
# Update
#
.PHONY: xxx-update

xxx-update:

#
# Status
#
.PHONY: xxx-status

xxx-status:

#
# Clean
#
.PHONY: xxx-clean

xxx-clean:

#
# Dist clean
#
.PHONY: xxx-distclean

xxx-distclean:

#
# Install
#
.PHONY: xxx-install

xxx-install:
