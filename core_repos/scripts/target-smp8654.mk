##############################################################################
# This file contails 4 parts: 
#     platform, OS,  compiler, additonal SDK 
##############################################################################

ifndef TARGET_SMP8634_MK_INCLUDED

TARGET_SMP8634_MK_INCLUDED := 1

CFLAGS := -Wall 

############################## OS section ####################################

CFLAGS += -D_POSIX  -D_UNIX -DLINUX -DUNIX 

############################## platform section ##############################

ARCH            := mipsel
ENABLE_SHLIB    := yes
CFLAGS += -D__MIPSEL__ -D__EM86XX__

CROSS_BIN                  := $(CONF_CROSS_BIN)
CROSS                      := $(CONF_CROSS)
CROSS_PREFIX               := $(CONF_CROSS_PREFIX)


CONF_SIGMA_CHIP_NO = SMP8654
CONF_LINUX_KERNEL_VERSION=2.6.22.19
CONF_LINUX_PATCH_VERSION=12

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0_ORIGINAL_KERNEL_PATCH),xy)
CONF_LINUX_PATCH_VERSION=19
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2_ORIGINAL_KERNEL_PATCH),xy)
CONF_LINUX_PATCH_VERSION=29
endif

ifeq (x$(CONF_LINUX_KERNEL_VERSION_2_6_22_19_36_IOM),xy)
CONF_LINUX_PATCH_VERSION=36
CONF_LINUX_KERNEL_CONFIG_FILE=linux_kernel_2.6.22.19-36_IOM_pagesize16kb
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_5_0), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654_3_5_0_dev.mips
#CONF_SIGMA_RUA_FW = mruafw_SMP8654_3_5_0_facsprod.mips.nodts
CONF_SIGMA_RUA_FW = mruafw_SMP8654_3_5_0_prod.mips.nodts
SIGMA_SDK_VERSION=3_5_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-7
CFLAGS += -mips32r2 -Wa,-mips32r2
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_6_0_rc11), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_6_0_rc_14_BC_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_6_0_rc_14
SIGMA_SDK_VERSION=3_6_0_rc11
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-7
CFLAGS += -mips32r2 -Wa,-mips32r2
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_6_0), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_6_0_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_6_0
SIGMA_SDK_VERSION=3_6_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-7
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_6_1_rc2), xy)
ifeq (x$(CONF_DTS_CHIP_SET), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_6_1_rc_4_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_DTS_prod_3_6_1_rc_4
else
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_6_1_rc_4_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_6_1_rc_4
endif
SIGMA_SDK_VERSION=3_6_1_rc2
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-7
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_7_0_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_7_0
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_1_RC3_BASE_ON_3_7_0), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_7_1_rc_3_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_7_1_rc_5
endif
SIGMA_SDK_VERSION=3_7_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
ifeq (x$(CONF_SIGMA_EZBOOT_0X82_NAND_FLASH_DRIVER), xy)
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy)
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x98
endif
ifeq (x$(CONF_SIGMA_YAMON_R2_13_17_NAND_FLASH_DRIVER), xy)
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
endif
ifeq (x$(CONF_SIGMA_YAMON_R2_13_24_NAND_FLASH_DRIVER), xy)
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-24
endif
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_0), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_0_rc_3_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_0_rc_3
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x82
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_1), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_1_rc_1_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_1_rc_1
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x98
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_2_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_2
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x98
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_3), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_3_rc_3_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_3_rc_3
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x98
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_5), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_5_rc_2_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_5_rc_2
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_5_rc_2.mips
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0x98
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-17
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7), xy)
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_7_rc_1_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_7_rc_1
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_7_rc_0.mips
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0xaa
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-31
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_8), xy)
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_SUBVERSION_rc_16), xy)
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_8_rc_16-1.mips
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_8_rc_16_janus_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_8_rc_16
else
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_SUBVERSION_rc_15), xy)
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_8_rc_15-1.mips
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_8_rc_15-janus_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_8_rc_15
else
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_SUBVERSION_rc_11), xy)
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_8_rc_11.mips
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_8_rc_11_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_8_rc_11
else
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_SUBVERSION_rc_6), xy)
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_8_rc_6.mips
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_8_rc_6_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_8_rc_6
else
CONF_SIGMA_REALPLUGIN = realplugin_SMP8654F_3_8_8_rc_3.mips
CONF_SIGMA_RUA_SDK= mrua_SMP8654F_3_8_8_rc_3_dev.mips
CONF_SIGMA_RUA_FW = mruafw_SMP8654F_prod_3_8_8_rc_3
endif
endif
endif
endif
SIGMA_SDK_VERSION=3_8_0
MRUASDK=$(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/$(CONF_SIGMA_RUA_SDK)
SIGMA_HWCIPHER_LIB_PATH=$(TOP_MP_DIR)/hwcipher/$(SIGMA_SDK_VERSION)/
CONF_SIGMA_BOOT_LOADER = smp86xx_ezboot_0xaa
CONF_SIGMA_YAMON = smp86xx_yamon_R2.13-31
CFLAGS += -mips32r2 -Wa,-mips32r2 -march=24kf -mtune=24kf
endif

CONF_SIGMA_XMBOOT_TOOLCHAIN = mips-sde-lite
CONF_SIGMA_XMBOOT_TOOLCHAIN_PACKAGE = PN00115-06.61-2B-MIPSSW-LSDE-v6.06.01.tgz

ifeq (x$(CONF_PLATFORM_SMP8654_WISTRON_VILLA_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_wistron_villa
endif

ifeq (x$(CONF_PLATFORM_SMP8654_WISTRON_VILLA_BOARD_D2), xy)
ifeq (x$(CONF_SIGMA_EZBOOT_0X82_NAND_FLASH_DRIVER), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_wistron_villa_512_d2
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy)
ifeq (x$(CONF_BUNGALOW_NEW_PARTITION),xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_bungalow_new_partition
else
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_wistron_villa_512_d2
endif
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_WISTRON_PENTHOUSE_512_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_wistron_penthouse_512
endif

ifeq (x$(CONF_PLATFORM_SMP8654_WISTRON_BOARD), xy)
ifeq (x$(CONF_SIGMA_EZBOOT_0X82_NAND_FLASH_DRIVER), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_wistron
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_wistron
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_LMP555_BOARD), xy)
ifeq (x$(CONF_SIGMA_EZBOOT_0X82_NAND_FLASH_DRIVER), xy) 
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_alpha_lacie
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy) 
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_lacie
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_IOM_BOARD), xy)
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy) 
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_iom_x2
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_iom_t4
endif
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0XAA_NAND_FLASH_DRIVER), xy) 
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0xaa_smp8654_alpha_iom_x2
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0xaa_smp8654_alpha_iom_t4
endif
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_LMP555_A2C_BOARD), xy)
ifeq (x$(CONF_SIGMA_EZBOOT_0X82_NAND_FLASH_DRIVER), xy) 
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x82_smp8654_alpha_lacie_A2c
endif
ifeq (x$(CONF_SIGMA_EZBOOT_0X98_NAND_FLASH_DRIVER), xy) 
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_lacie_A2c
endif
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_AV_LS700L_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_ezboot_0x82_smp8654_alpha_avls700l
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_IMEDIA_HD100_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_ezboot_0x98_smp8654_alpha_imediahd100
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_FUNTWIST_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_ezboot_0x82_smp8654_alpha_funtwist
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_EM7075_BOARD), xy)
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_ezboot_0x98_smp8654_alpha_em7075
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_8AV500LE_BOARD), xy) # RAM: 512MB , FLASH: 128MB
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_8av500le
endif

ifeq (x$(CONF_PLATFORM_SMP8654_ALPHA_RV_BOARD), xy) # RAM: 512MB , FLASH: 256MB
CONF_SMP86XX_XMBOOT_EZBOOT_CONFIG_FILE=smp86xx_xmboot_ezboot_0x98_smp8654_alpha_rv
endif

ifeq (x$(CONF_SECURITY_USE_CPU_BINDING), xy)
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2), xy)
CONF_SIGMA_SDK_CPU_KEY = CPU_KEYS_SMP86xx_2008-08-29_IOMEGA_X2_KEY51
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4), xy)
CONF_SIGMA_SDK_CPU_KEY = CPU_KEYS_SMP86xx_2008-08-29_IOMEGA_X2_KEY51
endif
else
CONF_SIGMA_SDK_CPU_KEY = CPU_KEYS_SMP86xx_2008-08-29
endif
SIGMALIB_MRUA_PATH  := $(MRUASDK)/lib
RUA_DIR             := $(MRUASDK)/MRUA_src
SIGMALIB_MRUA_PATH  := $(MRUASDK)/lib
SIGMALIB_NETFLIX_PATH	:= $(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/netflix/sigma_smp86xx_nrd-$(CONF_SIGMA_NETFLIX_VERSION)/nrd-$(CONF_NETFLIX_VERSION)/dist/Cross_prod.OBJ/
SIGMALIB_FLASHLITE_PATH	:= $(TOP_LIBS_DIR)/$(SIGMA_SDK_VERSION)/flashlite3/flashlite3_$(CONF_FLASHLITE3_VERSION)/lib

endif

BUILD_HOST 	:=      $(shell uname -m)
BUILD_TARGET    :=      $(ARCH)-linux
PATH		:= $(PATH):$(CROSS_BIN)

# em8634 platform flags
SMP8654_RMCFLAGS = \
	-DEM86XX_CHIP=EM86XX_CHIPID_TANGO3\
	-DEM86XX_REVISION=3\
	-DXBOOT2_SMP865X=1\
	-DEM86XX_MODE=EM86XX_MODEID_STANDALONE\
	-DWITH_IRQHANDLER_BOOTLOADER=1\
	-DWITH_XLOADED_UCODE=1\
	-DGCC4_TOOLCHAIN\
	-DDEMUX_PSF=1 \
	-DWITH_RMHDMI=1

COMPILKIND      = 'release'

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_6_0), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_6_1_rc2), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_0), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_1), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_3), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_5), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif
ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_8), xy)
SMP8654_RMCFLAGS = -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3 -DEM86XX_REVISION=3 -DDEMUX_PSF=1 -DXBOOT2_SMP865X=1 -DEM86XX_MODE=EM86XX_MODEID_STANDALONE -DWITH_XLOADED_UCODE=1 -DGCC4_TOOLCHAIN
COMPILKIND='codesourcery hardfloat glibc release'
endif

CFLAGS += $(SMP8654_RMCFLAGS)
CFLAGS += -ggdb \
	-D_FILE_OFFSET_BITS=64 \
	-D_LARGEFILE_SOURCE=1 \
	-D_LARGEFILE64_SOURCE=1 

RMCFLAGS = $(SMP8654_RMCFLAGS)

# Link flags
LDFLAGS = -ggdb -m elf32ltsmip -ldl -L${TOP}/lib
LDFLAGS                 += -L$(SYSLIB_PREFIX)/lib
LDFLAGS                 += -L$(SYSLIB_PREFIX)/../lib
LDFLAGS                 += -L$(CROSS_PREFIX)/lib
LDFLAGS                 += -L$(SIGMA_HWCIPHER_LIB_PATH)/src
LDFLAGS 		+= -L$(SIGMALIB_MRUA_PATH)
LDFLAGS += -L$(SIGMALIB_NETFLIX_PATH)/flash-app/lib/ -L$(SIGMALIB_NETFLIX_PATH)/nrdlib/lib/ -L$(SIGMALIB_FLASHLITE_PATH) 
LDFLAGS			+= -Wl,-rpath-link -Wl,$(SYSLIB_PREFIX)/lib \
		           -Wl,-rpath-link -Wl,$(SIGMALIB_MRUA_PATH) 
LDFLAGS			+= -L$(SYSLIB_PREFIX)/opt/lib 

RMCFLAGS += -I $(SYSLIB_PREFIX)/include

export COMPILKIND RMCFLAGS

# endian
CFLAGS += -D__LITTLE_ENDIAN__
CFLAGS += -I $(SYSLIB_PREFIX)/include
CFLAGS += -I $(SYSLIB_PREFIX)/include/freetype2

############################## compiler section ##############################

# Note: CROSS variable can be set by diffrent product to select 
#       different toolchains.

# Filename extensions
LIB_EXT		:=	a
OBJ_EXT		:=	o
ASM_EXT		:=	s
DEPEND_OBJ_EXT	:=	o
DEPEND_EXT	:=	d
PREPROC_EXT	:=	i
EXE_SUFFIX      :=
EXE_PREFIX      :=      x

