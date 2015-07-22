############################# global settings section ########################

TOP        := $(shell pwd)/../..#
include $(TOP)/Target.mk

COMPONENT  := src/libs# 

#
# DEBUG_LIB
#
DEBUG_LIB  := 1

#
# LIBS_INSTALL_PATH
#
ifeq (x$(DEBUG_LIB), x1)
LIBS_INSTALL_PATH := $(SYSLIB_PREFIX)/
else
LIBS_INSTALL_PATH := $(CROSS_PREFIX)/
endif
export LIBS_INSTALL_PATH

############################ object rules section ############################

LIBS_LIST_y				+=	popt
LIBS_LIST_$(CONF_ESPIAL_BROWSER) 	+=	espial
LIBS_LIST_$(CONF_ESPIAL_CPU_LIMIT) 	+=	cpulimit
LIBS_LIST_$(CONF_ZLIB)			+=	zlib
LIBS_LIST_$(CONF_LIBCX)			+=	libcx
LIBS_LIST_$(CONF_LIBJPEG)		+=	libjpeg
LIBS_LIST_$(CONF_LIBPNG)		+=	libpng
LIBS_LIST_$(CONF_LIBMCRYPT)		+= 	libmcrypt
LIBS_LIST_$(CONF_TIFF)			+=	tiff
LIBS_LIST_$(CONF_FREETYPE)		+=	freetype
LIBS_LIST_$(CONF_FREETYPE_DCCHD)	+=	freetype_dcchd
LIBS_LIST_$(CONF_FRIBIDI)		+=      fribidi
LIBS_LIST_$(CONF_OPENSSL)		+=	openssl
LIBS_LIST_$(CONF_DROPBEAR)		+=	dropbear
LIBS_LIST_$(CONF_TINYXML)		+=	tinyxml
LIBS_LIST_$(CONF_LIBUNGIF)		+=	libungif
LIBS_LIST_$(CONF_CURL)			+=	curl
LIBS_LIST_$(CONF_BUILD_SIGMA_SDK)	+=	linux_kernel sigma_driver
#LIBS_LIST_$(CONF_BUILD_SIGMA_SDK)	+=	sigma_package linux_kernel sigma_sdk sigma_driver
LIBS_LIST_$(CONF_SECURITY_PROPRIETARY_ENCRYPT)  +=      sigma_key_tools util-linux-ng-mips util-linux-ng-x86
#LIBS_LIST_$(CONF_BUILD_ZBOOT)		+=	sigma_zboot	
#LIBS_LIST_$(CONF_SUPPORT_DCCHD)		+=	dcchd	
#LIBS_LIST_$(CONF_QT_WEB_KIT)		+=	qt	
#LIBS_LIST_$(CONF_FLASHLITE3)		+= flashlite3
LIBS_LIST_$(CONF_DMA_VUDU)			+= vudu
LIBS_LIST_$(CONF_BUSYBOX)		+=	busybox
LIBS_LIST_$(CONF_BUSYBOX_PRIMARY_SYSTEM)+=	busybox_primary_system
LIBS_LIST_$(CONF_DMALLOC)		+=	dmalloc
LIBS_LIST_$(CONF_DOSFSTOOLS)		+=	dosfstools
LIBS_LIST_$(CONF_FLAC)			+=	flac
LIBS_LIST_$(CONF_LIBICONV)		+=	libiconv
#fonts require freetype 2.3.9, why?
LIBS_LIST_$(CONF_FONTS)			+=	fonts
LIBS_LIST_$(CONF_MICROWIN)		+=	microwin
LIBS_LIST_$(CONF_MXML)			+=	mxml
LIBS_LIST_$(CONF_EXPAT)				+= expat
LIBS_LIST_$(CONF_NTP)				+= ntp
LIBS_LIST_y				+= 	c-ares libidn
#LIBS_LIST_$(CONF_DMA_NETFLIX)		+= 	netflix
LIBS_LIST_$(CONF_MATRIXSSL)		+=	matrixssl
LIBS_LIST_$(CONF_SQLITE)		+=	sqlite
LIBS_LIST_$(CONF_TREMOR)		+=	tremor
LIBS_LIST_$(CONF_HFS_FSCK_SUPPORT)	+=	diskdev_cmds
LIBS_LIST_$(CONF_HFS_MKFS_SUPPORT)	+=	diskdev_cmds
LIBS_LIST_$(CONF_NTFS_3G_SUPPORT)	+=	ntfs-3g
LIBS_LIST_$(CONF_NTFS_3G_COMMERCIAL_SUPPORT)	+=	tntfs
#LIBS_LIST_$(CONF_PARAGON_NTFS_SUPPORT)	+=	paragon_ntfs
#LIBS_LIST_$(CONF_PARAGON_HFS_FSCK_SUPPORT)	+= paragon_hfs_fsck 
#LIBS_LIST_$(CONF_PARAGON_NTFS_TOOLS)	+=	paragon_ntfs_tools
LIBS_LIST_$(CONF_DHCPCD)		+=	dhcpcd
LIBS_LIST_$(CONF_SAMBA)			+=	samba
LIBS_LIST_$(CONF_XML2)			+=	libxml2
LIBS_LIST_$(CONF_FONTCONFIG)		+=	fontconfig
LIBS_LIST_$(CONF_PCRE)			+=	pcre

