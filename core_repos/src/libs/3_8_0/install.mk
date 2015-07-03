TOP        := $(shell pwd)/../..#
include $(TOP)/Target.mk

UCLINUX_KERNEL:=$(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/
utsrelease_h := $(wildcard $(UCLINUX_KERNEL)/include/linux/utsrelease.h)
kernel_version := $(shell grep UTS_RELEASE $(utsrelease_h))
kernel_version := $(shell echo '$(kernel_version)' | sed -n 's/.*\"\(.*\)\".*/\1/p')
SIGMA_SDK_SOURCE := $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)
.PHONY: sigma_sdk

sigma_sdk:

.PHONY: sigma_driver

sigma_driver:
	-if [ -d "$(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/modules/$(kernel_version)/" ]; then	\
		mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;\
		cp -f $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/modules/$(kernel_version)/em8xxx.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/; \
		cp -f $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/modules/$(kernel_version)/llad.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/; \
	fi
	if [ -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/ata/sata_tango3.ko ]; then \
		cp -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/ata/sata_tango3.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;\
	fi
	if [ -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/scsi/scsi_wait_scan.ko ]; then \
		cp -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/scsi/scsi_wait_scan.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;\
	fi
	if [ -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/char/irkernel.ko ]; then \
		cp -f $(SIGMA_SDK_SOURCE)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/drivers/char/irkernel.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;\
	fi
ifeq ($(CONF_PROCPIPE_PLAYER), y)
#	cp -f $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/MRUA_src/proc_pipe/proc_pipe.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;
	cp -f $(SIGMA_SDK_SOURCE)/proc_pipe/proc_pipe.ko $(TOP_INSTALL_ROOTFS_DIR)/lib/modules/;
endif

.PHONY: sigma_isdk

sigma_isdk:

.PHONY: sigma_zboot

sigma_zboot:
