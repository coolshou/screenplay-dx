##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# wireless-driver makefile fragments 
##############################################################################

#
# Defines
#
ifndef  WIRELESS_DRIVERS_VERSION 
WIRELESS_DRIVERS_VERSION := madwifi
endif
WIRELESS_RT2880_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2008_1120_RT2880_iNIC_v1.1.9.0/#
ifeq ($(CONF_RT2870_VERSION_2_1_0_0), y)
WIRELESS_RT2870_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2009_0302_RT2870_Linux_STA_v2.1.0.0#
endif
ifeq ($(CONF_RT2870_VERSION_2_4_0_0), y)
WIRELESS_RT2870_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2010_06_25_RT2870_Linux_STA_v2.4.0.0#
endif
WIRELESS_RT2860_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2009_0521_RT2860_Linux_STA_V2.1.2.0#
ifeq ($(CONF_RT3070_VERSION_2_1_0_0), y)
WIRELESS_RT3070_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2009_03_25_RT3070_Linux_STA_V2.1.0.0#
endif
ifeq ($(CONF_RT3070_VERSION_2_5_0_1), y)
WIRELESS_RT3070_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2011_0107_RT3070_RT3370_Linux_STA_v2.5.0.1_DPA#
endif
ifeq ($(CONF_RT3572_VERSION_2_1_2_0), y)
WIRELESS_RT3572_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2009_0521_RT3572_Linux_STA_V2.1.2.0#
endif
ifeq ($(CONF_RT3572_VERSION_2_5_0_0), y)
WIRELESS_RT3572_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/ralink/2010_1215_RT3572_Linux_STA_v2.5.0.0.DPA#
endif
WIRELESS_AR9170_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/atheros/ar9170/srcOtusLinux_3_2_0_32#
WIRELESS_RTL8192_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/realtek/rtl8192u_linux_2.6.0006.1031.2008#
WIRELESS_RTL8712_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/realtek/rtl8712_8188_8191_8192SU#
WIRELESS_BCM4323_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/broadcom/bcm4323#
WIRELESS_UB94_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/atheros/ub94#
ATHR_HOSTAP_SERVER_URL  := $(TOP_LIBS_URL)/wireless_drivers/atheros/athr-hostap#

WIRELESS_DRIVERS_DIR         := $(TOP_LIBS_DIR)#
WIRELESS_RT2880_SOURCE	    := $(WIRELESS_DRIVERS_DIR)/2008_1120_RT2880_iNIC_v1.1.9.0/module-v1.9.0.0/#
WIRELESS_RT2860_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2009_0521_RT2860_Linux_STA_V2.1.2.0
ifeq ($(CONF_RT2870_VERSION_2_1_0_0), y)
WIRELESS_RT2870_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2009_0302_RT2870_Linux_STA_v2.1.0.0
endif
ifeq ($(CONF_RT2870_VERSION_2_4_0_0), y)
WIRELESS_RT2870_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2010_06_25_RT2870_Linux_STA_v2.4.0.0
endif
ifeq ($(CONF_RT3070_VERSION_2_1_0_0), y)
WIRELESS_RT3070_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2009_03_25_RT3070_Linux_STA_V2.1.0.0
endif
ifeq ($(CONF_RT3070_VERSION_2_5_0_1), y)
WIRELESS_RT3070_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2011_0107_RT3070_RT3370_Linux_STA_v2.5.0.1_DPA
endif
ifeq ($(CONF_RT3572_VERSION_2_1_2_0), y)
WIRELESS_RT3572_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2009_0521_RT3572_Linux_STA_V2.1.2.0
endif
ifeq ($(CONF_RT3572_VERSION_2_5_0_0), y)
WIRELESS_RT3572_SOURCE      := $(WIRELESS_DRIVERS_DIR)/2010_1215_RT3572_Linux_STA_v2.5.0.0.DPA
endif
WIRELESS_AR9170_SOURCE      := $(WIRELESS_DRIVERS_DIR)/srcOtusLinux_3_2_0_32
WIRELESS_RTL8192_SOURCE      := $(WIRELESS_DRIVERS_DIR)/rtl8192u_linux_2.6.0006.1031.2008
WIRELESS_RTL8712_SOURCE      := $(WIRELESS_DRIVERS_DIR)/rtl8712_8188_8191_8192SU
WIRELESS_BCM4323_SOURCE		:= $(WIRELESS_DRIVERS_DIR)/bcm4323
WIRELESS_UB94_SOURCE		:= $(WIRELESS_DRIVERS_DIR)/ub94
#WIRELESS_UB94_SOURCE		:= $(WIRELESS_DRIVERS_DIR)/atheros_ub9x.patched
ATHR_HOSTAP_SOURCE		:= $(WIRELESS_DRIVERS_DIR)/athr-hostap
WIRELESS_DRIVERS_CONFIG		:=

#
# Download  the source 
#
.PHONY: wireless_drivers-downloaded

wireless_drivers-downloaded: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_downloaded

$(WIRELESS_DRIVERS_DIR)/.wireless_drivers_downloaded:

ifeq ($(CONF_WIRELESS_UB94), y)
	@echo "Downloading Atheros UB94 from $(WIRELESS_UB94_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_UB94_SERVER_URL); \
	fi
	@echo "Downloading Atheros HostAP from $(ATHR_HOSTAP_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(ATHR_HOSTAP_SERVER_URL); \
	fi
endif
ifeq ($(CONF_WIRELESS_BCM4323), y)
	@echo "Downloading Broadcom BCM4323 from $(WIRELESS_BCM4323_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_BCM4323_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_RT2880), y)
	@echo "Downloading Ralink RT2880 from $(WIRELESS_RT2880_SERVER_URL)"
	@if [ ! -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_RT2880_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_RT2870), y)
	@echo "Downloading Ralink RT2870 from $(WIRELESS_RT2870_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_RT2870_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_RT2860), y)
	@echo "Downloading Ralink RT2860 from $(WIRELESS_RT2860_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_RT2860_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_RT3070), y)
	@echo "Downloading Ralink RT3070 from $(WIRELESS_RT3070_SERVER_URL)"
endif

ifeq ($(CONF_WIRELESS_RT3572), y)
	@echo "Downloading Ralink RT3572 from $(WIRELESS_RT3572_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_RT3572_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_AR9170), y)
	@echo "Downloading Atheros AR9170 from $(WIRELESS_AR9170_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_AR9170_SERVER_URL); \
	fi
endif

ifeq ($(CONF_WIRELESS_RTL8192), y)
	@echo "Downloading Realtek RTL8192 from $(WIRELESS_RTL8192_SERVER_URL)"
endif

ifeq ($(CONF_WIRELESS_RTL8712), y)
	@echo "Downloading Realtek RTL8712 from $(WIRELESS_RTL8712_SERVER_URL)"
	@if [ -d "$(WIRELESS_DRIVERS_DIR)" ]; then \
		cd $(WIRELESS_DRIVERS_DIR); \
		$(TOP_DOWNLOAD) $(WIRELESS_RTL8712_SERVER_URL); \
	fi
endif

	@echo "Downloading $(WIRELESS_DRIVERS_VERSION) done"
	@touch $@

#
# Unpack the source
#
.PHONY: wireless_drivers-unpacked

wireless_drivers-unpacked: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_unpacked

$(WIRELESS_DRIVERS_DIR)/.wireless_drivers_unpacked: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_downloaded
	@echo "Unpacking... wireless drivers ..."
	@touch $@


#
# Patch the source
#
.PHONY: wireless_drivers-patched

wireless_drivers-patched: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_patched

$(WIRELESS_DRIVERS_DIR)/.wireless_drivers_patched: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_unpacked
	@echo "Patching... wireless drivers ..."
	@touch $@

#
# config
#
.PHONY: wireless_drivers-config

wireless_drivers-config: 

#
# Configuration
#
.PHONY: wireless_drivers-configured

wireless_drivers-configured:  wireless_drivers-config $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_configured

