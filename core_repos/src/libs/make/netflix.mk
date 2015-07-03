##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# netflix makefile fragments 
##############################################################################

#
# Defines
#
ifndef CONF_NETFLIX_VERSION 
ifeq (x$(CONF_NETFLIX_3_0),xy)
        CONF_NETFLIX_VERSION := 3.0.2-591521
else
        CONF_NETFLIX_VERSION := v2.0.4-091027-02
endif
endif

ifndef CONF_SIGMA_NETFLIX_VERSION
CONF_SIGMA_NETFLIX_VERSION := v2.0.4_20091229
endif

SIGMA_SDK_SERVER_URL	:= $(TOP_LIBS_URL)/sigma_sdk/$(CONF_SIGMA_CHIP_NO)/$(CONF_SIGMA_SDK_VERSION)#
SIGMA_SDK_SOURCE		:= $(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)#

NETFLIX_DIR				:= $(SIGMA_SDK_SOURCE)/netflix#
NETFLIX					:= sigma_smp86xx_nrd-$(CONF_SIGMA_NETFLIX_VERSION)
NETFLIX_SOURCE      	:= $(NETFLIX_DIR)/$(NETFLIX)#

PURE_NETFLIX			:= nrd-$(CONF_NETFLIX_VERSION)
PURE_NETFLIX_SOURCE		:= $(NETFLIX_SOURCE)/$(PURE_NETFLIX)

# Download  the source 
#
.PHONY: netflix-downloaded

netflix-downloaded: 

# Unpack the source
#
.PHONY: netflix-unpacked

netflix-unpacked: $(TOP_LIBS_DIR)/.netflix_unpacked

$(TOP_LIBS_DIR)/.netflix_unpacked: $(NETFLIX_SOURCE).tar.bz2 $(NETFLIX_DIR)/nrd-$(CONF_NETFLIX_VERSION).tar.bz2 
	@echo "Unpacking $(NETFLIX) ..."
	if [ -d "$(NETFLIX_SOURCE)" ]; then \
		rm -fr $(NETFLIX_SOURCE); \
	fi
	(cd $(NETFLIX_DIR); mkdir $(NETFLIX_SOURCE))
	(cd $(NETFLIX_SOURCE); tar xjf ../nrd-$(CONF_NETFLIX_VERSION).tar.bz2)
	@echo "Unpacking $(NETFLIX) done"
	@touch $@


#
# Patch the source
#
.PHONY: netflix-patched

netflix-patched: $(TOP_LIBS_DIR)/.netflix_patched

$(TOP_LIBS_DIR)/.netflix_patched: $(TOP_LIBS_DIR)/.netflix_unpacked
	# Patching...
ifeq (x$(CONF_NETFLIX_VERSION),x3.0.2-591521)
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/nrd_3.0.2-1.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/netflix_3_0_2_2_against_1.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/netflix_3_0_2_3_against_2.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/netflix_3_0_2_4_against_3.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/31242.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/nfx_keyboard_backspace_fix.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/31665.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/nrd_3.0.2-1_3rdParty.patch;
	cd $(PURE_NETFLIX_SOURCE); patch -p1 < $(NETFLIX_DIR)/nrd_3.0.2-remove-debug-log;
	(sed -i -e 's/cross_rootfs//' $(PURE_NETFLIX_SOURCE)/config/Cross.mk);
	(sed -i -e 's/cross_rootfs//' $(PURE_NETFLIX_SOURCE)/3rdParty/qt/mkspecs/qws/linux-mips_sigma-g++/qmake.conf);
	(sed -i -e 's/\/mnt\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/app/qt/src/AppConfiguration.cpp);
	(sed -i -e 's/\/mnt\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/Device/FileSystem.cpp);
	(sed -i -e 's/\/mnt\/nrd/\/tmp/' $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/Device/Playback/Cross/DrmSession.cpp);
	(sed -i -e 's/\/mnt\/nrd/\/tmp/' $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/Device/Playback/Cross/PlaybackDeviceCross.cpp);
	(sed -i -e 's/..\/etc\/certs\/ca.pem/\/etc\/ca.pem/' $(PURE_NETFLIX_SOURCE)/nrdlib-core/src/QAWrappers/QAPlugin.cpp);
	(sed -i -e 's/..\/etc\/certs\/ca.pem/\/etc\/ca.pem/' $(PURE_NETFLIX_SOURCE)/app/qt/src/AppConfiguration.cpp);
	(sed -i -e 's/..\/etc\/certs\/ca.pem/\/etc\/ca.pem/' $(PURE_NETFLIX_SOURCE)/app/qt/src/ConfigData.cpp);
	(sed -i -e 's/..\/etc\/certs\/ca.pem/\/etc\/ca.pem/' $(PURE_NETFLIX_SOURCE)/app/qt/resources/configuration/config.xml);
	(sed -i -e 's/..\/var\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/app/qt/src/ConfigData.cpp);
	(sed -i -e 's/..\/var\/nrd\/persistentStore/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/app/qt/src/AppConfiguration.cpp);
	(sed -i -e 's/..\/var\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/app/qt/src/AppConfiguration.cpp);
	(sed -i -e 's/..\/var\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/app/qt/resources/configuration/config.xml);
	(sed -i -e 's/..\/var\/nrd/\/tmp\/conf/' $(PURE_NETFLIX_SOURCE)/nrdlib-core/src/QAWrappers/QAPlugin.cpp);
	(sed -i -e 's/CONST_ROOT\"etc\/certs\"/\"\/etc\"/' $(PURE_NETFLIX_SOURCE)/nrdlib-core/include/prv/Base/Constants.h);
#	(sed -i -e 's/SRC_TESTING/SRC_NETFLIX_BUTTON/' $(PURE_NETFLIX_SOURCE)/app/qt/src/NetflixApplication.cpp);
ifneq (x$(CONF_NETFLIX_REMOTE_BUTTON),xy)
	(sed -i -e 's/sNetflixApplication->logLaunchSource();/\/\/sNetflixApplication->logLaunchSource();/' $(PURE_NETFLIX_SOURCE)/app/qt/src/NetflixApplication.cpp);
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2),xy)
	(sed -i -e 's/Sigma Designs Reference Application/iomega_x2/' $(PURE_NETFLIX_SOURCE)/app/qt/src/NetflixApplication.cpp);
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4),xy)
	(sed -i -e 's/Sigma Designs Reference Application/iomega_t4/' $(PURE_NETFLIX_SOURCE)/app/qt/src/NetflixApplication.cpp);
endif
ifeq (x$(CONF_SECURITY_PROPRIETARY_ENCRYPT), xy)
	(sed -i -e 's/\/mnt\/nrd/\/usr\/local\/sbin\/netflix\/oauth/' $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/NccpXtask/NccpXtask.cpp);
else
	(sed -i -e 's/\/mnt\/nrd/\/netflix\/oauth/' $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/NccpXtask/NccpXtask.cpp);
endif
	(cp -f $(NETFLIX_DIR)/librmnccp.a $(PURE_NETFLIX_SOURCE)/nrdlib-device/src/NccpXtask/)
endif
	@touch $@

#
# config
#
.PHONY: netflix-config

netflix-config: 

#
# Configuration
#
.PHONY: netflix-configured

netflix-configured:  netflix-config $(TOP_LIBS_DIR)/.netflix_configured

$(TOP_LIBS_DIR)/.netflix_configured: $(TOP_LIBS_DIR)/.netflix_patched $(NETFLIX_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(NETFLIX) ..."
	@touch $@

#
# Compile
#
.PHONY: netflix-compile

netflix-compile: $(TOP_LIBS_DIR)/.netflix_compiled

$(TOP_LIBS_DIR)/.netflix_compiled: $(TOP_LIBS_DIR)/.netflix_configured
	@echo "Compiling $(NETFLIX) ..."
ifeq (x$(CONF_NETFLIX_VERSION),x3.0.2-591521)
	(cd $(SIGMA_SDK_SOURCE)/${CONF_SIGMA_SDK_CPU_KEY}/; source ./CPU_KEYS.env; cd $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK);source ./build.env; cd $(SIGMA_SDK_SOURCE)/DCCHD/dcchd_$(CONF_DCCHD_VERSION); source ./DCCHD.env; export COMPILKIND='codesourcery hardfloat glibc release withthreads janus nccpxtask'; export QT_DIR=$(PURE_NETFLIX_SOURCE)/3rdParty/qt; export QT_INSTALL_DIR=$(PURE_NETFLIX_SOURCE)/qt; export DCCHD_CFG_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/dcchd/config/default/; export DCCHD_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/dcchd/; export DIRECTFB_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/directfb/; export DIRECTFB_INSTALL_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/directfb/; export RUA_DIR=$(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/MRUA_src/; export SMP86XX_ROOTFS_PATH=$(SYSLIB_PREFIX); export SMP86XX_TOOLCHAIN_PATH=$(CONF_CROSS_PREFIX); export BUILD_PLATFORM=cross; export BUILD_MODE=prod; export NETFLIX_STORAGE_DIR=/tmp/netflix; cd $(PURE_NETFLIX_SOURCE); make -f Makefile.smp86xx; unset AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER; export AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER; make -C 3rdParty/qt; make -f Makefile.smp86xx qt-app)
	-(cd $(SIGMA_SDK_SOURCE)/${CONF_SIGMA_SDK_CPU_KEY}/; source ./CPU_KEYS.env; cd $(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK);source ./build.env; cd $(SIGMA_SDK_SOURCE)/DCCHD/dcchd_$(CONF_DCCHD_VERSION); source ./DCCHD.env; export COMPILKIND='codesourcery hardfloat glibc release withthreads janus nccpxtask'; export QT_DIR=$(PURE_NETFLIX_SOURCE)/3rdParty/qt; export QT_INSTALL_DIR=$(PURE_NETFLIX_SOURCE)/qt; export DCCHD_CFG_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/dcchd/config/default/; export DCCHD_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/dcchd/; export DIRECTFB_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/directfb/; export DIRECTFB_INSTALL_DIR=$(TOP_LIBS_DIR)/3_8_0/DCCHD/dcchd_$(CONF_DCCHD_VERSION)/directfb/; export RUA_DIR=$(SIGMA_SDK_SOURCE)/$(CONF_SIGMA_RUA_SDK)/MRUA_src/; export SMP86XX_ROOTFS_PATH=$(SYSLIB_PREFIX); export SMP86XX_TOOLCHAIN_PATH=$(CONF_CROSS_PREFIX); export BUILD_PLATFORM=cross; export BUILD_MODE=prod; export NETFLIX_STORAGE_DIR=/tmp/netflix; cd $(PURE_NETFLIX_SOURCE); make -f Makefile.smp86xx qt-lib)
endif
	@echo "Compiling $(NETFLIX) done"
	@touch $@

#
# Update
#
.PHONY: netflix-update

netflix-update:
	@echo "Updating $(NETFLIX) ..."
	@if [ -d "$(NETFLIX_SOURCE)" ]; then\
		$(TOP_UPDATE) $(NETFLIX_SOURCE); \
	fi
	@echo "Updating $(NETFLIX) done"

#
# Status
#
.PHONY: netflix-status

netflix-status:
	@echo "Statusing $(NETFLIX) ..."
	@if [ -d "$(NETFLIX_SOURCE)" ]; then\
		$(TOP_STATUS) $(NETFLIX_SOURCE); \
	fi
	@echo "Statusing $(NETFLIX) done"

#
# Clean
#
.PHONY: netflix-clean

netflix-clean:
	@rm -f $(TOP_LIBS_DIR)/.netflix_configured
	@if [ -d "$(NETFLIX_SOURCE)" ]; then\
		make -C $(NETFLIX_SOURCE)/$(NETFLIX) clean; \
	fi

#
# Dist clean
#
.PHONY: netflix-distclean

netflix-distclean:
	@rm -f $(TOP_LIBS_DIR)/.netflix*

#
# Install
#
.PHONY: netflix-install

netflix-install:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/etc/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/netflix
ifeq (x$(CONF_NETFLIX_VERSION),xv2.0.4-091027-02)
	cp -avRf $(PURE_NETFLIX_SOURCE)/dist/Cross_prod.OBJ/flash-app/swf $(TOP_INSTALL_ROOTFS_DIR)/netflix/
	#cp -avRf $(PURE_NETFLIX_SOURCE)/dist/Cross_prod.OBJ/flash-app/bin $(TOP_INSTALL_ROOTFS_DIR)/netflix/
	cp -avRf $(PURE_NETFLIX_SOURCE)/dist/Cross_prod.OBJ/flash-app/lib $(LIBS_INSTALL_PATH)/
	cp -avRf $(PURE_NETFLIX_SOURCE)/dist/Cross_prod.OBJ/flash-app/etc/certs $(TOP_INSTALL_ROOTFS_DIR)/etc/
#	cp -f $(NETFLIX_SOURCE)/nccp_xtask-smp8644-0.5/libnccp.0.5.xos2P4a.so $(LIBS_INSTALL_PATH)/lib/librmnccp.so
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2),xy)
	(sed -i -e 's/sign_up_url=\"http:\/\/www.netflix.com\/VENDOR_NAME\"/sign_up_url=\"http:\/\/www.netflix.com\/iomega\"/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(sed -i -e 's/sign_up_url_display=\"netflix.com\/VENDOR_NAME\"/sign_up_url_display=\"netflix.com\/iomega\"/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(sed -i -e 's/VENDOR_NAME/iomega_x2/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(cp -f $(NETFLIX_DIR)/oauth_x2.bin $(TOP_INSTALL_ROOTFS_DIR)/netflix/oauth.bin)
endif
ifeq (x$(CONF_PRODUCT_EXT_IOM_T4),xy)
	(sed -i -e 's/sign_up_url=\"http:\/\/www.netflix.com\/VENDOR_NAME\"/sign_up_url=\"http:\/\/www.netflix.com\/iomega\"/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(sed -i -e 's/sign_up_url_display=\"netflix.com\/VENDOR_NAME\"/sign_up_url_display=\"netflix.com\/iomega\"/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(sed -i -e 's/VENDOR_NAME/iomega_t4/' $(TOP_INSTALL_ROOTFS_DIR)//netflix/swf/device.xml);
	(cp -f $(NETFLIX_DIR)/oauth_t4.bin $(TOP_INSTALL_ROOTFS_DIR)/netflix/oauth.bin)
endif
endif
ifeq (x$(CONF_NETFLIX_VERSION),x3.0.2-591521)
	cp -avRf $(PURE_NETFLIX_SOURCE)/qt/lib $(LIBS_INSTALL_PATH)/
#	cp -avRf $(PURE_NETFLIX_SOURCE)/nrdlib-core/data/etc/certs/ca.pem $(TOP_INSTALL_ROOTFS_DIR)/etc/
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/opt/qt/fonts
	cp -avRf $(PURE_NETFLIX_SOURCE)/3rdParty/fonts/* $(TOP_INSTALL_ROOTFS_DIR)/opt/qt/fonts
	@cp -af $(PURE_NETFLIX_SOURCE)/qt/plugins $(TOP_INSTALL_ROOTFS_DIR)/opt/qt
#	(cp -f $(NETFLIX_DIR)/siab_cacert.pem $(TOP_INSTALL_ROOTFS_DIR)/etc)
	(mkdir $(TOP_INSTALL_ROOTFS_DIR)/netflix/oauth;)
ifeq (x$(CONF_PRODUCT_EXT_IOM_X2),xy)
	(cp -f $(NETFLIX_DIR)/oauth_x2.bin $(TOP_INSTALL_ROOTFS_DIR)/netflix/oauth/oauth.bin)
else
	(cp -f $(NETFLIX_DIR)/oauth_t4.bin $(TOP_INSTALL_ROOTFS_DIR)/netflix/oauth/oauth.bin)
endif
endif
