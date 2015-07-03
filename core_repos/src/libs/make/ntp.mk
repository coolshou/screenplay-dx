##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# ntp makefile fragments 
##############################################################################

#
# Defines
#
ifndef  NTPVERSION 
NTPVERSION := 4.2.6
endif

NTP             := ntp-$(NTPVERSION)#
NTP_SERVER_URL  := $(TOP_LIBS_URL)/ntp/$(NTP)
NTP_DIR         := $(TOP_LIBS_DIR)#
NTP_SOURCE      := $(NTP_DIR)/$(NTP)
NTPCONFIG       := 


#
# Download  the source 
#
.PHONY: ntp-downloaded

ntp-downloaded: $(NTP_DIR)/.ntp_downloaded

$(NTP_DIR)/.ntp_downloaded:
	@echo "Downloading $(NTP) from $(NTP_SERVER_URL) ..."
	@if [ ! -d "$(NTP_SOURCE)" ]; then \
		cd $(NTP_DIR); \
		$(TOP_DOWNLOAD) $(NTP_SERVER_URL); \
	fi
	@echo "Downloading $(NTP) done"
	@touch $@

#
# Unpack the source
#
.PHONY: ntp-unpacked

ntp-unpacked: $(NTP_DIR)/.ntp_unpacked

$(NTP_DIR)/.ntp_unpacked: $(NTP_DIR)/.ntp_downloaded $(NTP_SOURCE)/$(NTP).tar.gz
	@echo "Unpacking the $(NTP) ..."
	if [ -d "$(NTP_SOURCE)/$(NTP)" ]; then \
		rm -fr $(NTP_SOURCE)/$(NTP); \
	fi
	cd $(NTP_SOURCE); tar xzvf $(NTP).tar.gz
	@echo "Unpacking the $(NTP) done"
	@touch $@


#
# Patch the source
#
.PHONY: ntp-patched

ntp-patched: $(NTP_DIR)/.ntp_patched

$(NTP_DIR)/.ntp_patched: $(NTP_DIR)/.ntp_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: ntp-config

ntp-config: 

#
# Configuration
#
.PHONY: ntp-configured

ntp-configured:  ntp-config $(NTP_DIR)/.ntp_configured

$(NTP_DIR)/.ntp_configured: $(NTP_DIR)/.ntp_patched $(NTPCONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(NTP) ..."
	cd $(NTP_SOURCE)/$(NTP);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET)
	@echo "Configuring $(NTP) done"
	@touch $@

#
# Compile
#
.PHONY: ntp-compile

ntp-compile: $(NTP_DIR)/.ntp_compiled

$(NTP_DIR)/.ntp_compiled: $(NTP_DIR)/.ntp_configured
	@echo "Compiling $(NTP) ..."
	make -C $(NTP_SOURCE)/$(NTP)
	@echo "Compiling $(NTP) done"
	@touch $@

#
# Update
#
.PHONY: ntp-update

ntp-update:
	@echo "Updating $(NTP) ..."
	@if [ -d "$(NTP_SOURCE)" ]; then\
		$(TOP_UPDATE) $(NTP_SOURCE); \
	fi
	@echo "Updating $(NTP) done"

#
# Status
#
.PHONY: ntp-status

ntp-status:
	@echo "Statusing $(NTP) ..."
	@if [ -d "$(NTP_SOURCE)" ]; then\
		$(TOP_STATUS) $(NTP_SOURCE); \
	fi
	@echo "Statusing $(NTP) done"

#
# Clean
#
.PHONY: ntp-clean

ntp-clean:
	@rm -f $(NTP_DIR)/.ntp_configured
	@if [ -d "$(NTP_SOURCE)" ]; then\
		make -C $(NTP_SOURCE)/$(NTP) clean; \
	fi

#
# Dist clean
#
.PHONY: ntp-distclean

ntp-distclean:
	@rm -f $(NTP_DIR)/.ntp_*

#
# Install
#
.PHONY: ntp-install

ntp-install:
	cp -f $(NTP_SOURCE)/$(NTP)/ntpdate/ntpdate $(TOP_INSTALL_ROOTFS_DIR)/bin/
