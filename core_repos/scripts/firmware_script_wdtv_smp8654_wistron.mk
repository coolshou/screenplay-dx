
ROMFS_BIN_NAME	:= romfs.bin

SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#

ZBOOT_FILE            := $(TOP_BUILD_DIR)/zboot.bin
YAMON_FILE            := $(TOP_BUILD_DIR)/zbimage-yamon-2.13
IMAT_FILE             := $(TOP_BUILD_DIR)/imat.bin
XMAT_FILE             := $(TOP_BUILD_DIR)/xmat.bin
KERNEL_FILE           := $(TOP_BUILD_DIR)/zbimage-linux-xload
ROOTFS_FILE           := ${TOP_BUILD_DIR}/$(ROMFS_BIN_NAME)
FF_TMP_DIR            := $(TOP_BUILD_DIR)/full_firmware
PKG_TMP_DIR           := $(TOP_BUILD_DIR)/package


include $(TOP_SCRIPTS_DIR)/build_sigma_nand_image.mk


ifeq (x$(CONF_SECURITY_USE_CPU_BINDING), xy)
firmware: rootfs_for_primary_system rootfs_for_application_system bootloader firmware_full firmware_package generate_md5sum_info check_cpu_binding
else
firmware: rootfs_for_primary_system rootfs_for_application_system bootloader firmware_full firmware_package generate_md5sum_info
endif

bootloader:
	- cp -vf $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_BOOT_LOADER)/xos/xboot2/xmasboot/nand_st2/phyblock0-0x20000padded.922-A2 $(TOP_BUILD_DIR)/zboot.bin
	- cp -vf $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_YAMON)/bin/zbimage-yamon-2.13 $(TOP_BUILD_DIR) 
#	dd if=$(TOP_BUILD_DIR)/zboot2.bin of=$(TOP_BUILD_DIR)/boot_loader
#	dd if=$(TOP_BUILD_DIR)/zbimage-yamon-2.11 of=$(TOP_BUILD_DIR)/boot_loader bs=94208 seek=1

flash_image: generate_16M_production_image generate_16M_f1_image

generate_16M_production_image:
	(cd $(TOP_BUILD_DIR);echo "okok" > okok;cat boot_loader /dev/zero|head -c $(CONF_BOOT_LOADER_SIZE) > 16M-flash-img-prod;cat primary_system.bin /dev/zero|head -c $(CONF_PRIMARY_SYSTEM_SIZE) >> 16M-flash-img-prod;cat $(ROMFS_BIN_NAME) /dev/zero|head -c `expr $(CONF_APP_ROMFS_SIZE) - 4` >> 16M-flash-img-prod;cat okok /dev/zero|head -c 262148 >> 16M-flash-img-prod;rm okok)

generate_16M_f1_image:
	(cd $(TOP_BUILD_DIR);echo "f1f1" > f1f1;cat boot_loader /dev/zero|head -c $(CONF_BOOT_LOADER_SIZE) > 16M-flash-img-f1;cat primary_system.bin /dev/zero|head -c $(CONF_PRIMARY_SYSTEM_SIZE) >> 16M-flash-img-f1;cat romfs.bin /dev/zero|head -c `expr $(CONF_APP_ROMFS_SIZE) - 4` >> 16M-flash-img-f1;cat f1f1 /dev/zero|head -c 262148 >> 16M-flash-img-f1;rm f1f1)

firmware_package:
ifeq (x$(CONF_FIRMWARE_UPGRADE_PLUGIN), xy)
	@echo -en "\n\\033[0;33m Createing full firmware package(.pkg = romfs(.fff + .bin))... \\033[0m\n"	
	rm -rf $(PKG_TMP_DIR);
	mkdir -p $(PKG_TMP_DIR);
	cp -vf ${TOP_BUILD_DIR}/$(CONF_FIRMWARE_VER_FILE) $(PKG_TMP_DIR)
	cp -vf ${TOP_BUILD_DIR}/$(CONF_FIRMWARE_BIN_FILE) $(PKG_TMP_DIR);
	cp -vf $(TOP_BUILD_DIR)/$(CONF_FIRMWARE_FULL_FILE) $(PKG_TMP_DIR);
	genromfs -d $(PKG_TMP_DIR) -f ${TOP_BUILD_DIR}/$(CONF_FIRMWARE_PACKAGE_FILE).tmp
	(cd ${TOP_BUILD_DIR}/; md5sum $(CONF_FIRMWARE_PACKAGE_FILE).tmp > ./md5_pkg;  cat ./md5_pkg |head -c 32|cat - $(CONF_FIRMWARE_PACKAGE_FILE).tmp > $(CONF_FIRMWARE_PACKAGE_FILE); rm $(CONF_FIRMWARE_PACKAGE_FILE).tmp)
	rm -rf $(PKG_TMP_DIR)
	@if [ `stat -c %s ${TOP_BUILD_DIR}/$(CONF_FIRMWARE_PACKAGE_FILE)` -gt ${CONF_STORAGE_PARTITION_SIZE} ]; then \
		echo -e "\E[31;47m WARNING: The package file($(CONF_FIRMWARE_PACKAGE_FILE)) size exceededs storage partition size(${CONF_STORAGE_PARTITION_SIZE})\E[0m"; \
		false;\
	fi
	@echo -en "\n\\033[0;33m Createing full firmware... Done \\033[0m\n"	
endif

firmware_full:
	@echo -en "\n\\033[0;33m Createing full firmware... \\033[0m\n"	
	rm -rf $(FF_TMP_DIR);
	mkdir -p $(FF_TMP_DIR); mkdir -p $(FF_TMP_DIR)/dev;
	echo VERSION=\'$(CONF_VERSION)\' > $(FF_TMP_DIR)/version;
	touch $(FF_TMP_DIR)/GPL;
	# Todo : file size check
	if [ -f $(ZBOOT_FILE) ] && [ x$(CONF_BOOTLOADER_UPGRADE) == xy ]; then \
		cp -vf $(ZBOOT_FILE) $(FF_TMP_DIR)/$(CONF_BOOTLOADER_MTD_PARTITION).bin; \
	fi
	if [ -f $(KERNEL_FILE) ]; then \
		md5sum $(KERNEL_FILE) | head -c 32  > $(FF_TMP_DIR)/md5_kernel; \
		cp -vf $(KERNEL_FILE) $(FF_TMP_DIR)/$(CONF_KERNEL_MTD_PARTITION).bin; \
		if [ x$(CONF_KERNEL_MTD_MIRROR_PARTITION) != x ]; then \
			(cd $(FF_TMP_DIR) && ln -s ../$(CONF_KERNEL_MTD_PARTITION).bin ./$(CONF_KERNEL_MTD_MIRROR_PARTITION).bin); \
		fi; \
	fi
	if [ -f $(IMAT_FILE) ] && [ x$(CONF_MTD_IMAT_UPGRADE) == xy ]; then \
		cp -vf $(IMAT_FILE) $(FF_TMP_DIR)/$(CONF_MTD_IMAT_PARTITION).bin; \
	fi
	if [ -f $(XMAT_FILE) ] && [ x$(CONF_MTD_XMAT_UPGRADE) == xy ]; then \
		cp -vf $(XMAT_FILE) $(FF_TMP_DIR)/$(CONF_MTD_XMAT_PARTITION).bin; \
	fi
	genromfs -d $(FF_TMP_DIR) -f $(TOP_BUILD_DIR)/$(CONF_FIRMWARE_FULL_FILE)
	rm -rf $(FF_TMP_DIR)
	@echo -en "\n\\033[0;33m Createing full firmware... Done \\033[0m\n"	

component_check:
	if [ ! -f $(TOP_BUILD_DIR)/zboot2.bin ] || [ ! -f $(TOP_BUILD_DIR)/zbimage-yamon-2.11 ]; then \
		echo "ERROR: =You have to build zboot and yamon...";\
		false;\
	fi
	if [ x$(CONF_BUILD_ROOTFS_PRIMARY_SYSTEM) != xy ] || [ x$(CONF_BUILD_ROOTFS) != xy ]; then	\
		echo "ERROR: You have to build rootfs and rootfs of primary system to make a firmware...";\
		false;\
	fi
	echo "Build rootfs of primary system...";\
	if [ ! -d $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/${CONF_SIGMA_SDK_CPU_KEY} ]; then	\
		echo "ERROR: CPU key directory not found..."	;\
		false;\
	fi;\
	if [ ! -d $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/linux_kernel_${CONF_LINUX_KERNEL_VERSION} ]; then \
		echo "ERROR: There is no linux kernel...";\
		false;\
	fi;\
	if [ ! -d $(TOP_LIBS_DIR)/$(CONF_RESOURCE)/splash_screen/8654 ]; then	\
		echo "ERROR: No splash screen found...";\
		false;\
	fi;\
	if [ ! -d $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR) ]; then \
		echo "ERROR: rootfs of primary system is not installed...";\
		false;\
	fi;\

generate_primary_system:

rootfs_for_primary_system: generate_primary_system

rootfs_for_application_system: generate_romfs generate_bin_file generate_ver_file
	if [ `stat -c %s ${TOP_BUILD_DIR}/$(ROMFS_BIN_NAME)` -gt ${CONF_APP_ROMFS_SIZE} ]; then \
		echo -e "\E[31;47mThe rootfs size exceededs (${CONF_APP_ROMFS_SIZE}), please check it\E[0m"; \
		false;\
	else \
		cp ${TOP_BUILD_DIR}/$(ROMFS_BIN_NAME) ${TOP_BUILD_DIR}/rootfs; \
	fi
		
check_mkcramfs:

generate_romfs: check_mkcramfs
ifeq (x${CONF_SECURITY_PROPRIETARY_ENCRYPT}, xy)
	modprobe cryptoloop
	modprobe aes_generic
	mkdir -p ${TOP_BUILD_ROOTFS_DIR}/proprietary
ifeq (x${CONF_CONSOLE_SECURE}, xy)
	mv ${TOP_BUILD_ROOTFS_DIR}/bin/gbus_read_serial_num ${TOP_BUILD_ROOTFS_DIR}/proprietary;
endif
	mv ${TOP_BUILD_ROOTFS_DIR}/bin/dmaosd ${TOP_BUILD_ROOTFS_DIR}/proprietary;
	mv ${TOP_BUILD_ROOTFS_DIR}/netflix ${TOP_BUILD_ROOTFS_DIR}/proprietary;
	mv ${TOP_BUILD_ROOTFS_DIR}/bin/MediaLogic ${TOP_BUILD_ROOTFS_DIR}/proprietary;
	mv ${TOP_BUILD_ROOTFS_DIR}/bin/MediaLogic_PIC ${TOP_BUILD_ROOTFS_DIR}/proprietary;
	dd if=/dev/zero of=${TOP_BUILD_ROOTFS_DIR}/home/file bs=1M count=15;
	genromfs -d ${TOP_BUILD_ROOTFS_DIR}/proprietary -f ${TOP_BUILD_ROOTFS_DIR}/pro-cramfs;
ifeq (x${CONF_SECURITY_USE_JANUS_SHA1SUM}, xy)
	if [ ! -f $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_JANUS_SHA1SUM_FILENAME) ]; then \
		echo "You must put the key to the config directory"; \
		false;\
	fi
	echo `cat $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_JANUS_SHA1SUM_FILENAME)` | sudo $(TOP_TOOLS_DIR)/losetup -e aes /dev/loop0 ${TOP_BUILD_ROOTFS_DIR}/home/file -p 0;
endif
ifeq (x${CONF_SECURITY_USE_CPU_KEY_SHA1SUM}, xy)
	if [ ! -f $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_CPU_KEY_SHA1SUM_FILENAME) ]; then \
		echo "You must put the key to the config directory";\
		false;\
	fi
	echo `cat $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_CPU_KEY_SHA1SUM_FILENAME)` | sudo $(TOP_TOOLS_DIR)/losetup -e aes /dev/loop0 ${TOP_BUILD_ROOTFS_DIR}/home/file -p 0;
