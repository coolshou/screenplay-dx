#
# Defines
#
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
BOOT_LOADER_DIR	      := $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_BOOT_LOADER)/#

#
# Download  the source 
#
.PHONY: sigma_zboot-downloaded

sigma_zboot-downloaded: $(SIGMA_SDK_DIR)/.sigma_zboot-downloaded

$(SIGMA_SDK_DIR)/.sigma_zboot-downloaded:
	touch $@ 

#
# Unpack the source
#
.PHONY: sigma_zboot-unpacked

sigma_zboot-unpacked:	$(SIGMA_SDK_DIR)/.sigma_zboot-unpacked

$(SIGMA_SDK_DIR)/.sigma_zboot-unpacked: $(SIGMA_SDK_DIR)/.sigma_zboot-downloaded
	@echo "Unpacking boot loader..."
	make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk sigma_zboot-unpack
	@touch $@
		 


#
# Patch the source
#
.PHONY: sigma_zboot-patched

sigma_zboot-patched: $(SIGMA_SDK_DIR)/.sigma_zboot-patched

$(SIGMA_SDK_DIR)/.sigma_zboot-patched: $(SIGMA_SDK_DIR)/.sigma_zboot-unpacked
	make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk sigma_zboot-patch
	@touch $@


#
# config
#
.PHONY: sigma_zboot-config

sigma_zboot-config:

#
# Configuration
#
.PHONY: sigma_zboot-configured

sigma_zboot-configured:


#
# Compile
#
.PHONY: sigma_zboot-compile

sigma_zboot-compile: $(SIGMA_SDK_DIR)/.sigma_zboot-compile

$(SIGMA_SDK_DIR)/.sigma_zboot-compile: $(SIGMA_SDK_DIR)/.sigma_zboot-patched
	-echo "Compile Sigma bootloader.."
	make -f $(SIGMA_SDK_SOURCE)/compile.mk sigma_zboot
	touch $@

#
# Update
#
.PHONY: sigma_zboot-update

sigma_zboot-update:

#
# Status
#
.PHONY: sigma_zboot-status

sigma_zboot-status:

#
# Clean
#
.PHONY: sigma_zboot-clean

sigma_zboot-clean:
	rm -f $(SIGMA_SDK_DIR)/.sigma_zboot-patched
	(cd $(BOOT_LOADER_DIR); make clean )
	

#
# Dist clean
#
.PHONY: sigma_zboot-distclean

sigma_zboot-distclean:
	rm -f $(SIGMA_SDK_DIR)/.sigma_zboot*

#
# Install
#
.PHONY: sigma_zboot-install

sigma_zboot-install:
	make -f $(SIGMA_SDK_SOURCE)/install.mk sigma_zboot

