#
# Defines
#
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#

#
# Download  the source 
#
.PHONY: sigma_driver-downloaded

sigma_driver-downloaded: 

#
# Unpack the source
#
.PHONY: sigma_driver-unpacked

sigma_driver-unpacked:


#
# Patch the source
#
.PHONY: sigma_driver-patched

sigma_driver-patched:$(SIGMA_SDK_DIR)/.sigma_driver-patched

$(SIGMA_SDK_DIR)/.sigma_driver-patched:
	touch $@


#
# config
#
.PHONY: sigma_driver-config

sigma_driver-config:

#
# Configuration
#
.PHONY: sigma_driver-configured

sigma_driver-configured:


#
# Compile
#
.PHONY: sigma_driver-compile

sigma_driver-compile: $(SIGMA_SDK_DIR)/.sigma_driver-compile 

$(SIGMA_SDK_DIR)/.sigma_driver-compile: $(SIGMA_SDK_DIR)/.sigma_driver-patched
	-echo "Compile Sigma MRUA.."
	make -f $(SIGMA_SDK_SOURCE)/compile.mk sigma_driver
	touch $@

#
# Update
#
.PHONY: sigma_driver-update

sigma_driver-update:

#
# Status
#
.PHONY: sigma_driver-status

sigma_driver-status:

#
# Clean
#
.PHONY: sigma_driver-clean

sigma_driver-clean:
	@make -C $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK); make cleanrelease
	rm -f $(SIGMA_SDK_DIR)/.sigma_driver-compile
	

#
# Dist clean
#
.PHONY: sigma_driver-distclean

sigma_driver-distclean:
	rm -f $(SIGMA_SDK_DIR)/.sigma_driver*

#
# Install
#
.PHONY: sigma_driver-install

sigma_driver-install:
	make -f $(SIGMA_SDK_SOURCE)/install.mk sigma_driver
