#
# Defines
#
ifndef  CONF_SIGMA_SDK_VERSION 
CONF_SIGMA_SDK_VERSION := 3.7.0# 
endif

SIGMA_SDK_SERVER_URL  		:= $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_DIR         		:= $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      		:= $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
DCCHD				:= dcchd-$(CONF_SIGMA_SDK_VERSION)#
DCCHD_SOURCE   		:= $(SIGMA_SDK_SOURCE)/DCCHD/dcchd_${CONF_DCCHD_VERSION}#
DCCHD_SOURCE_PACKAGE	:= $(DCCHD_SOURCE).tgz#
DIRECTFB_PORTING_SOURCE	:= $(SIGMA_SDK_SOURCE)/DCCHD/dcchd_$(CONF_DIRECTFB_PORTING_VERSION)#
DIRECTFB_PORTING_SOURCE_PACKAGE	:= $(DIRECTFB_PORTING_SOURCE).tgz#
DCCHD_MMAP_CONFIG 		:= $(SIGMA_SDK_SOURCE)/DCCHD/patch/$(CONF_DCCHD_MMAP_CONFIG_FILE)
RUA_DIR := $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)/MRUA_src

#
# Download  the source 
#
.PHONY: dcchd-downloaded
dcchd-downloaded:

#
# Unpack the source
#
.PHONY: dcchd-unpacked

dcchd-unpacked: $(SIGMA_SDK_DIR)/.dcchd_unpacked

$(SIGMA_SDK_DIR)/.dcchd_unpacked:
	@echo "Unpacking dcchd..." 
	@rm -fr $(DCCHD_SOURCE)
	cd $(SIGMA_SDK_SOURCE)/DCCHD; tar xzf ${DCCHD_SOURCE_PACKAGE};
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cd $(SIGMA_SDK_SOURCE)/DCCHD; tar xzvf $(DIRECTFB_PORTING_SOURCE_PACKAGE);
	rm -rf $(DCCHD_SOURCE)/directfb;
	cp -avR $(DIRECTFB_PORTING_SOURCE)/directfb $(DCCHD_SOURCE)/;
endif
	@touch $@


#
# Patch the source
#
.PHONY: dcchd-patched

dcchd-patched: $(SIGMA_SDK_DIR)/.dcchd_patched

$(SIGMA_SDK_DIR)/.dcchd_patched: $(SIGMA_SDK_DIR)/.dcchd_unpacked
	@echo "Patch dcchd..." 
