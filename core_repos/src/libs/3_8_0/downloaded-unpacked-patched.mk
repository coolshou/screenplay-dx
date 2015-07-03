TOP        := $(shell pwd)/../..#
include $(TOP)/Target.mk

SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#
BOOT_LOADER_DIR	      := $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_BOOT_LOADER)/#
TOOLCHAIN_SVERVER_URL	:= $(TOP_LIBS_URL)/toolchains/$(CONF_SIGMA_XMBOOT_TOOLCHAIN_PACKAGE)

kernel_src_2_6_22_19_dir       := linux-2.6.22.19

patch_dir := linux_kernel_${CONF_LINUX_KERNEL_VERSION}-${CONF_LINUX_PATCH_VERSION}_patch

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_ORIGINAL_KERNEL_PATCH), xy)
patch_list_2_6_22_19 :=  \
    0000.shared.patch \
    1000.tangox.patch \
    1001.zbf.patch \
    1002.pcidma.patch \
    1003.gpio.patch \
    1004.mbus.patch \
    1005.ide.patch \
    1006.enet.patch \
    1007.usb.patch \
    1008.mtd.patch \
    1009.udf.patch \
    1010.ipfilter.patch \
    1011.ir.patch \
    1012.fip.patch \
    1013.scard.patch \
    1014.fb.patch \
    1015.multirecv.patch \
    1016.watchdog.patch \
    1017.rootfs.patch \
    1018.sata.patch \
    1019.uir.patch \
    1020.freqctrl.patch \
    1021.ck1.patch \
    1022.oprofile.patch \
    1023.codesourcery.patch \
    1024.unaligned.patch \
    1025.testdisplay.patch \
    1026.gcc43x.patch \
    1027.tango3otg.patch \
    1033.gcc44x.patch
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2_ORIGINAL_KERNEL_PATCH), xy)
patch_list_2_6_22_19 :=  \
    0000.shared.patch \
    1000.tangox.patch \
    1001.zbf.patch \
    1002.pcidma.patch \
    1003.gpio.patch \
    1004.mbus.patch \
    1005.ide.patch \
    1006.enet.patch \
    1007.usb.patch \
    1008.mtd.patch \
    1009.udf.patch \
    1010.ipfilter.patch \
    1011.ir.patch \
    1012.fip.patch \
    1013.scard.patch \
    1014.fb.patch \
    1015.multirecv.patch \
    1016.watchdog.patch \
    1017.rootfs.patch \
    1018.sata.patch \
    1019.uir.patch \
    1020.freqctrl.patch \
    1022.oprofile.patch \
    1024.unaligned.patch \
    1025.testdisplay.patch \
    1026.gcc43x.patch \
    1027.tango3otg.patch \
    1031.mixdram.patch \
    1033.gcc44x.patch \
    1034.pref.memset.memcpy.10799.patch \
    1035.dtcpip.patch \
    1036.sdio.patch \
    1037.libertas.patch \
    1038.virtualinput.patch \
    1039.directfb-fusion.patch
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7_ORIGINAL_KERNEL_PATCH), xy)
patch_list_2_6_22_19 :=  \
    0000.shared.patch \
    1000.tangox.patch \
    1001.zbf.patch \
    1002.pcidma.patch \
    1003.gpio.patch \
    1004.mbus.patch \
    1005.ide.patch \
    1006.enet.patch \
    1007.usb.patch \
    1008.mtd.patch \
    1009.udf.patch \
    1010.ipfilter.patch \
    1011.ir.patch \
    1012.fip.patch \
    1013.scard.patch \
    1014.fb.patch \
    1015.multirecv.patch \
    1016.watchdog.patch \
    1017.rootfs.patch \
    1018.sata.patch \
    1019.uir.patch \
    1020.freqctrl.patch \
    1022.oprofile.patch \
    1024.unaligned.patch \
    1025.testdisplay.patch \
    1026.gcc43x.patch \
    1027.tango3otg.patch \
    1031.mixdram.patch \
    1033.gcc44x.patch \
    1034.pref.memset.memcpy.10799.patch \
    1035.dtcpip.patch \
    1036.sdio.patch \
    1037.libertas.patch \
    1039.directfb-fusion.patch \
    1041.zxenv.patch \
    2000.msdos-partition.patch \
    2100.efi-partition.patch \
    2200.mac-partition.patch
endif

patch_list_2_6_22_19_4TB :=  \
    0000.shared.patch \
    1000.tangox.patch \
    1001.zbf.patch \
    1002.pcidma.patch \
    1003.gpio.patch \
    1004.mbus.patch \
    1005.ide.patch \
    1006.enet.patch \
    1007.usb.patch \
    1008.mtd.patch \
    1009.udf.patch \
    1010.ipfilter.patch \
    1011.ir.patch \
    1012.fip.patch \
    1013.scard.patch \
    1014.fb.patch \
    1015.multirecv.patch \
    1016.watchdog.patch \
    1017.rootfs.patch \
    1018.sata.patch \
    1019.uir.patch \
    1020.freqctrl.patch \
    1021.ck1.patch \
    1022.oprofile.patch \
    1023.codesourcery.patch \
    1024.unaligned.patch \
    1025.testdisplay.patch \
    1026.gcc43x.patch \
    1027.tango3otg.patch \
    1031.mixdram.patch \
    1033.gcc44x.patch \
    1034.pref.memset.memcpy.10799.patch

patch_executed_list_2_6_22_19 := $(patch_list_2_6_22_19:%=$(kernel_src_2_6_22_19_dir)/README.%)

patch_executed_list_2_6_22_19_4TB := $(patch_list_2_6_22_19_4TB:%=$(kernel_src_2_6_22_19_dir)/README.%)

.PHONY: sigma_zboot-unpack

sigma_zboot-unpack:

.PHONY: sigma_zboot-patch

sigma_zboot-patch:

.PHONY: linux_kernel-unpack
linux_kernel-unpack:
	(cd $(SIGMA_SDK_SOURCE); ln -s linux_kernel_$(CONF_LINUX_KERNEL_VERSION) $(kernel_src_2_6_22_19_dir))


.PHONY: linux_kernel-patched
linux_kernel-patched: $(patch_executed_list_2_6_22_19) $(patch_executed_list_2_6_22_19_4TB) linux_kernel_patch_proprietary
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_ORIGINAL_KERNEL_PATCH), xy)
	@echo "patch_executed_list_2_6_22_19 finish"
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_4TB_KERNEL_PATCH), xy)
	@echo "patch_executed_list_2_6_22_19_4TB finish"
endif
	@echo "linux_kernel-patched"

.PHONY: linux_kernel_patch_proprietary
linux_kernel_patch_proprietary:
	@if [ -s $(patch_dir)/kernel.panic_restart.patch ]; then \
		cd $(SIGMA_SDK_SOURCE)/$(kernel_src_2_6_22_19_dir) && \
		patch -p0 < $(patch_dir)/kernel.panic_restart.patch; \
	fi

$(patch_executed_list_2_6_22_19):
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_ORIGINAL_KERNEL_PATCH), xy)
	(cd  $(SIGMA_SDK_SOURCE)/;patch -d $(@D) -p1 < $(patch_dir)/$(@D)/$(subst README.,,$(@F)) )
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2_ORIGINAL_KERNEL_PATCH), xy)
	(cd  $(SIGMA_SDK_SOURCE)/;patch -d $(@D) -p1 < $(patch_dir)/$(@D)/$(subst README.,,$(@F)) )
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7_ORIGINAL_KERNEL_PATCH), xy)
	(cd  $(SIGMA_SDK_SOURCE)/;patch -d $(@D) -p1 < $(patch_dir)/$(@D)/$(subst README.,,$(@F)) )
endif

$(patch_executed_list_2_6_22_19_4TB):
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_4TB_KERNEL_PATCH), xy)
	(cd  $(SIGMA_SDK_SOURCE)/;patch -d $(@D) -p1 < $(patch_dir)/$(@D)_4TB/$(subst README.,,$(@F)) )
endif

.PHONY: sigma_driver-patched
sigma_driver-patched:

.PHONY: sigma_sdk-patched

sigma_sdk-patched: $(SIGMA_SDK_DIR)/.sigma_sdk_patched

$(SIGMA_SDK_DIR)/.sigma_sdk_patched: 
	# Patching...

.PHONY: sigma_isdk-patched
sigma_isdk-patched:
	# Patching...
