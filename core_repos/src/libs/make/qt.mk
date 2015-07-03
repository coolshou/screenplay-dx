##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# QT makefile fragments 
##############################################################################

#
# Defines
#
ifndef  QT_VERSION 
QT_VERSION := 4.7.0
endif

QT             := qt-everywhere-opensource-src#
QT_SERVER_URL  := $(TOP_LIBS_URL)/$(QT)/
QT_DIR         := $(TOP_LIBS_DIR)#
QT_SOURCE      := $(TOP_LIBS_DIR)/$(QT)/$(QT)-$(QT_VERSION)
QT_CONFIG      := 


#
# Download  the source 
#
.PHONY: qt-downloaded

qt-downloaded: $(QT_DIR)/.qt_downloaded

$(QT_DIR)/.qt_downloaded:
	touch $@

#
# Unpack the source
#
.PHONY: qt-unpacked

qt-unpacked: $(QT_DIR)/.qt_unpacked

$(QT_DIR)/.qt_unpacked: $(QT_DIR)/.qt_downloaded
	@if [ ! -d "$(QT_SOURCE)" ]; then \
		cd $(TOP_LIBS_DIR)/$(QT); \
		tar -zxvf $(QT_SOURCE).tar.gz;	\
	fi
	@touch $@


#
# Patch the source
#
.PHONY: qt-patched

qt-patched: $(QT_DIR)/.qt_patched

$(QT_DIR)/.qt_patched: $(QT_DIR)/.qt_unpacked
	cp $(TOP_LIBS_DIR)/$(QT)/qmake.conf $(QT_SOURCE)/mkspecs/qws/linux-mips-g++/
	touch $@


#
# config
#
.PHONY: qt-config

qt-config: 

#
# Configuration
#
.PHONY: qt-configured

qt-configured:$(QT_DIR)/.qt_configured

$(QT_DIR)/.qt_configured: $(QT_DIR)/.qt_patched
	@echo "Configured $(QT) ..."
	cd $(QT_SOURCE);\
	unset AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER LD_LIBRARY_PATH;\
	export AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER LD_LIBRARY_PATH;\
	export CROSS=mips-linux-gnu- ;\
	export CROSS_COMPILER_FLAGS=-EL ;\
	export DIRECTFB_I=$(TOP_LIBS_DIR)/$(QT)/directfb;\
	export DIRECTFB_L=$(SYSLIB_PREFIX);\
	./configure -prefix $(LIBS_INSTALL_PATH) -release -opensource -embedded mips -xplatform /qws/linux-mips-g++ -little-endian -webkit -no-nis -no-cups -no-dbus -qt-freetype -no-gfx-transformed -no-gfx-multiscreen -no-accessibility -no-xmlpatterns -nomake tools -nomake docs -nomake examples -nomake translations -nomake demos -fast -confirm-license  -qt-kbd-tty -qt-kbd-linuxinput -qt-mouse-pc -qt-mouse-linuxinput -qt-gfx-directfb -v
	@echo "Configured $(QT) done"
	@touch $@

#
# Compile
#
.PHONY: qt-compile

qt-compile: qt-configured $(QT_DIR)/.qt_compiled

$(QT_DIR)/.qt_compiled:
	@echo "Compiling $(QT) ..."
	unset AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER;\
	export AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER;\
	export COMPILKIND='codesourcery hardfloat glibc release';\
	unset AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER LD_LIBRARY_PATH;\
	export AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER LD_LIBRARY_PATH;\
	export CROSS=mips-linux-gnu- ;\
	export CROSS_COMPILER_FLAGS=-EL ;\
	export DIRECTFB_I=$(TOP_LIBS_DIR)/$(QT)/directfb;\
	export DIRECTFB_L=$(SYSLIB_PREFIX);\
	make -C $(QT_SOURCE)
	make -C $(QT_SOURCE) install
	@echo "Compiling $(QT) done"
	@touch $@

#
# Update
#
.PHONY: qt-update

qt-update:
	@echo "Updating $(QT) done"

#
# Status
#
.PHONY: qt-status

ftpd-status:
	@echo "Statusing $(QT) done"

#
# Clean
#
.PHONY: qt-clean

qt-clean:
	@if [ -d "$(QT_SOURCE)" ]; then\
		make -C $(QT_SOURCE) clean; \
	fi

#
# Dist clean
#
.PHONY: qt-distclean

qt-distclean:
	rm -f $(TOP_LIBS_DIR)/.qt*

#
# Install
#
.PHONY: qt-install

qt-install:


