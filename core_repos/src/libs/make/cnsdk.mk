##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# cnsdk makefile fragments 
##############################################################################

#
# Defines
#
ifndef  CONF_CNSDK_VERSION 
CONF_CNSDK_VERSION := 1.1.0.513647__20100409-PStub
endif

CNSDK             := CNSDK_SourceCode_$(CONF_CNSDK_VERSION)#
CNSDK_SERVER_URL  := $(TOP_LIBS_URL)/cnsdk# /$(CNSDK)
CNSDK_DIR         := $(TOP_LIBS_DIR)#
CNSDK_SOURCE      := $(CNSDK_DIR)/cnsdk/$(CNSDK)
CNSDK_CONFIG      := 

#To be compatible with the arm toolchain which renamed the arm-elf-cpp with cpp, 
# add following code to support cross platform
ifneq ($(strip $(wildcard $(CROSS)cpp)),)
	CROSS_CPP 	:=  $(CROSS)cpp
else
	CROSS_CPP 	:=  $(CROSS_PREFIX)/bin/cpp
endif

#
# Download  the source 
#
.PHONY: cnsdk-downloaded

cnsdk-downloaded: $(CNSDK_DIR)/.cnsdk_downloaded

$(CNSDK_DIR)/.cnsdk_downloaded:
	@echo "Downloading $(CNSDK) from $(CNSDK_SERVER_URL) ..."
#ifeq (x$(PLATFORM_X86),xy)
#	cp -avR ../../cnsdk $(CNSDK_DIR)/;
#else
	@if [ ! -d "$(CNSDK_SOURCE)" ]; then \
		cd $(CNSDK_DIR); \
		$(TOP_DOWNLOAD) $(CNSDK_SERVER_URL); \
	fi
#endif
	@echo "Downloading $(CNSDK) done"
	@touch $@

#
# Unpack the source
#
.PHONY: cnsdk-unpacked

cnsdk-unpacked: $(CNSDK_DIR)/.cnsdk_unpacked

$(CNSDK_DIR)/.cnsdk_unpacked: $(CNSDK_DIR)/.cnsdk_downloaded $(wildcard $(CNSDK_SOURCE)/*.tgz)
	@echo "Unpacking $(CNSDK) ..."
	if [ -d "$(CNSDK_SOURCE)/$(CNSDK)" ]; then \
		rm -fr $(CNSDK_SOURCE)/$(CNSDK); \
	fi
	cd $(CNSDK_DIR)/cnsdk;tar zxvf $(CNSDK).tgz
	@echo "Unpacking $(CNSDK) done"
	@touch $@


#
# Patch the source
#
.PHONY: cnsdk-patched

cnsdk-patched: $(CNSDK_DIR)/.cnsdk_patched

$(CNSDK_DIR)/.cnsdk_patched: $(CNSDK_DIR)/.cnsdk_unpacked
	# Patching...
	mv $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Makefile_customer $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Makefile_customer.old
	cp $(CNSDK_SOURCE)/../CNWebServicesLib-Makefile_customer  $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Makefile_customer
ifeq ($(CONF_PLATFORM_X86), y)	
	echo "Move CROSS_COMPILE"
	sed -i -e "s/CROSS_COMPILE =/#CROSS_COMPILE =/" $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Makefile_customer
endif	
	@touch $@

#
# config
#
.PHONY: cnsdk-config

cnsdk-config: 

#
# Configuration
#
.PHONY: cnsdk-configured

cnsdk-configured:  cnsdk-config $(CNSDK_DIR)/.cnsdk_configured

$(CNSDK_DIR)/.cnsdk_configured: $(CNSDK_DIR)/.cnsdk_patched $(CNSDK_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(CNSDK) ..."
	@echo "Configuring $(CNSDK) done"
	@touch $@

#
# Compile
#
.PHONY: cnsdk-compile

cnsdk-compile: $(CNSDK_DIR)/.cnsdk_compiled

$(CNSDK_DIR)/.cnsdk_compiled: $(CNSDK_DIR)/.cnsdk_configured
	@echo "Compiling $(CNSDK) ..."
	make -C $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/  -f Makefile_customer 
#	make -C $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Sample/CNTestApp/ -f Makefile_customer
	cp $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/libcnws.a $(LIBS_INSTALL_PATH)lib/
	mkdir -p $(LIBS_INSTALL_PATH)include/cnsdk
	cp $(CNSDK_SOURCE)/CinemaNow/CNWebServicesLib/Public/* $(LIBS_INSTALL_PATH)include/cnsdk
	@echo "Compiling $(CNSDK) done"
	@touch $@

#
# Update
#
.PHONY: cnsdk-update

cnsdk-update:
	@echo "Updating $(CNSDK) ..."
	@if [ -d "$(CNSDK_SOURCE)" ]; then\
		$(TOP_UPDATE) $(CNSDK_SOURCE); \
	fi
	@echo "Updating $(CNSDK) done"

#
# Status
#
.PHONY: cnsdk-status

cnsdk-status:
	@echo "Statusing $(CNSDK) ..."
	@if [ -d "$(CNSDK_SOURCE)" ]; then\
		$(TOP_STATUS) $(CNSDK_SOURCE); \
	fi
	@echo "Statusing $(CNSDK) done"

#
# Clean
#
.PHONY: cnsdk-clean

cnsdk-clean:
	@rm -f $(CNSDK_DIR)/.cnsdk_configured
	@if [ -d "$(CNSDK_SOURCE)" ]; then\
		make -C $(CNSDK_SOURCE)/$(CNSDK) clean; \
	fi

#
# Dist clean
#
.PHONY: cnsdk-distclean

cnsdk-distclean:
	@rm -f $(CNSDK_DIR)/.cnsdk_*
#@rm -fr $(CNSDK_SOURCE)

#
# Install
#
.PHONY: cnsdk-install

cnsdk-install:
