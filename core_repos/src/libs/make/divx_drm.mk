##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  frank_chung@alphanetworks.com
# divx_drm makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_DIVX_DRM_VERSION 
CONF_DIVX_DRM_VERSION := 6.1
endif

DIVX_DRM             := divx_drm-$(CONF_DIVX_DRM_VERSION)#
DIVX_DRM_SERVER_URL  := $(TOP_LIBS_URL)/divx_drm/$(DIVX_DRM)
DIVX_DRM_DIR         := $(TOP_LIBS_DIR)#
DIVX_DRM_SOURCE      := $(DIVX_DRM_DIR)/$(DIVX_DRM)
DIVX_DRM_CONFIG      := 


#
# Download  the source 
#
.PHONY: divx_drm-downloaded

divx_drm-downloaded: $(DIVX_DRM_DIR)/.divx_drm_downloaded

$(DIVX_DRM_DIR)/.divx_drm_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: divx_drm-unpacked

divx_drm-unpacked: $(DIVX_DRM_DIR)/.divx_drm_unpacked

$(DIVX_DRM_DIR)/.divx_drm_unpacked: $(DIVX_DRM_DIR)/.divx_drm_downloaded $(wildcard $(DIVX_DRM_SOURCE)/*.tgz)
	@touch $@


#
# Patch the source
#
.PHONY: divx_drm-patched

divx_drm-patched: $(DIVX_DRM_DIR)/.divx_drm_patched

$(DIVX_DRM_DIR)/.divx_drm_patched: $(DIVX_DRM_DIR)/.divx_drm_unpacked
	@touch $@

#
# config
#
.PHONY: divx_drm-config

divx_drm-config: 

#
# Configuration
#
.PHONY: divx_drm-configured

divx_drm-configured:  divx_drm-config $(DIVX_DRM_DIR)/.divx_drm_configured

$(DIVX_DRM_DIR)/.divx_drm_configured: $(DIVX_DRM_DIR)/.divx_drm_patched $(DIVX_DRM_CONFIG) $(TOP_CURRENT_SET)
	@touch $@

#
# Compile
#
.PHONY: divx_drm-compile

divx_drm-compile: $(DIVX_DRM_DIR)/.divx_drm_compiled

$(DIVX_DRM_DIR)/.divx_drm_compiled: $(DIVX_DRM_DIR)/.divx_drm_configured
	@touch $@

#
# Update
#
.PHONY: divx_drm-update

divx_drm-update:
	@echo "Updating $(DIVX_DRM) ..."
	@if [ -d "$(DIVX_DRM_SOURCE)" ]; then\
		$(TOP_UPDATE) $(DIVX_DRM_SOURCE); \
	fi
	@echo "Updating $(DIVX_DRM) done"

#
# Status
#
.PHONY: divx_drm-status

divx_drm-status:
	@echo "Statusing $(DIVX_DRM) ..."
	@if [ -d "$(DIVX_DRM_SOURCE)" ]; then\
		$(TOP_STATUS) $(DIVX_DRM_SOURCE); \
	fi
	@echo "Statusing $(DIVX_DRM) done"

#
# Clean
#
.PHONY: divx_drm-clean

divx_drm-clean:
	@rm -f $(DIVX_DRM_DIR)/.divx_drm_configured

#
# Dist clean
#
.PHONY: divx_drm-distclean

divx_drm-distclean:
	@rm -f $(DIVX_DRM_DIR)/.divx_drm_*

#
# Install
#
.PHONY: divx_drm-install

divx_drm-install:
