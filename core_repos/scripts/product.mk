##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  nicle_yang@alphanetworks.com
# product makefile fragments 
##############################################################################

########################## global variables section ##########################

TOP         := $(shell pwd)

# server repos
PRODUCT_SERVER_URL   = $(TOP_PRODUCT_URL)/$(CURRENT_SET)  
COMMON_SERVER_URL    = $(TOP_PRODUCT_URL)/common

# client
PRODUCT_DIR          = $(TOP_PRODUCT_DIR)
COMMON_DIR           = $(TOP_PRODUCT_DIR)/common

########################## includes section ##################################

include $(TOP)/CURRENT_SET
include $(TOP)/scripts/defines.mk

########################## target section ####################################

.PHONY: download update status

download: product-downloaded common-downloaded

update: product-updated common-updated

status: product-status common-status 

#
# Download product
#
.PHONY: product-downloaded

product-downloaded:
	@echo "Downloading product from $(PRODUCT_SERVER_URL) ..."
	@if [ ! -d "$(PRODUCT_DIR)" ]; then \
		$(TOP_DOWNLOAD) $(PRODUCT_SERVER_URL) $(PRODUCT_DIR); \
	fi
	@echo "Downloading product done"

#
# Update product
#
.PHONY: product-updated

product-updated: 
	@echo "Updating product from $(PRODUCT_DIR) ..."
	cd $(PRODUCT_DIR); $(TOP_UPDATE);
	@echo "Updating product done"

.PHONY: product-status

#
# Status for product
#
product-status:
	@$(TOP_STATUS) $(PRODUCT_DIR);

#
# Download common
#
.PHONY: common-downloaded

common-downloaded: product-downloaded 
	@echo "Downloading common from $(COMMON_SERVER_URL) ..."
	@if [ ! -d "$(COMMON_DIR)" ]; then \
		$(TOP_DOWNLOAD) $(COMMON_SERVER_URL) $(COMMON_DIR); \
	fi
	@echo "Downloading common done"

#
# Update common
#
.PHONY: common-updated
common-updated:
	@echo "Updating common from $(COMMON_DIR) ..."
	cd $(COMMON_DIR); $(TOP_UPDATE);
	@echo "Updating $(COMMON_DIR) done"

#
# Status for common
#
.PHONY: common-status
common-status:
	@$(TOP_STATUS) $(COMMON_DIR);
