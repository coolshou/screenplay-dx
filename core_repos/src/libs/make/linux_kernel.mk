#
# Defines
#
ifndef  CONF_SIGMA_SDK_VERSION 
CONF_SIGMA_SDK_VERSION := 2.8.3.0# 
endif

SIGMA_SDK_SERVER_URL  		:= $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_DIR         		:= $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      		:= $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
LINUX_KERNEL_SOURCE   		:= $(SIGMA_SDK_SOURCE)/linux_kernel_${CONF_LINUX_KERNEL_VERSION}#
LINUX_KERNEL_PATCH_SOURCE	:= $(SIGMA_SDK_SOURCE)/linux_kernel_${CONF_LINUX_KERNEL_VERSION}-${CONF_LINUX_PATCH_VERSION}_patch#
LINUX_KERNEL_SOURCE_PACKAGE	:= $(LINUX_KERNEL_SOURCE).tar.gz#
LINUX_KERNEL_CONFIG 		:= $(TOP_CONFIG_DIR)/$(CONF_LINUX_KERNEL_CONFIG_FILE)




#
# Download  the source 
#
.PHONY: linux_kernel-downloaded
linux_kernel-downloaded:

#
# Unpack the source
#
.PHONY: linux_kernel-unpacked

linux_kernel-unpacked: $(SIGMA_SDK_DIR)/.linux_kernel_unpacked

$(SIGMA_SDK_DIR)/.linux_kernel_unpacked:
	@echo "Unpacking linux kernel..." 
	@echo "Jimmy: disable @rm -fr $(LINUX_KERNEL_SOURCE) because ${LINUX_KERNEL_SOURCE_PACKAGE} too big to upload to github" 
	#@rm -fr $(LINUX_KERNEL_SOURCE)
	#cd $(SIGMA_SDK_SOURCE); tar xzf ${LINUX_KERNEL_SOURCE_PACKAGE};
	#make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk linux_kernel-unpack
	@touch $@


#
# Patch the source
#
.PHONY: linux_kernel-patched

linux_kernel-patched: $(SIGMA_SDK_DIR)/.linux_kernel_patched

$(SIGMA_SDK_DIR)/.linux_kernel_patched: $(SIGMA_SDK_DIR)/.linux_kernel_unpacked
	@echo "Patch linux kernel..." 
	make -f $(SIGMA_SDK_SOURCE)/downloaded-unpacked-patched.mk linux_kernel-patched
	@echo "finish linux_kernel-patched"
	if [ x$(CONF_PRODUCT_EXT_IOM_T4) == xy ]; then \
		echo "Patching $(LINUX_KERNEL_SOURCE) for $(CONF_PRODUCT) ...";	\
		if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.c" ]; then	\
			cd $(LINUX_KERNEL_SOURCE)/drivers/char;cp -f $(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.c .;        \
		fi; \
		if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.patch" ]; then	\
			cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.patch;	\
		fi; \
	fi
	if [ x$(CONF_PRODUCT_EXT_IOM_X2) == xy ]; then \
		echo "Patching $(LINUX_KERNEL_SOURCE) for $(CONF_PRODUCT) ...";	\
		if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/iom554h_proc.c" ]; then	\
			cd $(LINUX_KERNEL_SOURCE)/drivers/char;cp -f $(LINUX_KERNEL_PATCH_SOURCE)/iom554h_proc.c ./iom554_proc.c;        \
		fi; \
		if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.patch" ]; then	\
			cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/iom554_proc.patch;	\
		fi; \
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/ir_hold_key.patch" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/ir_hold_key.patch;	\
	fi; 
	cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/fix_tangox_enet_tx_pending.patch;	\
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet.c.patch" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet.c.patch;	\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_ethernet_led.c.patch" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_ethernet_led.c.patch;	\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/unaligned.c.patch" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/unaligned.c.patch;	\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_modify_tx_delay_to_1000us" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_modify_tx_delay_to_1000us;	\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_fix_ethernet_hang.patch" ]; then	\
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/tangox_enet_fix_ethernet_hang.patch;	\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/irkernel.c.patch" ]; then \
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/irkernel.c.patch;     \
	fi
	if [ x$(CONF_SYSCONFIG_USING_SQUASHFS) == xy ]; then \
		cd $(LINUX_KERNEL_SOURCE);patch -p0 < $(LINUX_KERNEL_PATCH_SOURCE)/squashfs3.4-patch;\
	fi
	if [ x$(CONF_CRAMFS_GATHER_16MB) == xy ]; then \
		cd $(LINUX_KERNEL_SOURCE);patch -p0 < $(LINUX_KERNEL_PATCH_SOURCE)/cramfs_fs.h.patch;\
	fi
	if [ -f "$(LINUX_KERNEL_PATCH_SOURCE)/mm_page_alloc.c.patch" ]; then \
		cd $(LINUX_KERNEL_SOURCE);patch -p0 <$(LINUX_KERNEL_PATCH_SOURCE)/mm_page_alloc.c.patch; \
	fi


	echo "Patching $@ done"
	@touch $@