#LIBS_LIST_$(CONF_TWONKYMEDIA_SERVER)	+=	twonkymedia_server	
LIBS_LIST_$(CONF_WIRELESS_SUPPORT)	+=	wireless_drivers
LIBS_LIST_$(CONF_WIRELESS_TOOLS)	+=	wireless_tools
LIBS_LIST_$(CONF_WPA_SUPPLICANT)	+=	wpa_supplicant
LIBS_LIST_$(CONF_IPERF_TOOL)		+=	iperf
LIBS_LIST_$(CONF_BERKELEY_DB)		+=	berkeley
LIBS_LIST_$(CONF_NETATALK)		+=	netatalk
LIBS_LIST_$(CONF_HOWL)			+=      howl
LIBS_LIST_$(CONF_LLTD)			+=      lltd
LIBS_LIST_$(CONF_FLICKR)		+=	flickcurl
LIBS_LIST_$(CONF_SDPARM)		+=	sdparm
LIBS_LIST_$(CONF_SMARTMONTOOLS)		+=	smartmontools
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	fuse
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	glib
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	libexif
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	libusb
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	gettext
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	libtool
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	libgphoto2
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	gphoto2
LIBS_LIST_$(CONF_PTP_SUPPORT)		+=	gphotofs
LIBS_LIST_$(CONF_NTFSPROGS_SUPPORT)	+= 	ntfsprogs
LIBS_LIST_$(CONF_ITUNE_SUPPORT)		+=	libid3tag gdbm mt-daapd
LIBS_LIST_$(CONF_WIN7_WAKEONLAN)	+=	wol
LIBS_LIST_$(CONF_SUPPORT_RSYNC)		+=	rsync
LIBS_LIST_$(CONF_UUID)			+=	uuid
LIBS_LIST_$(CONF_XFS)			+=	xfs
LIBS_LIST_$(CONF_PARTED)		+=	parted
LIBS_LIST_$(CONF_WEB_SERVER_APACHE)     +=      httpd
LIBS_LIST_$(CONF_WEB_SERVER_PHP)	+=	php
LIBS_LIST_$(CONF_PG8169)		+=	pg8169
LIBS_LIST_$(CONF_DMA_CINEMANOW)		+= 	cnsdk
LIBS_LIST_$(CONF_DBUS)			+=	dbus
LIBS_LIST_$(CONF_BONNIE)		+=	bonnie
LIBS_LIST_$(CONF_DIVX_CERTIFICATION)	+=	divx_drm
LIBS_LIST_$(CONF_LIBEVENT)		+=	libevent
LIBS_LIST_$(CONF_TRANSMISSION)		+=	transmission
LIBS_LIST_$(CONF_SIGMA_OWB_BROWSER)		+=	owb
LIBS_LIST_$(CONF_GLIB)                 +=      glib
LIBS_LIST_$(CONF_DIRECTFB)           +=      directfb
LIBS_LIST_$(CONF_QT_WEB_KIT)           +=      qt
LIBS_LIST_$(CONF_PRODUCE_ANIMATION_SPLASH_SCREEN)		+=	sigma_isdk
LIBS_LIST_$(CONF_MONGOOSE)		+=	mongoose