endif
ifeq (x${CONF_SECURITY_USE_IPTOKEN_SHA1SUM}, xy)
	if [ ! -f $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_IPTOKEN_SHA1SUM_FILENAME) ]; then \
		echo "You must put the key to the config directory";\
		false;\
	fi
	echo `cat $(TOP_CONFIG_DIR)/$(CONF_SECURITY_USE_IPTOKEN_SHA1SUM_FILENAME)` | sudo $(TOP_TOOLS_DIR)/losetup -e aes /dev/loop0 ${TOP_BUILD_ROOTFS_DIR}/home/file -p 0;
endif
	cat ${TOP_BUILD_ROOTFS_DIR}/pro-cramfs > /dev/loop0;
	rm -rf ${TOP_BUILD_ROOTFS_DIR}/proprietary;
	rm -rf ${TOP_BUILD_ROOTFS_DIR}/pro-cramfs;
	sudo $(TOP_TOOLS_DIR)/losetup -d /dev/loop0
endif	
	rm -f ${TOP_BUILD_DIR}/$(ROMFS_BIN_NAME)
	tools/mksquashfs ${TOP_BUILD_ROOTFS_DIR} ${TOP_BUILD_DIR}/$(ROMFS_BIN_NAME)
ifeq (x${CONF_BOOT_AUTH}, xy)	
	(cd ${TOP_BUILD_DIR} ; ./sign_tool $(TOP_CONFIG_DIR)/$(CONF_BOOT_AUTH_KEY) $(ROMFS_BIN_NAME))
endif
ifeq (x${CONF_FWUP_ENCRYPT}, xy)
	(cd ${TOP_BUILD_DIR} ; $(TOP)/src/misc/fwup_security/mkencfw.sh $(ROMFS_BIN_NAME) $(TOP)/config/$(CONF_FWUP_SEK_FILE) $(CONF_FIRMWARE_BIN_FILE))
endif


generate_bin_file:
	(cd ${TOP_BUILD_DIR}/; ./host/bin/mkfw romfs.bin.tail 2 $(ROMFS_BIN_NAME))
	(cd ${TOP_BUILD_DIR}/; md5sum romfs.bin.tail > md5_fw;  cat md5_fw |head -c 32|cat - romfs.bin.tail > $(CONF_FIRMWARE_BIN_FILE); rm romfs.bin.tail )
	
generate_ver_file:
	(cd ${TOP_BUILD_DIR}/;echo VERSION=\'$(CONF_VERSION)\' > $(CONF_FIRMWARE_VER_FILE); echo LOCATION=\'$(CONF_FIRMWARE_BIN_FILE)\' >> $(CONF_FIRMWARE_VER_FILE))
	if [ x$(CONF_FIRMWARE_UPGRADE_WORKAROUND) == xy ]; then \
                (cd ${TOP_BUILD_DIR}/;echo KERNEL=\'Yes\' >> $(CONF_FIRMWARE_VER_FILE));\
        fi
ifneq (x$(CONF_FIRMWARE_PACKAGE_FILE), x)
	(cd ${TOP_BUILD_DIR}/;echo PKG_LOCATION=\'$(CONF_FIRMWARE_PACKAGE_FILE)\' >> $(CONF_FIRMWARE_VER_FILE))
endif

generate_md5sum_info:
ifneq (x$(CONF_FIRMWARE_PACKAGE_FILE), x)
	(cd ${TOP_BUILD_DIR}/; echo VERSION=\'$(CONF_VERSION)\'> ./md5sum.txt && md5sum $(CONF_FIRMWARE_BIN_FILE) >> ./md5sum.txt && md5sum $(CONF_FIRMWARE_FULL_FILE) >> ./md5sum.txt && md5sum $(CONF_FIRMWARE_PACKAGE_FILE) >> ./md5sum.txt)
else
	(cd ${TOP_BUILD_DIR}/; echo VERSION=\'$(CONF_VERSION)\'> ./md5sum.txt && md5sum $(CONF_FIRMWARE_BIN_FILE) >> ./md5sum.txt && md5sum $(CONF_FIRMWARE_FULL_FILE) >> ./md5sum.txt)
endif

check_cpu_binding:

include $(TOP_SCRIPTS_DIR)/firmware_script_wdtv_combine_house_hut.mk

