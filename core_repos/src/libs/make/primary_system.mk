
ROOTFS_PRIMARY_SKELETON             := rootfs_primary_system_skeleton

ROOTFS_PRIMARY_SYSTEM_SERVER_URL	:= $(TOP_LIBS_URL)/$(ROOTFS_PRIMARY_SKELETON)
ROOTFS_PRIMARY_SYSTEM_SRC_DIR		:= $(TOP_LIBS_DIR)/$(ROOTFS_PRIMARY_SKELETON)
WDTVFWMAKER_SRC_DIR			:= $(ROOTFS_PRIMARY_SYSTEM_SRC_DIR)/wdtvfwmaker

#
# Download  the source 
#
.PHONY: primary_system-downloaded

primary_system-downloaded: $(TOP_LIBS_DIR)/.primary_system_downloaded

$(TOP_LIBS_DIR)/.primary_system_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: primary_system-unpacked

primary_system-unpacked: $(TOP_LIBS_DIR)/.primary_system_unpacked

$(TOP_LIBS_DIR)/.primary_system_unpacked: $(TOP_LIBS_DIR)/.primary_system_downloaded


#
# Patch the source
#
.PHONY: primary_system-patched

primary_system-patched: $(TOP_LIBS_DIR)/.primary_system_patched

$(TOP_LIBS_DIR)/.primary_system_patched: $(TOP_LIBS_DIR)/.primary_system_unpacked

#
# config
#
.PHONY: primary_system-config

primary_system-config: 

#
# Configuration
#
.PHONY: primary_system-configured

primary_system-configured:  primary_system-config $(TOP_LIBS_DIR)/.primary_system_configured

$(TOP_LIBS_DIR)/.primary_system_configured: $(TOP_LIBS_DIR)/.primary_system_patched

#
# Compile
#
.PHONY: primary_system-compile

primary_system-compile: $(TOP_LIBS_DIR)/.primary_system_compiled

$(TOP_LIBS_DIR)/.primary_system_compiled: $(TOP_LIBS_DIR)/.primary_system_configured
	make -C $(WDTVFWMAKER_SRC_DIR)
	touch $@

#
# Update
#
.PHONY: primary_system-update

primary_system-update:
	@echo "Updating : $(ROOTFS_PRIMARY_SKELETON) ..."
	@if [ -d "$(ROOTFS_PRIMARY_SKELETON)" ]; then\
		$(TOP_UPDATE) $(ROOTFS_PRIMARY_SKELETON); \
	fi
	@echo "Updating $(ROOTFS_PRIMARY_SKELETON) done"

#
# Status
#
.PHONY: primary_system-status

primary_system-status:
	@echo "Statusing : $(ROOTFS_PRIMARY_SKELETON) ..."
	@if [ -d "$(ROOTFS_PRIMARY_SKELETON)" ]; then\
		$(TOP_STATUS) $(ROOTFS_PRIMARY_SKELETON); \
	fi
	@echo "Statusing $(ROOTFS_PRIMARY_SKELETON) done"

#
# Clean
#
.PHONY: primary_system-clean

primary_system-clean:

#
# Dist clean
#
.PHONY: primary_system-distclean

primary_system-distclean:
	@rm -rf $(TOP_LIBS_DIR)/.primary*

#
# Install
#
.PHONY: primary_system-install