ifeq (x$(CONF_REMOTE_IOM_WITH_KEYBOARD), xy)
	cp -f $(DCCHD_SOURCE)/../patch/directfb_keynames.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/smp863x/include/
	cp -f $(DCCHD_SOURCE)/../patch/directfb_keynames.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/include/
	cp -f $(DCCHD_SOURCE)/../patch/directfb_keyboard.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/include/
	patch $(DCCHD_SOURCE)/../patch/alpha_ir_map.h -p0 < $(DCCHD_SOURCE)/../patch/alpha_ir_map_iom_remote_keyboard.patch	
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0), xy)
	cp -rf $(SIGMA_SDK_SOURCE)/DCCHD/lib/*.so $(SIGMA_SDK_SOURCE)/$(SIGMA_RUA_SDK)/lib/
	cd $(DCCHD_SOURCE);patch -p0 < ../$(DCCHD).patch
	cp $(DCCHD_MMAP_CONFIG) $(DCCHD_SOURCE)/dcchd/config/default/dcchd_config.h
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_0), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_0.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp $(DCCHD_MMAP_CONFIG) $(DCCHD_SOURCE)/dcchd/config/default/dcchd_config.h
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
endif
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_1), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_1.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp $(DCCHD_SOURCE)/dcchd/config/single_bank/dcchd_config.h $(DCCHD_SOURCE)/dcchd/config/default/dcchd_config.h
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
endif
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_2.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
endif
ifeq (x$(CONF_DCCHD_VERSION), xSMP8654_3_8_2_aqua.mips)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/memory_config_path.patch
endif
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_libsample1_audio-3_8_2.patch
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_3), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_3.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
	cd $(DCCHD_SOURCE)/;patch -p0 < ../patch/dcchd_fix_LG_TV_audio.patch
endif
ifeq (x$(CONF_DCCHD_FIX_HDMI_SPD_TO_WDTV), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_HDMI_SPD_to_WDTV.patch
endif
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/memory_config_path.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_libsample1_audio-3_8_2.patch
	cd $(DCCHD_SOURCE)/dcchd;patch -p0 < ../../patch/dcchd_fix_SPDIF_bitstream_issue.patch
ifeq (x$(CONF_DCCHD_FIX_USB_HOTPLUG_CRASH), xy)
	cp $(DCCHD_SOURCE)/../patch/librmdvdfs.so $(DCCHD_SOURCE)/dcchd/curacao/lib/librmdvdfs.so
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_5), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_3.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/memory_config_path_for_single_bank.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
endif
ifeq (x$(CONF_DCCHD_FIX_HDMI_SPD_WORDS), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_HDMI_SPD_Words.patch
endif
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_libsample1_audio-3_8_4.patch
	cd $(DCCHD_SOURCE)/dcchd;patch -p0 < ../../patch/dcchd_fix_SPDIF_bitstream_issue.patch
#	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_SDK_385rc1.patch
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_7.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/memory_config_path_for_single_bank.patch
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
ifeq (x$(CONF_USE_DIRECTFB_PORTING_SOURCECODE), xy)
	cp $(DCCHD_SOURCE)/../patch/linux_input.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/linux_input/
endif
ifeq (x$(CONF_DCCHD_FIX_HDMI_SPD_WORDS), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_HDMI_SPD_Words.patch
endif
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_libsample1_audio-3_8_4.patch
	cd $(DCCHD_SOURCE)/dcchd;patch -p0 < ../../patch/dcchd_fix_SPDIF_bitstream_issue.patch
#	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_SDK_385rc1.patch
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_8), xy)
ifeq (x$(CONF_DMA_VUDU), xy)
	cd $(DCCHD_SOURCE)/../patch;patch -p0 < em86remote_sigmarc.c.patch
endif
	cp -rf $(DCCHD_SOURCE)/../patch/em86remote_sigmarc.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cp -rf $(DCCHD_SOURCE)/../patch/alpha_ir_map.h $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/inputdrivers/em86_input/
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd-3_8_3.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/using_sw_jpeg.patch
ifeq (x$(CONF_3_8_0_NEW_MMAP), xy)
else ifeq (x$(CONF_MMAP_DOUBLE_TO_SINGLE), xy)
	cd $(DCCHD_SOURCE); sed -i -e "s/RMCFLAGS=\"-I\$$DCCHD_CFG_DIR \"/RMCFLAGS=\"-I\$$DCCHD_CFG_DIR -DMMAP_DRAM0_SIZE=130 \"/" DCCHD.flags.env;
	cd $(DCCHD_SOURCE); sed -i -e "s/config\/hd1/config\/single_bank/" DCCHD.flags.env;
else
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/memory_config_path_for_single_bank.patch
endif
#	cd $(DCCHD_SOURCE);patch -p0 < ../patch/HDMI_passthru_disable_data_pads.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_libsample1_audio-3_8_5.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_SPDIF_bitstream_issue_388rc4.patch
#	cd $(DCCHD_SOURCE);patch -p0 < ../patch/30802.patch
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/no_analog_no_spdif.patch
#	cd $(DCCHD_SOURCE);patch -p0 -R < ../patch/31008.patch
endif



ifeq (x$(CONF_DCCHD_FIX_HDMI_NOT_SYNC), xy)
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_8), xy)
else
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/set_pixel_clock_dcchd.patch
endif
endif
ifeq (x$(CONF_DIRECTFB_HDMI_FIX), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/em86xx_internals.patch
endif

ifeq (x$(CONF_DIRECTFB_FIX_COLOR_SPACE), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_color_space.patch
endif
ifeq (x$(CONF_DIRECTFB_FIX_CRASH_IN_INVALID_ISO), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_read_invalid_iso.patch
endif
ifeq (x$(CONF_DIRECTFB_HDMI_FIX_COLOR_DEPTH_SWITCHING), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_deep_color_switching.patch
endif
ifeq (x$(CONF_DIRECTFB_HDMI_FIX_1080P24_SWITCHING), xy)
	cd $(DCCHD_SOURCE);patch -p0 < ../patch/dcchd_fix_1080p24_switch.patch
endif
ifeq (x$(CONF_DIRECTFB_OVERWRITE_SIMGA_PNG_PATCH), xy)
	cp -rf $(DCCHD_SOURCE)/../patch/idirectfbimageprovider_png.c $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/interfaces/IDirectFBImageProvider/
endif
ifeq (x$(CONF_SIGMA_NETFLIX_PATCH_REDUCE_CPU_USAGE),xy)
ifeq (x$(CONF_DMA_NETFLIX),xy)
ifneq (x$(CONF_NETFLIX_3_0),xy)
	cd $(DCCHD_SOURCE);patch -p1 < ../patch/30052.patch
endif
endif
endif
	sed -i -e "s/DATADIR/\"\/osd\/image\" /" $(DCCHD_SOURCE)/directfb/install/dfb-smp86xx/src/core/windowstack.c
	echo "Patching $@ done"
	@touch $@
#
# Compile
#
.PHONY: dcchd-compile

dcchd-compile: $(SIGMA_SDK_DIR)/.dcchd_compiled

$(SIGMA_SDK_DIR)/.dcchd_compiled: $(SIGMA_SDK_DIR)/.dcchd_patched
	@echo "Compiling dcchd..."
	(export LINKER=g++;export PATH=$(CONF_CROSS_PREFIX)/bin:$(PATH);export SMP86XX_TOOLCHAIN_PATH=$(CONF_CROSS_PREFIX);cd $(SIGMA_SDK_SOURCE)/${CONF_SIGMA_SDK_CPU_KEY}/;. ./CPU_KEYS.env;cd $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK);. ./build.env;export RMCFLAGS="$(RMCFLAGS) -I$(SYSLIB_PREFIX)/include/freetype2 -I$(SYSLIB_PREFIX)/include";rm -rf $(SYSLIB_PREFIX)/cross_rootfs/lib;ln -s $(SYSLIB_PREFIX)/lib $(SYSLIB_PREFIX)/cross_rootfs;export SMP86XX_ROOTFS_PATH="$(SYSLIB_PREFIX)";export SMP86XX_ROOTFS_PATH=$(LIBS_INSTALL_PATH);export COMPILKIND='codesourcery hardfloat glibc debug'; export UCLINUX_KERNEL=$(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/;cd $(DCCHD_SOURCE)/;. ./DCCHD.env;make clean && make &&make install)
	(cd $(DCCHD_SOURCE)/; find . -name *.so -exec cp -a {} $(LIBS_INSTALL_PATH)/lib/ \;)
	(cd $(DCCHD_SOURCE)/; find . -name *.so.0 -exec cp -a {} $(LIBS_INSTALL_PATH)/lib/ \;)
	(cd $(DCCHD_SOURCE)/; find . -name *.so.0.0 -exec cp -a {} $(LIBS_INSTALL_PATH)/lib/ \;)
	cp -Rdf $(DCCHD_SOURCE)/directfb/include/*  $(LIBS_INSTALL_PATH)/include/.
	cp -fa $(DCCHD_SOURCE)/directfb/bin/df_fire $(SYSLIB_PREFIX)/bin/
	cp -fa $(DCCHD_SOURCE)/directfb/bin/df_window $(SYSLIB_PREFIX)/bin/
	mkdir -p $(LIBS_INSTALL_PATH)/include/dcchd
	mkdir -p $(LIBS_INSTALL_PATH)/include/dcchd/rmcci/include/
	mkdir -p $(LIBS_INSTALL_PATH)/include/dcchd/rmdvdtypes
	cp -fa $(DCCHD_SOURCE)/dcchd/core/*defs.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/core/cdefs_av.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/core/globals.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/config/single_bank/dcchd_config.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/core/globals.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/core/dcchd.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/config/default/drm_config.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/mono/cdefs_lpb.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/curacao/cdefs_dvd.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/curacao/cdefs_cdda.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/curacao/cdefs_vcd.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/curacao/rmdvdtypes/dvdtypes.h $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/curacao/rmdvdtypes/dvdtypes.h $(LIBS_INSTALL_PATH)/include/dcchd/rmdvdtypes/
	cp -fa $(DCCHD_SOURCE)/dcchd/dvdvr/cdefs_vr.h  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/dvdvr/mdefs_vr.h  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/brd/cdefs_b*  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/brd/mdefs_b*  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/brd/bd_common.h  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/dtv/cdefs_*  $(LIBS_INSTALL_PATH)/include/dcchd
	cp -fa $(DCCHD_SOURCE)/dcchd/dtv/dtvdbg.h  $(LIBS_INSTALL_PATH)/include/dcchd
	touch $@

#
# Update
#
.PHONY: dcchd-update

dcchd-update:

#
# Status
#
.PHONY: dcchd-status

dcchd-status:

#
# Clean
#
.PHONY: dcchd-clean

dcchd-clean:
	@rm -f .dcchd_configured
	@make -C $(DCCHD_SOURCE) clean   
	rm -f $(SIGMA_SDK_DIR)/.dcchd_compiled
	

#
# Dist clean
#
.PHONY: dcchd-distclean

dcchd-distclean:

#
# Install
#
.PHONY: dcchd-install

dcchd-install:
	(cd $(DCCHD_SOURCE)/; find . -name *.so -exec cp -a {} $(TOP_INSTALL_ROOTFS_DIR)/lib/ \; ;cp test/amp_test $(TOP_INSTALL_ROOTFS_DIR)/bin/;cp -Rdf directfb $(TOP_INSTALL_ROOTFS_DIR)/;cd $(TOP_INSTALL_ROOTFS_DIR)/directfb/;rm -rf install bin; find . -name *.c -exec rm -rf {} \; ;find . -name *.h -exec rm -rf {} \; ;find . -name *.d -exec rm -rf {} \; ;find . -name *.o -exec rm -rf {} \;)
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/bin/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/opt/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/opt/qt/
	cp -Rdf $(DCCHD_SOURCE)/directfb/share/directfb-examples/fonts $(TOP_INSTALL_ROOTFS_DIR)/opt/qt/
	cp -f $(SIGMA_SDK_SOURCE)/DCCHD/run_dcchd $(TOP_INSTALL_ROOTFS_DIR)/bin/
	cp -rf $(SIGMA_SDK_SOURCE)/DCCHD/directfbrc $(TOP_INSTALL_ROOTFS_DIR)/etc/
	cp -rf $(SIGMA_SDK_SOURCE)/DCCHD/sigmadfbrc $(TOP_INSTALL_ROOTFS_DIR)/etc/
	cp -rf $(SIGMA_SDK_SOURCE)/$(SIGMA_RUA_SDK)/lib/* $(TOP_INSTALL_ROOTFS_DIR)/lib/
ifeq (x$(CONF_DMA_HDCP_ALWAYS_ON), xy)
	echo "hdcp-always-on" >> $(TOP_INSTALL_ROOTFS_DIR)/etc/sigmadfbrc
endif