LIBS_LIST += toolchain $(LIBS_LIST_y) dns

# We have to put rootfs at last because it will do md5sum
FINAL_LIBS_LIST_$(CONF_BUILD_ROOTFS_PRIMARY_SYSTEM)	+=	primary_system
FINAL_LIBS_LIST_$(CONF_BUILD_ROOTFS)		+=	rootfs

LIBS_LIST += $(FINAL_LIBS_LIST_y)

########################### target section ###################################

#
# Compile
#
COMPILE_TARGETS := $(patsubst %, %-compile, $(LIBS_LIST))

all:$(COMPILE_TARGETS)

#
# download
#
DOWNLOAD_TARGETS := $(patsubst %, %-patched, $(LIBS_LIST))

.PHONY: download

download: .downloaded

.downloaded: $(DOWNLOAD_TARGETS)
	@touch .downloaded
	@echo
	@echo "  Next, you can build the libs"
	@echo

#
# install
#
INSTALL_TARGETS := $(patsubst %, %-install, $(LIBS_LIST))

.PHONY: install install-all

install install_all: $(INSTALL_TARGETS)

#
# update
#
UPDATE_TARGETS  := $(patsubst %, %-update, $(LIBS_LIST))

.PHONY: update

update: $(UPDATE_TARGETS)
	@echo -en "\n\\033[0;33m ........ Updating the src/libs ............\\033[0m\n"
	@$(TOP_UPDATE)
	@echo -en "\n\\033[0;33m ........ Updating the src/libs done ............\\033[0m\n"

#
# status
#
STATUS_TARGETS  := $(patsubst %, %-status, $(LIBS_LIST))

.PHONY: status

status: $(STATUS_TARGETS)
	@echo -en "\n\\033[0;33m ........ Statusing the src/libs ............\\033[0m\n"
	@$(TOP_STATUS)
	@echo -en "\n\\033[0;33m ........ Statusing the src/libs done ............\\033[0m\n"


#
# clean
#
CLEAN_TARGETS := $(patsubst %, %-clean, $(LIBS_LIST))

.PHONY: clean

clean:
	@echo -en "\n\\033[0;33m ........ We don't clean the src/libs ............\\033[0m\n"

cleanlib: $(CLEAN_TARGETS)
	@echo -en "\n\\033[0;33m ........ Clean the src/libs ............\\033[0m\n"
	@rm -f .downloaded
	@echo -en "\n\\033[0;33m ........ Clean the src/libs done ............\\033[0m\n"

#
# distclean
#
DISTCLEAN_TARGETS := $(patsubst %, %-distclean, $(LIBS_LIST))

.PHONY: distclean

distclean:$(DISTCLEAN_TARGETS)
	@echo -en "\n\\033[0;33m ........ Distclean the src/libs ............\\033[0m\n"
	@rm -f .downloaded
	@echo -en "\n\\033[0;33m ........ Distclean the src/libs done ............\\033[0m\n"

#
# Components
#
LIBS_MAKEFILE := $(addprefix make/, $(patsubst %, %.mk, $(LIBS_LIST)))
include $(LIBS_MAKEFILE)

asm:
