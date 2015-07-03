##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# sigma_isdk makefile fragments 
##############################################################################

#
# Defines
#

SIGMA_SDK_SERVER_URL  := $(TOP_LIBS_URL)/sigma_isdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_ISDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_ISDK_VERSION)#
SIGMA_SDK_CONFIG      := 
SIGMA_RUA_SDK	=	$(CONF_SIGMA_RUA_SDK)
SIGMA_RUA_FW	=	$(CONF_SIGMA_RUA_FW)
export SIGMA_RUA_SDK
export SIGMA_SDK_SOURCE
export SIGMA_RUA_FW

#
# Download  the source 
#
.PHONY: sigma_isdk-downloaded

sigma_isdk-downloaded: $(SIGMA_SDK_DIR)/.sigma_isdk_downloaded

$(SIGMA_SDK_DIR)/.sigma_isdk_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: sigma_isdk-unpacked

sigma_isdk-unpacked: $(SIGMA_SDK_DIR)/.sigma_isdk_unpacked

$(SIGMA_SDK_DIR)/.sigma_isdk_unpacked:
	@echo "Unpacking $(SIGMA_ISDK_SOURCE) ..."
	# Remove the source file firstly
	rm -fr $(SIGMA_ISDK_SOURCE)
	cd $(SIGMA_SDK_SOURCE); tar zxvf $(SIGMA_ISDK_SOURCE).tar.gz;
	@touch $@


#
# Patch the source
#
.PHONY: sigma_isdk-patched

sigma_isdk-patched: $(SIGMA_SDK_DIR)/.sigma_isdk_patched

$(SIGMA_SDK_DIR)/.sigma_isdk_patched: $(SIGMA_SDK_DIR)/.sigma_isdk_unpacked
	make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk sigma_isdk-patched
	touch $@


#
# Compile
#
.PHONY: sigma_isdk-compile

sigma_isdk-compile: $(SIGMA_SDK_DIR)/.sigma_isdk_compile

$(SIGMA_SDK_DIR)/.sigma_isdk_compile: $(SIGMA_SDK_DIR)/.sigma_isdk_patched
	-echo "Compile Sigma ISDK.."
	make -f $(SIGMA_SDK_SOURCE)/compile.mk sigma_isdk
	touch $@

#
# Update
#
.PHONY: sigma_isdk-update

sigma_isdk-update:
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Updating $(CONF_SIGMA_SDK_VERSION) done"

#
# Status
#
.PHONY: sigma_isdk-status

sigma_isdk-status:
	@echo "Statusing $(SIGMA_SDK) ..."
	@if [ -d "$(SIGMA_SDK_SOURCE)" ]; then\
		$(TOP_STATUS) $(SIGMA_SDK_SOURCE); \
	fi
	@echo "Statusing $(SIGMA_SDK) done"

#
# Clean
#
.PHONY: sigma_isdk-clean

sigma_isdk-clean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_isdk_downloaded

#
# Dist clean
#
.PHONY: sigma_isdk-distclean

sigma_isdk-distclean:
	@rm -f $(SIGMA_SDK_DIR)/.sigma_isdk_*

#
# Install
#
.PHONY: sigma_isdk-install

sigma_isdk-install:
	echo "install $(CONF_SIGMA_RUA_FW) ..."
	make -f $(SIGMA_SDK_SOURCE)/install.mk sigma_isdk

