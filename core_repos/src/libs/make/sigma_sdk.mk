##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# sigma_sdk makefile fragments 
##############################################################################

#
# Defines
#
include $(TOP)/scripts/target-smp8654.mk
SIGMA_SDK_SERVER_URL  := $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_CONFIG      := 
RUA_DIR := $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)/MRUA_src
SIGMA_RUA_SDK	=	$(CONF_SIGMA_RUA_SDK)
SIGMA_RUA_FW	=	$(CONF_SIGMA_RUA_FW)
export SIGMA_RUA_SDK
export SIGMA_SDK_SOURCE
export SIGMA_RUA_FW

#
# Download  the source 
#
.PHONY: sigma_sdk-downloaded

sigma_sdk-downloaded: $(SIGMA_SDK_DIR)/.sigma_sdk_downloaded

$(SIGMA_SDK_DIR)/.sigma_sdk_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: sigma_sdk-unpacked

sigma_sdk-unpacked: $(SIGMA_SDK_DIR)/.sigma_sdk_unpacked

$(SIGMA_SDK_DIR)/.sigma_sdk_unpacked:
	@echo "Unpacking $(SIGMA_SDK_SOURCE) ..."
	# Remove the source file firstly
	rm -fr $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)
	cd $(SIGMA_SDK_SOURCE); tar zxvf $(CONF_SIGMA_RUA_SDK).tgz;
	rm -fr $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_FW)
	if [ ! -d "$(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_FW).tgz" ]; then \
		cd $(SIGMA_SDK_SOURCE);\
		tar zxvf $(CONF_SIGMA_RUA_FW).tgz; \
	fi
ifeq ($(CONF_HAVE_VIDEO_CODEC_RMVB), y)
	rm -fr $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_REALPLUGIN)
	cd $(SIGMA_SDK_SOURCE); tar zxvf $(CONF_SIGMA_REALPLUGIN).tgz;
	cd $(SIGMA_SDK_SOURCE); cp -f $(CONF_SIGMA_REALPLUGIN)/librmlibrealmedia.so $(CONF_SIGMA_RUA_SDK)/lib/
endif
#ifeq  (x$(CONF_USE_LEGACY_MRUA_DRIVER), xn)
#	rm -fr $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_FW);
#	cd $(SIGMA_SDK_SOURCE); tar zxvf $(CONF_SIGMA_RUA_FW).tgz; 
#	cd $(SIGMA_SDK_SOURCE); tar zxvf mruafw_SMP8634_2.8.3.0_facsprod.mips.nodts.tgz;
#endif
	# Remove the Werror from inc.Makefile
	cp $(RUA_DIR)/scripts/inc.Makefile $(RUA_DIR)/scripts/inc.Makefile.old -rf
	sed 's/-Werror/-Wall/' $(RUA_DIR)/scripts/inc.Makefile.old > $(RUA_DIR)/scripts/inc.Makefile
	cp $(RUA_DIR)/scripts/inc.Makefile $(RUA_DIR)/scripts/inc.Makefile.old -rf
	@echo "Unpacking $(SIGMA_SDK_SOURCE) done"
	@touch $@


#
# Patch the source
#
.PHONY: sigma_sdk-patched

sigma_sdk-patched: $(SIGMA_SDK_DIR)/.sigma_sdk_patched

$(SIGMA_SDK_DIR)/.sigma_sdk_patched: $(SIGMA_SDK_DIR)/.sigma_sdk_unpacked
	make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk sigma_sdk-patched
	touch $@

#
# config
#
.PHONY: sigma_sdk-config

sigma_sdk-config: 

#
# Configuration
#
.PHONY: sigma_sdk-configured

sigma_sdk-configured:  sigma_sdk-config $(SIGMA_SDK_DIR)/.sigma_sdk_configured

$(SIGMA_SDK_DIR)/.sigma_sdk_configured: $(SIGMA_SDK_DIR)/.sigma_sdk_patched $(SIGMA_SDK_CONFIG) $(TOP_CURRENT_SET)
	# Configuring ...
	@touch $@

#
# Compile
#
.PHONY: sigma_sdk-compile

sigma_sdk-compile: sigma_sdk-configured
	# Compiling...

#
# Update
#
.PHONY: sigma_sdk-update

sigma_sdk-update:
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) done"

#
# Status
#
.PHONY: sigma_sdk-status

sigma_sdk-status:
	@echo "Statusing $(SIGMA_SDK) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_STATUS) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Statusing $(SIGMA_SDK) done"

#
# Clean
#
.PHONY: sigma_sdk-clean

sigma_sdk-clean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_sdk_downloaded

#
# Dist clean
#
.PHONY: sigma_sdk-distclean

sigma_sdk-distclean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_sdk_*

#
# Install
#
.PHONY: sigma_sdk-install

sigma_sdk-install:
	echo "install $(CONF_SIGMA_RUA_FW) ..."
	make -f $(SIGMA_SDK_SOURCE)/install.mk sigma_sdk

