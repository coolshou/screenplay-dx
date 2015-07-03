##############################################################################
# Copyright (C) alphanetworks 2011-- 
# All Rights Reserved -- Company Confidential
# Author:  pam_tu@alphanetworks.com
# vudu makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_VUDU_VERSION 
CONF_VUDU_VERSION := VUDU_79839_ALPHA
endif

SIGMA_SDK_SERVER_URL	:= $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_SOURCE		:= $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)#

VUDU_DIR				 := $(SIGMA_SDK_SOURCE)/vudu#
VUDU             := $(CONF_VUDU_VERSION)#
VUDU_SOURCE      := $(VUDU_DIR)/$(VUDU)#
#VUDU_LIB_DIR     := $(VUDU_SOURCE)/targets/linux/SigmaDesigns/release#




# Download  the source 
#
.PHONY: vudu-downloaded

vudu-downloaded: 

#
# Unpack the source
#
.PHONY: vudu-unpacked

vudu-unpacked: $(TOP_LIBS_DIR)/.vudu_unpacked

$(TOP_LIBS_DIR)/.vudu_unpacked: $(VUDU_SOURCE).tgz 
	@echo "Unpacking $(VUDU) ..."
	if [ -d "$(VUDU_SOURCE)" ]; then \
		rm -fr $(VUDU_SOURCE); \
	fi
	(cd $(VUDU_DIR); tar zxvf $(VUDU_SOURCE).tgz)
ifeq (x$(CONF_VUDU_VERSION), xVUDU_79839_ALPHA)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavcodec.so; ln -s libavcodec.so.52.20.0 libavcodec.so)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavcodec.so.52; ln -s libavcodec.so.52.20.0 libavcodec.so.52)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavformat.so; ln -s libavformat.so.52.31.0 libavformat.so)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavformat.so.52; ln -s libavformat.so.52.31.0 libavformat.so.52)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavutil.so; ln -s libavutil.so.49.15.0 libavutil.so)
	@(cd $(VUDU_SOURCE)/lib; rm -f libavutil.so.49; ln -s libavutil.so.49.15.0 libavutil.so.49)
	@(cd $(VUDU_SOURCE)/lib; rm -f libcurl.so; ln -s libcurl.so.4.2.0 libcurl.so)
	@(cd $(VUDU_SOURCE)/lib; rm -f libcurl.so.4; ln -s libcurl.so.4.2.0 libcurl.so.4)
	@(cd $(VUDU_SOURCE)/lib; rm -f libxml2.so; ln -s libxml2.so.2.6.32 libxml2.so)
	@(cd $(VUDU_SOURCE)/lib; rm -f libxml2.so.2; ln -s libxml2.so.2.6.32 libxml2.so.2)
endif
	@(cd $(VUDU_SOURCE)/src/sigmaSmp86xx/vuduxtask; cp libvuduxtask.a $(SYSLIB_PREFIX)/lib)
	@(cd $(VUDU_SOURCE)/lib; cp libavcodec.so* libavformat.so* libavutil.so* libvudu.so $(SYSLIB_PREFIX)/lib)
	@echo "Unpacking $(VUDU) done"
	@touch $@



#
# Patch the source
#
.PHONY: vudu-patched

vudu-patched: $(TOP_LIBS_DIR)/.vudu_patched

$(TOP_LIBS_DIR)/.vudu_patched: $(TOP_LIBS_DIR)/.vudu_unpacked
	# Patching...
ifeq (x$(CONF_PRODUCT_EXT_IOM), xy)
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/iomega_remote_key_map.patch)
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/iomega_fix_compile_error.patch)
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/vudu_alpha_wireless.patch)
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/Vudu-UploadStatusChanges.patch)
ifeq (x$(CONF_VUDU_VERSION), xVUDU_80955__3)
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/iomega_uid_3.patch)
else
	(cd $(VUDU_SOURCE); patch -p0 < ../patch/iomega_uid.patch)
endif
endif
	@touch $@

#
# config
#
.PHONY: vudu-config

vudu-config: 

#
# Configuration
#
.PHONY: vudu-configured

vudu-configured:  vudu-config $(TOP_LIBS_DIR)/.vudu_configured

$(TOP_LIBS_DIR)/.vudu_configured: $(TOP_LIBS_DIR)/.vudu_patched $(VUDU_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(VUDU) ..."
	@touch $@

#
# Compile
#
.PHONY: vudu-compile

vudu-compile: $(TOP_LIBS_DIR)/.vudu_compiled

$(TOP_LIBS_DIR)/.vudu_compiled: $(TOP_LIBS_DIR)/.vudu_configured
	@echo "Compiling $(VUDU) ..."
	@echo "Compiling $(VUDU) done"
	@touch $@

#
# Update
#
.PHONY: vudu-update

vudu-update:
	@echo "Updating $(VUDU) ..."
	@if [ -d "$(VUDU_SOURCE)" ]; then\
		$(TOP_UPDATE) $(VUDU_SOURCE); \
	fi
	@echo "Updating $(VUDU) done"

#
# Status
#
.PHONY: vudu-status

vudu-status:
	@echo "Statusing $(VUDU) ..."
	@if [ -d "$(VUDU_SOURCE)" ]; then\
		$(TOP_STATUS) $(VUDU_SOURCE); \
	fi
	@echo "Statusing $(VUDU) done"

#
# Clean
#
.PHONY: vudu-clean

vudu-clean:
	@rm -f $(TOP_LIBS_DIR)/.vudu_configured

#
# Dist clean
#
.PHONY: vudu-distclean

vudu-distclean:
	@rm -f $(TOP_LIBS_DIR)/.vudu*

#
# Install
#
.PHONY: vudu-install

vudu-install:
ifeq (x$(CONF_VUDU_VERSION), xVUDU_79839_ALPHA)
	@(cd $(VUDU_SOURCE)/lib; cp libavcodec.so.52.20.0 libavformat.so.52.31.0 libavutil.so.49.15.0 libvudu.so $(TOP_BUILD_ROOTFS_DIR)/lib)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavcodec.so; ln -s libavcodec.so.52.20.0 libavcodec.so)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavcodec.so.52; ln -s libavcodec.so.52.20.0 libavcodec.so.52)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavformat.so; ln -s libavformat.so.52.31.0 libavformat.so)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavformat.so.52; ln -s libavformat.so.52.31.0 libavformat.so.52)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavutil.so; ln -s libavutil.so.49.15.0 libavutil.so)
	@(cd $(TOP_BUILD_ROOTFS_DIR)/lib; rm -f libavutil.so.49; ln -s libavutil.so.49.15.0 libavutil.so.49)
endif
