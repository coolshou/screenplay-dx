##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
#          nicle_yang@alphanetworks.com
# Global definitions fragments 
##############################################################################

ifndef DEFINES_MK_INCLUDED

DEFINES_MK_INCLUDED := 1

#
# Time stamp
#
STAMP := $(shell date +"%Y.%m.%d-%H%M")
export STAMP

#
# CURRENT_SET
#
TOP_CURRENT_SET             := $(TOP)/CURRENT_SET

#
# The absolute path of all the directories. 
#
TOP_SRC_DIR                 := $(TOP)/src#
TOP_BUILD_DIR               := $(TOP)/build#
TOP_TOOLS_DIR               := $(TOP)/tools#
TOP_SCRIPTS_DIR             := $(TOP)/scripts#
TOP_CONFIG_DIR              := $(TOP)/config#
TOP_CUSTOMERS_DIR	    := $(TOP)/customers/$(CONF_CUSTOMER_NAME)/$(CONF_MODEL_NAME)
export TOP_SRC_DIR TOP_BUILD_DIR TOP_TOOLS_DIR TOP_SCRIPTS_DIR TOP_CONFIG_DIR TOP_CUSTOMERS_DIR

TOP_CRYPTO_DIR              := $(TOP)/src/crypto#
TOP_LIBS_DIR                := $(TOP)/src/libs#
TOP_MISC_DIR                := $(TOP)/src/misc#
TOP_MP_DIR                  := $(TOP)/src/mediaplayer#
TOP_RENDERER_DIR            := $(TOP)/src/renderer#
TOP_OSD_DIR                 := $(TOP)/src/osd#
TOP_UTILS_DIR               := $(TOP)/src/util#
TOP_LOCAL_MEDIASERVER_DIR   := $(TOP)/src/server/pc_media_server/RedAVServer1200/Posix#
TOP_CAS   		    := $(TOP)/src/cas#
TOP_DEBUG_DIR               := $(TOP)/src/debug#
export  TOP_CRYPTO_DIR TOP_LIBS_DIR  TOP_MP_DIR TOP_RENDERER_DIR
export  TOP_OSD_DIR    TOP_UTILS_DIR TOP_LOCAL_MEDIASERVER_DIR

#
# MCX ROOT 
#
TOP_MCX_ROOT                := $(TOP_LIBS_DIR)/mcx#
TOP_MCX_PAK_SOURCE          := $(TOP_MCX_ROOT)/PAK/Source#
TOP_MCX_PAL_DIR             := $(TOP_MCX_PAK_SOURCE)/PAL

# The $(MSPK_PLATFORM) may be defined after the include defines.mk, so use = not :=
TOP_MCX_SAMPLES_SHELL_DIR   = $(TOP_MCX_PAK_SOURCE)/Platform/$(MSPK_PLATFORM)/Samples/Shell
TOP_MCX_PAL_INCLUDE         = $(TOP_MCX_PAK_SOURCE)/Platform/$(MSPK_PLATFORM)/PALimpl/include/
TOP_MCX_PDK_XSP_SHARE       = $(TOP_MCX_PAK_SOURCE)/PDK/XSP/Shared/

export TOP_MCX_ROOT TOP_MCX_PAK_SOURCE TOP_MCX_PAL_DIR
export TOP_MCX_SAMPLES_SHELL_DIR  TOP_MCX_PAL_INCLUDE  TOP_MCX_PAK_XSP_SHARE

#
# Cardea root
#
TOP_CARDEA_ROOT             := $(TOP_LIBS_DIR)/cardea#
export TOP_CARDEA_ROOT 

#
# The core make path
#
TOP_CORE_MAKEFILE           := $(TOP_SCRIPTS_DIR)/top.mk

#
# product directory
#
TOP_PRODUCT_DIR             := $(TOP)/product#
TOP_LIB_CONFIG_DIR          := $(TOP_PRODUCT_DIR)/libconfig
export TOP_PRODUCT_DIR TOP_LIB_CONFIG_DIR

#
# rootfs root directory 
#
TOP_BUILD_ROOTFS_DIR                        := $(TOP_BUILD_DIR)/root
TOP_INSTALL_ROOTFS_DIR                      := $(TOP_BUILD_DIR)/root
TOP_INSTALL_ROOTFS_OSD_DIR                  := $(TOP_BUILD_DIR)/root/osd
TOP_INSTALL_ROOTFS_FONT_DIR                 := $(TOP_BUILD_DIR)/root/osd/font
TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR       := $(TOP_BUILD_DIR)/root_primary_system
TOP_FLASHIMAGE_DIR                          := $(TOP_BUILD_DIR)/flashimage
export  TOP_BUILD_ROOTFS_DIR TOP_INSTALL_ROOTFS_DIR TOP_INSTALL_ROOTFS_OSD_DIR TOP_INSTALL_ROOTFS_FONT_DIR TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR TOP_FLASHIMAGE_DIR

#
# download site
#
ifeq (x$(CONF_SPECIFY_SVN_VERSION), xy)
	TOP_DOWNLOAD                := svn co -r $(CONF_SVN_VERSION)
else
	TOP_DOWNLOAD                := svn co
endif
TOP_UPDATE                  := svn up
TOP_STATUS                  := svn st
TOP_DOWNLOAD_CAT            := svn cat
TOP_SVN_SERVER              := $(CONF_REPOSITORY_IP)# 
export TOP_DOWNLOAD TOP_UPDATE TOP_DOWNLOAD_CAT TOP_SVN_SERVER

TOP_DOWNLOAD_SITE           := http://2.42.9.253/svn/SMP/Trunk

TOP_LIBS_URL                := $(TOP_DOWNLOAD_SITE)/bsp_repos#
TOP_PRODUCT_URL             := $(TOP_DOWNLOAD_SITE)/product_repos#
TOP_RESOURCE_URL            := $(TOP_DOWNLOAD_SITE)/resource_repos#
TOP_RELEASE_URL             := http://$(TOP_SVN_SERVER)/dmax/release/tvdock#
export TOP_LIBS_URL TOP_PRODUCT_URL TOP_RESOURCE_URL

# 
# unpack tools
#
TOP_UNPACK_TGZ              := tar -zxv
export TOP_UNPACK_TGZ

endif    # DEFINES_MK_INCLUDED