primary_system-install:
	@echo -en "\n\\033[0;33mInstalling primary_system ...\\033[0m\n"
	mkdir -p $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)
	echo "export SYSCONF_BUILD_DATE=$(STAMP)" > $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_BUILD_VERSION=$(CONF_VERSION)" > $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_BIN=$(CONF_FIRMWARE_BIN_FILE)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_VER=$(CONF_FIRMWARE_VER_FILE)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_BOOTLOADER_MTD_PARTITION=$(CONF_BOOTLOADER_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_KERNEL_MTD_PARTITION=$(CONF_KERNEL_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_MTD_PARTITION=$(CONF_FIRMWARE_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_MTD_SIZE=$(CONF_APP_ROMFS_SIZE)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig
	if [ x$(CONF_FIRMWARE_STORAGE_PARTITION) != x ]; then \
		if [ $(CONF_STORAGE_PARTITION_SIZE) -lt $(CONF_APP_ROMFS_SIZE) ]; then \
			printf "ERROR!! Storage partition size (%d) is less then application partition size (%d) \n" $(CONF_STORAGE_PARTITION_SIZE) $(CONF_APP_ROMFS_SIZE) ; \
			exit 1 ; \
		fi ; \
		echo "export SYSCONF_FIRMWARE_STORAGE_PARTITION=$(CONF_FIRMWARE_STORAGE_PARTITION)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig ;\
		echo "export SYSCONF_STORAGE_PARTITION_SIZE=$(CONF_STORAGE_PARTITION_SIZE)" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig ;\
	fi
	if [ x$(CONF_PRODUCT_EXT_WDTV_VILLA) == xy ] || [ x$(CONF_PRODUCT_EXT_WDTV_HOUSE) == xy ] || [ x$(CONF_PRODUCT_EXT_WDTV_HUT) == xy ]; then \
		echo "export SYSCONF_DOUBLE_SPLASH_SCREEN=y" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig	;\
	fi
	if [ x$(CONF_FWUP_ENCRYPT) == xy ]; then \
		echo "export SYSCONF_FWUP_ENCRYPT=y" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig   ;\
	fi
	if [ x$(CONF_BOOT_AUTH) == xy ]; then \
		echo "export SYSCONF_BOOT_AUTH=y" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig   ;\
	fi
	if [ x$(CONF_SYSCONFIG_USING_SQUASHFS) == xy ]; then \
		echo "export SYSCONF_USING_SQUASHFS=y" >> $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/sysconfig   ;\
	fi
	if [ x$(CONF_ROOTFS_PRIMARY_SYSTEM_SKELETON_GENERIC) == xy ]; then \
		( cd $(ROOTFS_PRIMARY_SYSTEM_SRC_DIR)/generic/mandatory/; tar cf - * ) | ( cd $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) && tar xf -);	\
	fi
	if [ x$(CONF_PLATFORM_SMP8634) == xy ]; then \
		( cd $(ROOTFS_PRIMARY_SYSTEM_SRC_DIR)/platform_smp8634/mandatory/; tar cf - *) | (cd $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) && tar xf -);  \
	fi
	if [ x$(CONF_PLATFORM_SMP8654) == xy ]; then \
		( cd $(ROOTFS_PRIMARY_SYSTEM_SRC_DIR)/platform_smp8654/mandatory/; tar cf - *) | (cd $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) && tar xf -);  \
		mkdir -p $(HOST_TOOL_DIR);\
		cp -f $(WDTVFWMAKER_SRC_DIR)/mkfw $(HOST_TOOL_DIR);\
	fi
	if [ x$(CONF_BUILD_ROOTFS_PRIMARY_SYSTEM_PRIMARY_SYSTEM) == xy ]; then \
		echo nothing;	\
	fi
	if [ x$(CONF_FWUP_ENCRYPT) == xy ]; then \
		cp -f $(BIN_DIR)/fwup_dec $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/bin; \
		chmod +x $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/bin/fwup_dec; \
	fi
	if [ x$(CONF_BOOT_AUTH) == xy ]; then \
		cp -f $(TOP_MISC_DIR)/boot_auth/boot_auth $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/bin; \
		chmod +x $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/bin/boot_auth; \
		openssl asn1parse <$(TOP_CONFIG_DIR)/$(CONF_BOOT_AUTH_KEY) | head -n 3 | tail -n 1 | cut -d':' -f4 | xargs tobin.bash > $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)/mnt/mykey.pub; \
		cp -f $(TOP_MISC_DIR)/boot_auth/sign_tool $(TOP_BUILD_DIR); \
		chmod +x $(TOP_BUILD_DIR)/sign_tool; \
	fi
	find $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) -type f -exec file {} \; | grep -v "\.ko" | grep "not\ stripped" | awk -F ":" '{ print $$1 }' | xargs $(STRIP) 
	find $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) -name .svn -exec rm -rf {} \; &> /dev/null; true