# 
AS              = $(CROSS)as
LD              = $(CROSS)ld
CC              = $(CROSS)gcc
DEPEND_CC       = $(CROSS)gcc
CPP             = $(CROSS)cpp -E
AR              = $(CROSS)ar
NM              = $(CROSS)nm
STRIP           = $(CROSS)strip
OBJCOPY	        = $(CROSS)objcopy
OBJDUMP         = $(CROSS)objdump
RANLIB          = $(CROSS)ranlib
LINKER          = $(CROSS)g++
MAKELIB		= $(CROSS)ar -rcus 
export AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER

############################## common flags section ##########################

CFLAGS += $(CONF_COMPILE_WITH_GFLAG) 
CFLAGS += $(CONF_COMPILE_WITH_OPTIMIZE) 

# compiling flags
COMPILER_FLAGS	:=	-c -o # Comment to preserve trailing space

# preprocess flags
PREPROC_FLAGS	:=	-E -o # Comment to preserve trailing space

# dependence flags
CFLAGS_DEP      := -MM -MG -DCHECKING # Comment to preserve trailing space

# warning flags
WARNINGS     :=	-W -Wpointer-arith -Wcast-align \
		-Wwrite-strings -Wstrict-prototypes \
		-Wmissing-prototypes \
		-Wmissing-declarations -Wnested-externs \
                -Werror-implicit-function-declaration -Wundef
#CFLAGS_COMMON = $(WARNINGS) --unsigned-char

CFLAGS += $(CFLAGS_COMMON) 


CFLAGS += 	-DDESKTOP_WIDTH=\($(DESKTOP_WIDTH)\) \
	-DDESKTOP_HEIGHT=\($(DESKTOP_HEIGHT)\) 

############################## extra SDK section #############################


lib_list :=                     \
	dcc \
	llad \
	rmcdfs \
	rmrtk86 \
	rmscc \
	rmmp4api \
	rmmp4 \
	rmmp4core \
	rmmpeg4framework \
	rmdescriptordecoder \
	rmdetectorapi \
	rmdetector \
	rmhttp \
	rmcpputils_t \
	rmcw \
	rmcore \
	rua \
	rmpthreadw \
	ruahdmi

ifeq ($(CONF_WMAPRO_UNSUPPORTED), y)
else
lib_list += rmwmaprodecoder rmwmaprodecodercore
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_7_0), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi
endif

ifeq (x$(CONF_DMA_DTCP_SIGMA), xy)
lib_list += \
	rmdrm   \
	rmdtcpapi
endif

ifeq (x$(CONF_DMA_MS_JANUS_SIGMA), xy)
lib_list += \
	rmdrm   \
	rmwmdrmstub
endif

ifeq (x$(CONF_HAVE_VIDEO_CODEC_RMVB), xy)
lib_list += \
	rmlibrealmedia \
	rmchannel \
	gbus
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_0), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_1), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_2), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_3), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_5), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_7), xy)
lib_list += \
	rmhdmi \
	rmedid \
	rmi2c \
	ruai2c \
	rmsha1 \
	rmcec \
	rmhsi \
	ruahsi \
	rmvideoout \
	displayoutports \
	audiooutports \
	rmmpegdemux \
	rmdisplay
endif

ifeq (x$(CONF_PLATFORM_SMP8654_SDK_3_8_8), xy)
lib_list += \
    rmhdmi \
    rmedid \
    rmi2c \
    ruai2c \
    rmsha1 \
    rmcec \
    rmhsi \
    ruahsi \
    rmvideoout \
    displayoutports \
    audiooutports \
    rmdisplay
endif

ifeq (x$(CONF_SW_DEMUX_PLAYER), xy)
lib_list += \
	rmvdemux
endif

#LIBS_MRUA_A = -Wl,--start-group $(addprefix $(TOP)/lib/lib,$(addsuffix .so,$(lib_list))) -Wl,--end-group
#LIBS_MRUA_A = -Wl,--start-group $(addprefix $(TOP)/lib/lib,$(addsuffix .so,$(lib_list))) -Wl,--end-group
LIBS_MRUA_A = $(addprefix -l,$(lib_list))

CONF_TOOLCHAIN_INSTALL_DIR = "/opt"
export CONF_TOOLCHAIN_INSTALL_DIR