$(WIRELESS_DRIVERS_DIR)/.wireless_drivers_configured: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_patched $(WIRELESS_DRIVERS_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring... wireless drivers ..."
	@touch $@

#
# Compile
#
.PHONY: wireless_drivers-compile

wireless_drivers-compile: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_compile

$(WIRELESS_DRIVERS_DIR)/.wireless_drivers_compile: $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_configured
	@echo "Compile wireless drivers ..."

ifeq ($(CONF_WIRELESS_UB94), y)
	@echo "Compiling Atheros UB94 & UB95"
	make -C $(WIRELESS_UB94_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
	make -C $(ATHR_HOSTAP_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_AR9170), y)
	@echo "Compiling Atheros AR9170"
	make -C $(WIRELESS_AR9170_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_BCM4323), y)
	@echo "Compiling Broadcom BCM4323"
	make -C $(WIRELESS_BCM4323_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RT2880), y)
	@echo "Compiling Ralink RT2880"
	make -C $(WIRELESS_RT2880_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RT2870), y)
	@echo "Compiling Ralink RT2870"
	make -C $(WIRELESS_RT2870_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RT2860), y)
	@echo "Compiling Ralink RT2860"
	make -C $(WIRELESS_RT2860_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RT3070), y)
	@echo "Compiling Ralink RT3070"
	make -C $(WIRELESS_RT3070_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RT3572), y)
	@echo "Compiling Ralink RT3572"
	make -C $(WIRELESS_RT3572_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RTL8192), y)
	@echo "Compiling Realtek RTL8192"
	make -C $(WIRELESS_RTL8192_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

ifeq ($(CONF_WIRELESS_RTL8712), y)
	@echo "Compiling Realtek RTL8712"
	make -C $(WIRELESS_RTL8712_SOURCE) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD)
endif

	@echo "Compiling wireless drivers down"
	@touch $@

#
# Update
#
.PHONY: wireless_drivers-update

wireless_drivers-update:
ifeq ($(CONF_WIRELESS_UB94), y)
	@echo "Updating Atheros UB94 & UB95 driver"
	@cd $(WIRELESS_UB94_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_UB94_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_UB94_SOURCE); \
	fi
	@cd $(ATHR_HOSTAP_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(ATHR_HOSTAP_SOURCE)" ]; then \
		$(TOP_UPDATE) $(ATHR_HOSTAP_SOURCE); \
	fi
	@echo "Updating UB94 done"
endif

ifeq ($(CONF_WIRELESS_BCM4323), y)
	@echo "Updating BCM4323 driver"
	@cd $(WIRELESS_BCM4323_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_BCM4323_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_BCM4323_SOURCE); \
	fi
	@echo "Updating BCM4323 done"
endif
ifeq ($(CONF_WIRELESS_RT2880), y)
	@echo "Updating RT2880 driver"
	@cd $(WIRELESS_RT2880_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RT2880_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RT2880_SOURCE); \
	fi
	@echo "Updating RT2880 done"
endif
ifeq ($(CONF_WIRELESS_RT2870), y)
	@echo "Updating RT2870 driver"
	@cd $(WIRELESS_RT2870_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RT2870_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RT2870_SOURCE); \
	fi
	@echo "Updating RT2870 done"
endif
ifeq ($(CONF_WIRELESS_RT2860), y)
	@echo "Updating RT2860 driver"
	@cd $(WIRELESS_RT2860_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RT2860_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RT2860_SOURCE); \
	fi
	@echo "Updating RT2860 done"
endif
ifeq ($(CONF_WIRELESS_RT3070), y)
	@echo "Updating RT3070 driver"
	@cd $(WIRELESS_RT3070_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RT3070_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RT3070_SOURCE); \
	fi
	@echo "Updating RT3070 done"
endif
ifeq ($(CONF_WIRELESS_RT3572), y)
	@echo "Updating RT3572 driver"
	@cd $(WIRELESS_RT3572_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RT3572_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RT3572_SOURCE); \
	fi
	@echo "Updating RT3572 done"
endif
ifeq ($(CONF_WIRELESS_AR9170), y)
	@echo "Updating AR9170 driver"
	@cd $(WIRELESS_AR9170_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_AR9170_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_AR9170_SOURCE); \
	fi
	@echo "Updating AR9170 done"
endif
ifeq ($(CONF_WIRELESS_RTL8192), y)
	@echo "Updating RTL8192 driver"
	@cd $(WIRELESS_RTL8192_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RTL8192_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RTL8192_SOURCE); \
	fi
	@echo "Updating RTL8192 done"
endif
ifeq ($(CONF_WIRELESS_RTL8712), y)
	@echo "Updating RTL8712 driver"
	@cd $(WIRELESS_RTL8712_SOURCE);$(TOP_UPDATE)
	@if [ -d "$(WIRELESS_RTL8712_SOURCE)" ]; then \
		$(TOP_UPDATE) $(WIRELESS_RTL8712_SOURCE); \
	fi
	@echo "Updating RTL8712 done"
endif


#
# Status
#
.PHONY: wireless_drivers-status

wireless_drivers-status:
ifeq ($(CONF_WIRELESS_UB94), y)
	@echo "Statusing Atheros UB94 & UB95 driver"
	@if [ -d "$(WIRELESS_UB94_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_UB94_SOURCE); \
	fi
	@if [ -d "$(ATHR_HOSTAP_SOURCE)" ]; then \
		$(TOP_STATUS) $(ATHR_HOSTAP_SOURCE); \
	fi
endif

ifeq ($(CONF_WIRELESS_BCM4323), y)
	@echo "Statusing Broadcom BCM4323 driver ..."
	@if [ -d "$(WIRELESS_BCM4323_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_BCM4323_SOURCE); \
	fi
endif
ifeq ($(CONF_WIRELESS_RT2880), y)
	@echo "Statusing RT2880 driver ..."
	@if [ -d "$(WIRELESS_RT2880_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RT2880_SOURCE); \
	fi
	@echo "Statusing RT2880 done"
endif
ifeq ($(CONF_WIRELESS_RT2870), y)
	@echo "Statusing RT2870 driver ..."
	@if [ -d "$(WIRELESS_RT2870_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RT2870_SOURCE); \
	fi
	@echo "Statusing RT2870 done"
endif
ifeq ($(CONF_WIRELESS_RT2860), y)
	@echo "Statusing RT2860 driver ..."
	@if [ -d "$(WIRELESS_RT2860_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RT2860_SOURCE); \
	fi
	@echo "Statusing RT2860 done"
endif
ifeq ($(CONF_WIRELESS_RT3070), y)
	@echo "Statusing RT3070 driver ..."
	@if [ -d "$(WIRELESS_RT3070_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RT3070_SOURCE); \
	fi
	@echo "Statusing RT3070 done"
endif
ifeq ($(CONF_WIRELESS_RT3572), y)
	@echo "Statusing RT3572 driver ..."
	@if [ -d "$(WIRELESS_RT3572_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RT3572_SOURCE); \
	fi
	@echo "Statusing RT3572 done"
endif
ifeq ($(CONF_WIRELESS_AR9170), y)
	@echo "Statusing AR9170 driver ..."
	@if [ -d "$(WIRELESS_AR9170_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_AR9170_SOURCE); \
	fi
	@echo "Statusing AR9170 done"
endif
ifeq ($(CONF_WIRELESS_RTL8192), y)
	@echo "Statusing RTL8192 driver ..."
	@if [ -d "$(WIRELESS_RTL8192_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RTL8192_SOURCE); \
	fi
	@echo "Statusing RTL8192 done"
endif
ifeq ($(CONF_WIRELESS_RTL8712), y)
	@echo "Statusing RTL8712 driver ..."
	@if [ -d "$(WIRELESS_RTL8712_SOURCE)" ]; then \
		$(TOP_STATUS) $(WIRELESS_RTL8712_SOURCE); \
	fi
	@echo "Statusing RTL8712 done"
endif

#
# Clean
#
.PHONY: wireless_drivers-clean

wireless_drivers-clean:
	@rm -f $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_configured
ifeq ($(CONF_WIRELESS_UB94), y)
	@if [ -d "$(WIRELESS_UB94_SOURCE)" ]; then \
		make -C $(WIRELESS_UB94_SOURCE) clean \
	fi
	@if [ -d "$(ATHR_HOSTAP_SOURCE)" ]; then \
		make -C $(ATHR_HOSTAP_SOURCE) clean \
	fi
endif
ifeq ($(CONF_WIRELESS_BCM4323), y)
	@if [ -d "$(WIRELESS_BCM4323_SOURCE)" ]; then \
		make -C $(WIRELESS_BCM4323_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RT2880), y)
	@if [ -d "$(WIRELESS_RT2880_SOURCE)" ]; then \
		make -C $(WIRELESS_RT2880_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RT2870), y)
	@if [ -d "$(WIRELESS_RT2870_SOURCE)" ]; then \
		make -C $(WIRELESS_RT2870_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RT2860), y)
	@if [ -d "$(WIRELESS_RT2860_SOURCE)" ]; then \
		make -C $(WIRELESS_RT2860_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RT3070), y)
	@if [ -d "$(WIRELESS_RT3070_SOURCE)" ]; then \
		make -C $(WIRELESS_RT3070_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RT3572), y)
	@if [ -d "$(WIRELESS_RT3572_SOURCE)" ]; then \
		make -C $(WIRELESS_RT3572_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_AR9170), y)
	@if [ -d "$(WIRELESS_AR9170_SOURCE)" ]; then \
		make -C $(WIRELESS_AR9170_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RTL8192), y)
	@if [ -d "$(WIRELESS_RTL8192_SOURCE)" ]; then \
		make -C $(WIRELESS_RTL8192_SOURCE) clean; \
	fi
endif
ifeq ($(CONF_WIRELESS_RTL8712), y)
	@if [ -d "$(WIRELESS_RTL8712_SOURCE)" ]; then \
		make -C $(WIRELESS_RTL8712_SOURCE) clean; \
	fi
endif

#
# Dist clean
#
.PHONY: wireless_drivers-distclean

wireless_drivers-distclean:
	@rm -f $(WIRELESS_DRIVERS_DIR)/.wireless_drivers_*

#
# Install
#
.PHONY: wireless_drivers-install

wireless_drivers-install:
ifeq ($(CONF_WIRELESS_UB94), y)
	@if [ -d "$(WIRELESS_UB94_SOURCE)" ]; then \
		@echo "Installing Atheros UB94";	\
		make -C $(WIRELESS_UB94_SOURCE) install;	\
		make -C $(ATHR_HOSTAP_SOURCE) install;	\
	fi
endif
ifeq ($(CONF_WIRELESS_BCM4323), y)
	@if [ -d "$(WIRELESS_BCM4323_SOURCE)" ]; then \
		@echo "Installing Broadcom BCM4323";	\
		make -C $(WIRELESS_BCM4323_SOURCE) install;	\
	fi
endif
ifeq ($(CONF_WIRELESS_RT2880), y)
	@if [ -d "$(WIRELESS_RT2880_SOURCE)" ]; then \
		@echo "Installing Ralink RT2880";	\
		make -C $(WIRELESS_RT2880_SOURCE) install;	\
	fi
endif

ifeq ($(CONF_WIRELESS_RT2870), y)
	@if [ -d "$(WIRELESS_RT2870_SOURCE)" ]; then \
		@echo "Installing Ralink RT2870";	\
		make -C $(WIRELESS_RT2870_SOURCE) install;	\
	fi
endif

ifeq ($(CONF_WIRELESS_RT2860), y)
	@if [ -d "$(WIRELESS_RT2860_SOURCE)" ]; then \
		@echo "Installing Ralink RT2860";	\
		make -C $(WIRELESS_RT2860_SOURCE) install;	\
	fi
endif
	
ifeq ($(CONF_WIRELESS_RT3070), y)
	@if [ -d "$(WIRELESS_RT3070_SOURCE)" ]; then \
		@echo "Installing Ralink RT3070";	\
		make -C $(WIRELESS_RT3070_SOURCE) install;	\
	fi
endif

ifeq ($(CONF_WIRELESS_RT3572), y)
	@if [ -d "$(WIRELESS_RT3572_SOURCE)" ]; then \
		@echo "Installing Ralink RT3572";	\
		make -C $(WIRELESS_RT3572_SOURCE) install;	\
	fi
endif

ifeq ($(CONF_WIRELESS_AR9170), y)
	@if [ -d "$(WIRELESS_AR9170_SOURCE)" ]; then \
		@echo "Installing Atheros AR9170";	\
		make -C $(WIRELESS_AR9170_SOURCE) install;	\
	fi
endif
ifeq ($(CONF_WIRELESS_RTL8192), y)
	@if [ -d "$(WIRELESS_RTL8192_SOURCE)" ]; then \
		@echo "Installing Realtek";	\
		make -C $(WIRELESS_RTL8192_SOURCE) install;	\
	fi
endif
ifeq ($(CONF_WIRELESS_RTL8712), y)
	@if [ -d "$(WIRELESS_RTL8712_SOURCE)" ]; then \
		@echo "Installing Realtek";	\
		make -C $(WIRELESS_RTL8712_SOURCE) install;	\
	fi
endif

	@echo "Install wireless drivers done"
