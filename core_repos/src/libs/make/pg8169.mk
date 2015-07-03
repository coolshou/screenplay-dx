##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# pg8169 makefile fragments 
##############################################################################

#
# Defines
#

SIGMA_SDK_DIR         		:= $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      		:= $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
LINUX_KERNEL_SOURCE   		:= $(SIGMA_SDK_SOURCE)/linux_kernel_${CONF_LINUX_KERNEL_VERSION}#
KERNELDIR := $(LINUX_KERNEL_SOURCE)

PG8169             := pg8169
PG8169_SERVER_URL  := $(TOP_LIBS_URL)/pg8169/$(PG8169)
PG8169_DIR         := $(TOP_LIBS_DIR)#
PG8169_SOURCE      := $(PG8169_DIR)/$(PG8169)
PG8169_CONFIG      := 

#
# Download  the source 
#
.PHONY: pg8169-downloaded

pg8169-downloaded: $(PG8169_DIR)/.pg8169_downloaded

$(PG8169_DIR)/.pg8169_downloaded:
	@echo "Downloading $(PG8169) from $(PG8169_SERVER_URL) ..."
	@if [ ! -d "$(PG8169_SOURCE)" ]; then \
		cd $(PG8169_DIR); \
		$(TOP_DOWNLOAD) $(PG8169_SERVER_URL); \
	fi
	@echo "Downloading $(PG8169) from $(PG8169_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: pg8169-unpacked

pg8169-unpacked: $(PG8169_DIR)/.pg8169_unpacked

$(PG8169_DIR)/.pg8169_unpacked: $(PG8169_DIR)/.pg8169_downloaded $(PG8169_SOURCE)/$(PG8169).tar.gz
	@echo "Unpacking $(PG8169) ..."
	if [ -d "$(PG8169_SOURCE)/$(PG8169)" ]; then \
		rm -fr $(PG8169_SOURCE)/$(PG8169); \
	fi
	cd $(PG8169_SOURCE); tar zxvf $(PG8169).tar.gz
	@echo "Unpacking $(PG8169) done"
	@touch $@


#
# Patch the source
#
.PHONY: pg8169-patched

pg8169-patched: $(PG8169_DIR)/.pg8169_patched

$(PG8169_DIR)/.pg8169_patched: $(PG8169_DIR)/.pg8169_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: pg8169-config

pg8169-config: 

#
# Configuration
#
.PHONY: pg8169-configured

pg8169-configured:  pg8169-config $(PG8169_DIR)/.pg8169_configured

$(PG8169_DIR)/.pg8169_configured: $(PG8169_DIR)/.pg8169_patched $(PG8169_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(PG8169) ..."
	@echo "Configuring $(PG8169) done"
	@touch $@

#
# Compile
#
.PHONY: pg8169-compile

pg8169-compile: $(PG8169_DIR)/.pg8169_compiled

$(PG8169_DIR)/.pg8169_compiled: $(PG8169_DIR)/.pg8169_configured
	@echo "Compiling $(PG8169) ..."
	make -C $(PG8169_SOURCE)/$(PG8169) -f Makefile.mips CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) KERNELDIR=$(KERNELDIR)
	@echo "Compiling $(PG8169) done"
	@touch $@

#
# Update
#
.PHONY: pg8169-update

pg8169-update:
	@echo "Updating $(PG8169) ..."
	@if [ -d "$(PG8169_SOURCE)" ]; then\
		$(TOP_UPDATE) $(PG8169_SOURCE); \
	fi
	@echo "Updating $(PG8169) done"

#
# Status
#
.PHONY: pg8169-status

pg8169-status:
	@echo "Statusing $(PG8169) ..."
	@if [ -d "$(PG8169_SOURCE)" ]; then\
		$(TOP_STATUS) $(PG8169_SOURCE); \
	fi
	@echo "Statusing $(PG8169) done"

#
# Clean
#
.PHONY: pg8169-clean

pg8169-clean:
	@rm -f $(PG8169_DIR)/.pg8169_configured
	@if [ -d "$(PG8169_SOURCE)" ]; then\
		make -C $(PG8169_SOURCE)/$(PG8169) -f Makefile.mips KERNELDIR=$(KERNELDIR) clean; \
	fi

#
# Dist clean
#
.PHONY: pg8169-distclean

pg8169-distclean:
	@rm -f $(PG8169_DIR)/.pg8169_*

#
# Install
#
.PHONY: pg8169-install

pg8169-install:
	cp -f $(PG8169_SOURCE)/$(PG8169)/pgdrv.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/
	cp -f $(PG8169_SOURCE)/$(PG8169)/rtnicpg-mipsel-32r2 $(TOP_INSTALL_ROOTFS_DIR)/bin/