#
# config
#
.PHONY: linux_kernel-config

linux_kernel-config: linux_kernel-patched 
	@if [ -f $(LINUX_KERNEL_CONFIG) ]; then	\
		if [ ! -f $(LINUX_KERNEL_SOURCE)/.config ]; then \
			echo "copy $(LINUX_KERNEL_CONFIG) to $(LINUX_KERNEL_SOURCE)/.config ...";	\
			cp -pf $(LINUX_KERNEL_CONFIG) $(LINUX_KERNEL_SOURCE)/.config;	\
		fi	\
	fi 

#
# Configuration
#
.PHONY: linux_kernel-configured

linux_kernel-configured:  linux_kernel-config $(SIGMA_SDK_DIR)/.linux_kernel_configured

$(SIGMA_SDK_DIR)/.linux_kernel_configured: $(SIGMA_SDK_DIR)/.linux_kernel_patched $(SIGMA_SDK_CONFIG) $(TOP_CURRENT_SET)
	@echo "apply kernel config..."
	-make -C $(LINUX_KERNEL_SOURCE) oldconfig 
	@touch $@

#
# Compile
#
.PHONY: linux_kernel-compile

linux_kernel-compile: linux_kernel-configured $(SIGMA_SDK_DIR)/.linux_kernel_compiled

$(SIGMA_SDK_DIR)/.linux_kernel_compiled:
	@echo "Compiling kernel..."
	-mkdir -p $(LINUX_KERNEL_SOURCE)/initramfs_tmp
	-(export INITRAMFS_PATH=$(LINUX_KERNEL_SOURCE)/initramfs_tmp; make -C $(LINUX_KERNEL_SOURCE))
	-(export INITRAMFS_PATH=$(LINUX_KERNEL_SOURCE)/initramfs_tmp; make -C $(LINUX_KERNEL_SOURCE) modules)
	touch $@

#
# Update
#
.PHONY: linux_kernel-update

linux_kernel-update:

#
# Status
#
.PHONY: linux_kernel-status

linux_kernel-status:

#
# Clean
#
.PHONY: linux_kernel-clean

linux_kernel-clean:
	@rm -f .linux_kernel_configured
	@make -C $(LINUX_KERNEL_SOURCE) clean   
	rm -f $(SIGMA_SDK_DIR)/.linux_kernel_compiled
	

#
# Dist clean
#
.PHONY: linux_kernel-distclean

linux_kernel-distclean:
	@rm -f .linux*

#
# Install
#
.PHONY: linux_kernel-install

linux_kernel-install:
	cd $(LINUX_KERNEL_SOURCE); make modules_install INSTALL_MOD_PATH=$(TOP_INSTALL_ROOTFS_DIR);	\
	if [ x$(CONF_PRODUCT_EXT_WDTV_RV) == xy ]; then \
	mkdir -p $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/lib/modules/;	\
	if [ -f $(LINUX_KERNEL_SOURCE)/drivers/net/r8169.ko ]; then \
	cp -f $(LINUX_KERNEL_SOURCE)/drivers/net/r8169.ko $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/lib/modules/;	\
	fi	\
	fi
	if [ "x$(CONF_NFS_DEBUG)" == "xy" ]; then	\
		echo "Install modules for NFS debug....";	\
		#cd $(LINUX_KERNEL_SOURCE); make modules_install INSTALL_MOD_PATH=$(TOP_INSTALL_ROOTFS_DIR);	\
		touch $(TOP_INSTALL_ROOTFS_DIR)/nfs_debug;	\
	fi


