
ROOTFS_SKELETON     := rootfs_skeleton

ROOTFS_SERVER_URL	:= $(TOP_LIBS_URL)/$(ROOTFS_SKELETON)
ROOTFS_SRC_DIR		:= $(TOP_LIBS_DIR)/$(ROOTFS_SKELETON)

UCLIBC_SERVER_URL	:= $(TOP_LIBS_URL)/uClibc_binary/$(CONF_UCLIBC_VERSION)
UCLIBC_SRC_DIR		:= $(TOP_LIBS_DIR)/$(CONF_UCLIBC_VERSION)

GLIBC_SERVER_URL	:= $(TOP_LIBS_URL)/GLIBC_binary/$(CONF_GLIBC_VERSION)
GLIBC_SRC_DIR		:= $(TOP_LIBS_DIR)/$(CONF_GLIBC_VERSION)

RESOURCE_SERVER_URL	:= $(TOP_RESOURCE_URL)/$(CONF_RESOURCE)
RESOURCE_SRC_DIR	:= $(TOP_LIBS_DIR)/$(CONF_RESOURCE)/resource

ifeq (x$(CONF_SUPPORT_EXTRA_RESOURCE), xy)
EXTRA_RESOUCRE_SERVER_URL	:= $(TOP_RESOURCE_URL)/$(CONF_EXTRA_RESOURCE)
EXTRA_RESOURCE_SRC_DIR		:= $(TOP_LIBS_DIR)/$(CONF_EXTRA_RESOURCE)/resource
endif

DATE                := $(CONF_PRODUCT)_$(CONF_MODEL)_$(STAMP)

#
# Download  the source 
#
.PHONY: rootfs-downloaded

rootfs-downloaded: $(TOP_LIBS_DIR)/.rootfs_downloaded

$(TOP_LIBS_DIR)/.rootfs_downloaded:
	@touch $@

#
# Unpack the source
#
.PHONY: rootfs-unpacked

rootfs-unpacked: $(TOP_LIBS_DIR)/.rootfs_unpacked

$(TOP_LIBS_DIR)/.rootfs_unpacked: $(TOP_LIBS_DIR)/.rootfs_downloaded


#
# Patch the source
#
.PHONY: rootfs-patched

rootfs-patched: $(TOP_LIBS_DIR)/.rootfs_patched

$(TOP_LIBS_DIR)/.rootfs_patched: $(TOP_LIBS_DIR)/.rootfs_unpacked

#
# config
#
.PHONY: rootfs-config

rootfs-config: 

#
# Configuration
#
.PHONY: rootfs-configured

rootfs-configured:  rootfs-config $(TOP_LIBS_DIR)/.rootfs_configured

$(TOP_LIBS_DIR)/.rootfs_configured: $(TOP_LIBS_DIR)/.rootfs_patched

#
# Compile
#
.PHONY: rootfs-compile

rootfs-compile: $(TOP_LIBS_DIR)/.rootfs_compiled

$(TOP_LIBS_DIR)/.rootfs_compiled: $(TOP_LIBS_DIR)/.rootfs_configured

#
# Update
#
.PHONY: rootfs-update

rootfs-update:
	@echo "Updating resource: $(CONF_RESOURCE) ..."
	@if [ -d "$(CONF_RESOURCE)" ]; then\
		$(TOP_UPDATE) $(CONF_RESOURCE); \
	fi
	@if [ -d "$(CONF_EXTRA_RESOURCE)" ]; then\
		$(TOP_UPDATE) $(CONF_EXTRA_RESOURCE); \
	fi
	@echo "Updating $(CONF_RESOURCE) done"
	@echo "Updating : $(ROOTFS_SKELETON) ..."
	@if [ -d "$(ROOTFS_SKELETON)" ]; then\
		$(TOP_UPDATE) $(ROOTFS_SKELETON); \
	fi
	@echo "Updating $(ROOTFS_SKELETON) done"

#
# Status
#
.PHONY: rootfs-status

rootfs-status:
	@echo "Statusing resource: $(CONF_RESOURCE) ..."
	@if [ -d "$(CONF_RESOURCE)" ]; then\
		$(TOP_STATUS) $(CONF_RESOURCE); \
	fi
	@if [ -d "$(CONF_EXTRA_RESOURCE)" ]; then\
		$(TOP_STATUS) $(CONF_EXTRA_RESOURCE); \
	fi
	@echo "Statusing $(CONF_RESOURCE) done"
	@echo "Statusing : $(ROOTFS_SKELETON) ..."
	@if [ -d "$(ROOTFS_SKELETON)" ]; then\
		$(TOP_STATUS) $(ROOTFS_SKELETON); \
	fi
	@echo "Statusing $(ROOTFS_SKELETON) done"

#
# Clean
#
.PHONY: rootfs-clean

rootfs-clean:

#
# Dist clean
#
.PHONY: rootfs-distclean

rootfs-distclean:
	@rm -f $(TOP_LIBS_DIR)/.rootfs_*



#
# Install
#
.PHONY: rootfs-install

rootfs-install:
	@echo -en "\n\\033[0;33mInstalling rootfs...\\033[0m\n"
	@mkdir -p $(TOP_INSTALL_ROOTFS_DIR)
	@mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc
	echo "export SYSCONF_BUILD_DATE=$(STAMP)" > $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_BUILD_VERSION=$(CONF_VERSION)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_BIN=$(CONF_FIRMWARE_BIN_FILE)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_VER=$(CONF_FIRMWARE_VER_FILE)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_BOOTLOADER_MTD_PARTITION=$(CONF_BOOTLOADER_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_KERNEL_MTD_PARTITION=$(CONF_KERNEL_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_MTD_PARTITION=$(CONF_FIRMWARE_MTD_PARTITION)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_MTD_SIZE=$(CONF_APP_ROMFS_SIZE)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
ifeq (x$(CONF_DUAL_ROMFS), xy)
	echo "export SYSCONF_DUAL_ROMFS=$(CONF_DUAL_ROMFS)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_FIRMWARE_MTD_MIRROR_PARTITION=$(CONF_FIRMWARE_MTD_MIRROR_PARTITION)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
endif
ifeq (x$(CONF_SAVE_DEFAULT_SETTING_IN_LAST_PARTITON), xy)
	echo "export SYSCONF_LAST_PARTITION_NODE_NAME=$(CONF_LAST_PARTITION_NODE_NAME)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
	echo "export SYSCONF_STATIC_CONFIG_MOUNT_POINT=$(CONF_STATIC_CONFIG_MOUNT_POINT)" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
endif
ifeq (x$(CONF_DTS_CHIP_SET), xy)
	echo "export IS_DTS=y" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
else
	echo "export IS_DTS=n" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
endif
ifeq (x$(CONF_DMA_DTCP_SIGMA), xy)
	echo "export IS_DTCP=y" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
else
	echo "export IS_DTCP=n" >> $(TOP_INSTALL_ROOTFS_DIR)/sysconfig
endif
	@if [ x$(CONF_ROOTFS_SKELETON_GENERIC) == xy ]; then \
		( cd $(ROOTFS_SRC_DIR)/generic/mandatory/; tar cf - * ) | ( cd $(TOP_INSTALL_ROOTFS_DIR) && tar xf -);	\
	fi
	@if [ x$(CONF_PLATFORM_SMP8634) == xy ]; then \
		( cd $(ROOTFS_SRC_DIR)/platform_smp8634/mandatory/; tar cf - *) | (cd $(TOP_INSTALL_ROOTFS_DIR) && tar xf -);  \
	fi
	@if [ x$(CONF_PLATFORM_SMP8654) == xy ]; then \
		( cd $(ROOTFS_SRC_DIR)/platform_smp8654/mandatory/; tar cf - *) | (cd $(TOP_INSTALL_ROOTFS_DIR) && tar xf -);  \
	fi
	@mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/lib
	@echo -en "\n\\033[0;33m Installing shared objects... ...\\033[0m\n"
ifeq (x$(CONF_PLATFORM_X86),xy)
	-cp -a $(SYSLIB_PREFIX)/lib/*so* $(TOP_INSTALL_ROOTFS_DIR)/lib
else
	cp -a $(SYSLIB_PREFIX)/lib/*so* $(TOP_INSTALL_ROOTFS_DIR)/lib
endif
	@if [ x$(CONF_INSTALL_UCLIBC) == xy ]; then	\
		(cd $(UCLIBC_SRC_DIR); tar cf - * ) | ( cd $(TOP_INSTALL_ROOTFS_DIR)/lib && tar xf - );\
	fi
	@if [ x$(CONF_INSTALL_GLIBC) == xy ]; then	\
		(cd $(GLIBC_SRC_DIR); tar cf - * ) | ( cd $(TOP_INSTALL_ROOTFS_DIR)/lib && tar xf - ); \
	fi
	($(STRIP) $(TOP_INSTALL_ROOTFS_DIR)/lib/*so*; true );
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/sbin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin
ifeq (x$(CONF_DIRECTFB),xy)
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc
endif
	if [ -f $(BIN_DIR)/config_tool ]; then \
		cp -fa $(BIN_DIR)/config_tool	$(TOP_INSTALL_ROOTFS_DIR)/sbin/; \
	fi
	cp -fa $(BIN_DIR)/dmaosd	$(TOP_INSTALL_ROOTFS_DIR)/bin/
	if [ -f $(BIN_DIR)/DMARender ]; then \
		cp -fa $(BIN_DIR)/DMARender	$(TOP_INSTALL_ROOTFS_DIR)/bin/;\
	fi
ifeq (x$(CONF_IPCAM_PLAYER),xy)
	(cd $(TOP_INSTALL_ROOTFS_DIR)/bin/; ln -s DMARender PICRender; ln -s DMARender AV2Render);
ifeq (x$(CONF_SINGLE_RENDERER),xy)
	(sed -i -e 's/cd \/bin/cd \/bin\nif [ -f \/tmp\/STOP_AV2RENDER ]; then\n\techo \"\/tmp\/STOP_AV2RENDER exists, AV2Render spawn stopped\";\nelse\n\texec MediaLogic AV2 MSGL_FATAL \&\n\texec #av2render.sh \&\nfi\n/' $(TOP_INSTALL_ROOTFS_DIR)/bin/run_all);
else
	(sed -i -e 's/cd \/bin/cd \/bin\nif [ -f \/tmp\/STOP_AV2RENDER ]; then\n\techo \"\/tmp\/STOP_AV2RENDER exists, AV2Render spawn stopped\";\nelse\n\texec MediaLogic AV2 MSGL_FATAL \&\n\texec av2render.sh \&\nfi\n/' $(TOP_INSTALL_ROOTFS_DIR)/bin/run_all);
endif
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/init ]; then sed -i -e 's/fw_reload_t3.sh/export LLAD_PARAMS=\"max_dmapool_memory_size=8388608\"\nfw_reload_t3.sh/' $(TOP_INSTALL_ROOTFS_DIR)/init; fi;)
else
	(cd $(TOP_INSTALL_ROOTFS_DIR)/bin/; ln -sf DMARender PICRender)
endif
	if [ -f $(BIN_DIR)/network_sync_daemon ]; then \
		cp -fa $(BIN_DIR)/network_sync_daemon	$(TOP_INSTALL_ROOTFS_DIR)/usr/sbin/;\
	fi
	if [ -f $(BIN_DIR)/MediaLogic ]; then \
		cp -fa $(BIN_DIR)/MediaLogic	$(TOP_INSTALL_ROOTFS_DIR)/bin/;\
	fi
	if [ -f $(BIN_DIR)/MediaLogic_PIC ]; then \
		cp -fa $(BIN_DIR)/MediaLogic_PIC	$(TOP_INSTALL_ROOTFS_DIR)/bin/;\
	fi
	if [ -f $(BIN_DIR)/network_daemon ]; then \
		cp -fa $(BIN_DIR)/network_daemon	$(TOP_INSTALL_ROOTFS_DIR)/usr/bin/;\
	fi
ifeq (x$(CONF_WIN7_WAKEONLAN),xy)
	cp -fa $(SYSLIB_PREFIX)/bin/wol $(TOP_INSTALL_ROOTFS_DIR)/usr/bin/
endif
	-ln -s /tmp/hostname $(TOP_INSTALL_ROOTFS_DIR)/etc/hostname
	-ln -s /tmp/passwd.conf $(TOP_INSTALL_ROOTFS_DIR)/etc/passwd
	-ln -s /tmp/shadow.conf $(TOP_INSTALL_ROOTFS_DIR)/etc/shadow
ifeq (x$(CONF_MULTI_PLAYER_CACHE),xy)
	if [ -f $(BIN_DIR)/memory_cache_server ]; then \
		cp -fa $(BIN_DIR)/memory_cache_server   $(TOP_INSTALL_ROOTFS_DIR)/bin/;\
	fi
endif
ifeq (x$(CONF_DMA_MS_JANUS_SIGMA),xy)
	cp -fa $(BIN_DIR)/get_lic  $(TOP_INSTALL_ROOTFS_DIR)/bin/
	cp -fa $(BIN_DIR)/get_lic_state  $(TOP_INSTALL_ROOTFS_DIR)/bin/
endif
ifeq (x$(CONF_CAS),xy)
	cp -fa $(BIN_DIR)/scan_manager	$(TOP_INSTALL_ROOTFS_DIR)/bin/
	cp -fa $(BIN_DIR)/scan_test	$(TOP_INSTALL_ROOTFS_DIR)/bin/
endif
ifeq (x$(CONF_DMA_RUN_SWF),xy)
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/swf
	cp -fra $(RESOURCE_SRC_DIR)/swf/* $(TOP_INSTALL_ROOTFS_DIR)/swf
endif

ifeq (x$(CONF_TRANSMISSION),xy)
	cp -fa $(SYSLIB_PREFIX)/bin/transmission* $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/share
	cp -fa $(SYSLIB_PREFIX)/share/transmission/web $(TOP_INSTALL_ROOTFS_DIR)/usr/share
	chmod a+x $(TOP_INSTALL_ROOTFS_DIR)/bin/bt*
endif
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/osd
###############################################################################################
#		install resource (font, image, mo, screenshot, wmdrm, xml)
###############################################################################################
	cp -fra $(RESOURCE_SRC_DIR)/font $(TOP_INSTALL_ROOTFS_DIR)/osd
	cp -fra $(RESOURCE_SRC_DIR)/image $(TOP_INSTALL_ROOTFS_DIR)/osd
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/osd/mo
	cp -fra $(RESOURCE_SRC_DIR)/mo/*.mo $(TOP_INSTALL_ROOTFS_DIR)/osd/mo
	cp -fra $(RESOURCE_SRC_DIR)/eula $(TOP_INSTALL_ROOTFS_DIR)/osd
ifeq (x$(CONF_THEME_ENABLED),xy)
	cp -fra $(RESOURCE_SRC_DIR)/screenshot $(TOP_INSTALL_ROOTFS_DIR)/osd
endif
ifeq (x$(CONF_DMA_MS_JANUS_SIGMA),xy)
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2),xy)
	cp -f $(RESOURCE_SRC_DIR)/x2_wmdrm/*.dat $(TOP_INSTALL_ROOTFS_DIR)/conf_src/	
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4),xy)
	cp -f $(RESOURCE_SRC_DIR)/t4_wmdrm/*.dat $(TOP_INSTALL_ROOTFS_DIR)/conf_src/	
endif
endif
	cp -fra $(RESOURCE_SRC_DIR)/xml/* $(TOP_INSTALL_ROOTFS_DIR)/osd

###############################################################################################
#		install extra resource (xml)
###############################################################################################
ifeq (x$(CONF_SUPPORT_EXTRA_RESOURCE), xy)
	cp -fra $(EXTRA_RESOURCE_SRC_DIR)/xml/* $(TOP_INSTALL_ROOTFS_DIR)/osd
	cp -fra $(EXTRA_RESOURCE_SRC_DIR)/image $(TOP_INSTALL_ROOTFS_DIR)/osd
endif


	if [ -f $(RESOURCE_SRC_DIR)/conf_src/config_factory_default ]; then \
		cp -fra $(RESOURCE_SRC_DIR)/conf_src/config_factory_default $(TOP_INSTALL_ROOTFS_DIR)/conf_src/ ; \
	fi
	find $(TOP_INSTALL_ROOTFS_DIR) -name .svn -exec rm -rf {} \; &> /dev/null; true
	echo $(CONF_VERSION) > ${TOP_INSTALL_ROOTFS_DIR}/conf_src/version
	echo "$(DATE)" > ${TOP_INSTALL_ROOTFS_DIR}/conf_src/date
	@if [ x$(CONF_PHOTO_BROWSE_DISPLAY_DEFAULT_IS_THUMBNAIL) == xy ]; then \
		(sed -i -e s/DMA_PHOTO_BROWSEMODE=\'[0-9]\'/DMA_PHOTO_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_PHOTO_BROWSEMODE=\'[0-9]\'/DMA_PHOTO_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_PHOTO_BROWSE_DISPLAY_DEFAULT_IS_LIST) == xy ]; then \
		(sed -i -e s/DMA_PHOTO_BROWSEMODE=\'[0-9]\'/DMA_PHOTO_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_PHOTO_BROWSEMODE=\'[0-9]\'/DMA_PHOTO_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_VIDEO_BROWSE_DISPLAY_DEFAULT_IS_THUMBNAIL) == xy ]; then \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_VIDEO_BROWSE_DISPLAY_DEFAULT_IS_LIST) == xy ]; then \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_VIDEO_BROWSE_DISPLAY_DEFAULT_IS_VIDEO) == xy ]; then \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'3\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_MOVIE_BROWSEMODE=\'[0-9]\'/DMA_MOVIE_BROWSEMODE=\'3\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_MUSIC_BROWSE_DISPLAY_DEFAULT_IS_THUMBNAIL) == xy ]; then \
		(sed -i -e s/DMA_MUSIC_BROWSEMODE=\'[0-9]\'/DMA_MUSIC_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_MUSIC_BROWSEMODE=\'[0-9]\'/DMA_MUSIC_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_MUSIC_BROWSE_DISPLAY_DEFAULT_IS_LIST) == xy ]; then \
		(sed -i -e s/DMA_MUSIC_BROWSEMODE=\'[0-9]\'/DMA_MUSIC_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_MUSIC_BROWSEMODE=\'[0-9]\'/DMA_MUSIC_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_BROWSE_DISPLAY_DEFAULT_IS_THUMBNAIL) == xy ]; then \
		(sed -i -e s/DMA_BROWSEMODE=\'[0-9]\'/DMA_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_BROWSEMODE=\'[0-9]\'/DMA_BROWSEMODE=\'1\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
	@if [ x$(CONF_BROWSE_DISPLAY_DEFAULT_IS_LIST) == xy ]; then \
		(sed -i -e s/DMA_BROWSEMODE=\'[0-9]\'/DMA_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);  \
		(sed -i -e s/DMA_BROWSEMODE=\'[0-9]\'/DMA_BROWSEMODE=\'0\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_for_mass_product);  \
	fi
		(sed -i -e s/DMA_SLIDESHOW=\'1\'/DMA_SLIDESHOW=\'$(CONF_SLIDESHOW_INTERVAL)\'/ $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default);
	(cd ${TOP_BUILD_ROOTFS_DIR}; mv ./etc/securetty ./etc/securetty.ori)
	(cd ${TOP_BUILD_ROOTFS_DIR}/etc; ln -sf /tmp/securetty.ori ./securetty)

ifeq (x$(CONF_SECURITY_PROPRIETARY_ENCRYPT),xy)
ifeq (x$(CONF_SECURITY_USE_JANUS_SHA1SUM),xy)	
	(cp $(TOP_MISC_DIR)/mount_script/init_1 $(TOP_INSTALL_ROOTFS_DIR)/bin);
	(sed -i -e 's/fw_reload_t3.sh/fw_reload_t3.sh\n\init_1/' $(TOP_INSTALL_ROOTFS_DIR)/init);
endif
ifeq (x$(CONF_SECURITY_USE_CPU_KEY_SHA1SUM),xy)	
	(cp $(TOP_MISC_DIR)/mount_script/init_2 $(TOP_INSTALL_ROOTFS_DIR)/bin);
	(sed -i -e 's/fw_reload_t3.sh/fw_reload_t3.sh\n\init_2/' $(TOP_INSTALL_ROOTFS_DIR)/init);
endif
ifeq (x$(CONF_SECURITY_USE_IPTOKEN_SHA1SUM),xy)	
	(cp $(TOP_MISC_DIR)/mount_script/init_3 $(TOP_INSTALL_ROOTFS_DIR)/bin);
	(sed -i -e 's/fw_reload_t3.sh/fw_reload_t3.sh\n\init_3/' $(TOP_INSTALL_ROOTFS_DIR)/init);
endif
endif

ifeq (x$(CONF_CONSOLE_SECURE),xy)
	(sed -i -e 's/cp \/etc\/shadow.conf \/tmp -f/cp \/etc\/shadow.conf \/tmp -f\n\n\gbus_read_serial_num\n/' $(TOP_INSTALL_ROOTFS_DIR)/init);
	(sed -i -e 's/\t\/bin\/sh/\/sbin\/getty -L ttyS0 115200 vt100/' $(TOP_INSTALL_ROOTFS_DIR)/init);
endif

ifeq (x$(CONF_PLATFORM_X86),xy)
	mkdir -p ${TOP_BUILD_ROOTFS_DIR}/$(CONF_SETTING_CONFIG_FILE_DIR)
	cp -f ${TOP_BUILD_ROOTFS_DIR}/$(CONF_SETTING_ORIGINAL_CONFIG_FILE_DIR)/$(CONF_SETTING_FACTORY_SETTINGS) ${TOP_BUILD_ROOTFS_DIR}/$(CONF_SETTING_CONFIG_FILE_DIR)/$(CONF_SETTING_CONFIG_FILE_NAME)
endif
ifneq (x$(CONF_TWONKYMEDIA_SERVER_SUPPORT), xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/init ]; then sed -i s,/bin/run_twonky_server,\#/bin/run_twonky_server, $(TOP_INSTALL_ROOTFS_DIR)/init; fi;)
endif
ifeq (x$(CONF_TWONKYMEDIA_SERVER_SUPPORT), xy)
	#TMS5.1 ignore to scan /tmp folder so I create mediaitems to / and link to /tmp/media/usb to workaround this issue.
	ln -sf /tmp/media/usb $(TOP_INSTALL_ROOTFS_DIR)/mediaitems
endif	
ifeq (x$(CONF_TWONKYMEDIA_SERVER_6_0_34_SMP8654), xy)
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/var/twonkymedia
	ln -sf /tmp/twonkymedia $(TOP_INSTALL_ROOTFS_DIR)/var/twonkymedia/twonkymedia
endif
ifeq (x$(CONF_MULTI_PLAYER_CACHE),xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/init ]; then sed -i s,\#/bin/memory_cache_server,/bin/memory_cache_server, $(TOP_INSTALL_ROOTFS_DIR)/init; fi;)
endif

ifeq (x$(CONF_PRODUCT_EXT_WDTV_VILLA), xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_NAME="'My Media Player'",DMA_NAME="'WDTV'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
endif
ifeq (x$(CONF_SAMBA_VERSION_3_5_1), xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/bin/run_samba ]; then sed -i s,"exec smbd -D --configfile=/tmp/smb.conf --piddir=/tmp --private-dir=/tmp/private --lockdir=/tmp/ --smb-passwd-file=/tmp/private/smbpasswd","exec smbd -D --configfile=/tmp/smb.conf --piddir=/tmp --private-dir=/tmp/private --lockdir=/tmp/ --smb-passwd-file=/tmp/private/smbpasswd --statedir=/tmp --cachedir=/tmp", $(TOP_INSTALL_ROOTFS_DIR)/bin/run_samba; fi;)
endif
ifeq (x$(CONF_PRODUCT_EXT_LMP555), xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,VIDEO_OUT="'COMPOSITE'",VIDEO_OUT="'HDMI'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,VIDEO_OUT_RESOLUTION="'480i'",VIDEO_OUT_RESOLUTION="'auto'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_CONTENT_AGGREGATION="'1'",DMA_CONTENT_AGGREGATION="'0'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_ENABLE_AUTO_STANDBY="'0'",DMA_ENABLE_AUTO_STANDBY="'20'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_BROWSEMODE="'1'",DMA_BROWSEMODE="'0'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,PICFIT="'0'",PICFIT="'1'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,PHOTO_SLIDESHOW_EFFECT="'0'",PHOTO_SLIDESHOW_EFFECT="'1'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_SLIDESHOW="'3'",DMA_SLIDESHOW="'5'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,SUBTITLE_FONT_SIZE="'40'",SUBTITLE_FONT_SIZE="'36'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,ENABLE_AUTO_LOGIN="'0'",ENABLE_AUTO_LOGIN="'1'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,DMA_VOLUME="'80'",DMA_VOLUME=\'$(CONF_DEFAULT_VOLUME)\', $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
endif
ifeq (x$(CONF_SINGLE_RENDERER),xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/bin/run_all ]; then sed -i 's:exec picrender.sh:\#exec picrender.sh:' $(TOP_INSTALL_ROOTFS_DIR)/bin/run_all; fi;)
endif
ifeq (x$(CONF_PRODUCT_EXT_WDTV_RV), xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,ENABLE_TRANSFER_SYNC="'0'",ENABLE_TRANSFER_SYNC="'1'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	cp -raf $(ROOTFS_SRC_DIR)/RV/* $(TOP_INSTALL_ROOTFS_DIR) 
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM),xy)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,ENABLE_TRANSFER_SYNC="'0'",ENABLE_TRANSFER_SYNC="'1'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,PHOTO_SLIDESHOW_EFFECT="'0'",PHOTO_SLIDESHOW_EFFECT="'3'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,VIDEO_OUT="'COMPOSITE'",VIDEO_OUT="'HDMI'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
	(if [ -f $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default ]; then sed -i s,VIDEO_OUT_RESOLUTION="'480i'",VIDEO_OUT_RESOLUTION="'auto'", $(TOP_INSTALL_ROOTFS_DIR)//conf_src/config_factory_default; fi;)
endif
ifeq (x$(CONF_QT_SPLIT_LIBQTWEBKIT),xy)
	rm -f $(TOP_INSTALL_ROOTFS_DIR)/lib/libQtWebKit.so
	rm -f $(TOP_INSTALL_ROOTFS_DIR)/lib/libQtWebKit.so.4
	rm -f $(TOP_INSTALL_ROOTFS_DIR)/lib/libQtWebKit.so.4.5
	(cd $(TOP_INSTALL_ROOTFS_DIR)/lib/; ln -s /tmp/qt/libQtWebKit.so.4.5.0 libQtWebKit.so;ln -s /tmp/qt/libQtWebKit.so.4.5.0 libQtWebKit.so.4; ln -s /tmp/qt/libQtWebKit.so.4.5.0 libQtWebKit.so.4.5)
	(cd $(TOP_INSTALL_ROOTFS_DIR)/lib/;dd if=libQtWebKit.so.4.5.0 of=libQtWebKit.so.4.5.0.p1 bs=1M count=8; dd if=libQtWebKit.so.4.5.0 of=libQtWebKit.so.4.5.0.p2 bs=1M skip=8)
	rm -f $(TOP_INSTALL_ROOTFS_DIR)/lib/libQtWebKit.so.4.5.0
	sed -i "2i mkdir /tmp/qt" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "3i cp /lib/libQtWebKit.so.4.5.0.p1 /tmp/qt/libQtWebKit.so.4.5.0" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "4i cat /lib/libQtWebKit.so.4.5.0.p2 >> /tmp/qt/libQtWebKit.so.4.5.0" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "5i export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:/tmp/qt" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "6i export QT_INSTALL_DIR=/opt/qt/" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "7i export LD_LIBRARY_PATH=\$$QT_INSTALL_DIR/lib:\$$QT_INSTALL_DIR/plugins/imageformats:\$$QT_INSTALL_DIR/plugins/gfxdrivers:\$$LD_LIBRARY_PATH" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "8i export QT_PLUGIN_PATH=/opt/qt/plugins" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "9i export set QT_QWS_FONTDIR=/opt/qt/fonts/" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
	sed -i "10i export set QT_QWS_FONTDIR=/opt/qt/fonts/" $(TOP_INSTALL_ROOTFS_DIR)/bin/dmaosd.sh
endif
ifeq (x$(CONF_ESPIAL_BROWSER),xy)
	ln -sf /usr/applications/EspialTVBrowser/bin/HtmlUI $(TOP_INSTALL_ROOTFS_DIR)/osd/HtmlUI
	ln -sf /usr/applications/EspialTVBrowser/bin/plugins $(TOP_INSTALL_ROOTFS_DIR)/osd/plugins
endif
	(echo "FORCE_FIRMWARE_UPGRADE='0'" >> $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default)
	(echo "USB_FORCE_FIRMWARE_UPGRADE='0'" >> $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default)
	(echo "FLASH_PLUGIN_SUPPORT='y'" >> $(TOP_INSTALL_ROOTFS_DIR)/conf_src/config_factory_default)
	@echo -en "\n\\033[0;33m Striping binary executable (Please keep this in the last)\\033[0m\n"
	find $(TOP_BUILD_ROOTFS_DIR) -type f -exec file {} \; | grep -v "\.ko" | grep "not\ stripped" | awk -F ":" '{ print $$1 }' | xargs $(STRIP) 
	(cd ${TOP_BUILD_ROOTFS_DIR}; find . -type f -exec md5sum {} \; > /tmp/md5sum.txt.`whoami` )
	cp -f /tmp/md5sum.txt.`whoami` ${TOP_BUILD_ROOTFS_DIR}/md5sum.txt

