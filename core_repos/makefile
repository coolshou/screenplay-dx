TOP = $(shell pwd)
export TOP

PREREQS	:= init
SUBDIRS = src

include $(TOP)/Target.mk
ifneq (x$(TOP_SCRIPTS_DIR),x)
include $(TOP_SCRIPTS_DIR)/rules.mk
endif

.PHONY: init
init: scripts/kconfig/mconf scripts/kconfig/lxdialog/lxdialog .config Target.h Target.options 

scripts/kconfig/mconf: 
	make -C scripts/kconfig/

scripts/kconfig/lxdialog/lxdialog:
	make -C scripts/kconfig/lxdialog

.config:
	@if [ ! -f .config ]; then	\
		echo "";\
		echo "Use default configuration";	\
		echo "";\
		echo "	1. WDTV_HOUSE_smp8634 (WD UI)"; \
		echo "	2. WDTV_HOUSE_smp8634 (ALPHA_UI)";\
		echo "	3. WDTV PENTHOUSE(HUT) smp8654 (WD UI)";\
		echo "	4. WDTV PENTHOUSE(HUT) smp8654 (ALPHA_UI)";\
		echo "	5. WDTV x86 (WD UI)";\
		echo "	6. WDTV_VILLA_smp8654_WD_UI (256MB flash)";\
		echo "	7. WDTV_BUNGALOW_smp8654_WD_UI (Netflix)";\
		echo "	8. WDTV_RV With alpha board";\
		echo "	9. LaCinema Mediaplayer ";\
		echo "	10. LaCinema DMA (with miniPCI) ";\
		echo "	11. IODATA_AVLS700L_smp8654_UI";\
		echo "	12. BEWAN_IMEDIAHD100_smp8654_UI";\
		echo "";\
	fi;
	@read -p "Please select a default config: ";\
	if [ x$$REPLY == x1 ]; then	\
		cp config/default_config_WDTV_HOUSE_smp8634_wistron .config;\
	fi;\
	if [ x$$REPLY == x2 ]; then	\
		cp config/default_config_WDTV_HOUSE_smp8634_ALPHA_UI .config;\
	fi;\
	if [ x$$REPLY == x3 ]; then	\
		cp config/default_config_WDTV_HUT_smp8654_wistron .config;\
	fi;\
	if [ x$$REPLY == x4 ]; then	\
		cp config/default_config_WDTV_HUT_smp8654_ALPHA_UI .config;\
	fi;\
	if [ x$$REPLY == x5 ]; then	\
		cp config/default_config_WDTV_x86 .config;\
	fi;\
	if [ x$$REPLY == x6 ]; then	\
		cp config/default_config_WDTV_VILLA_smp8654_WD_UI_D2 .config;\
	fi;\
	if [ x$$REPLY == x7 ]; then	\
		cp config/default_config_WDTV_BUNGALOW_smp8654_WD_UI_D2 .config;\
	fi;\
	if [ x$$REPLY == x8 ]; then	\
		cp config/default_config_WDTV_RV_smp8654_ALPHA_BOARD .config;\
	fi;\
	if [ x$$REPLY == x9 ]; then	\
		cp config/default_config_LMP555 .config;\
	fi;\
	if [ x$$REPLY == x10 ]; then	\
		cp config/default_config_LMP555_DMA .config;\
	fi;\
	if [ x$$REPLY == x11 ]; then	\
		cp config/default_config_AV-LS700L_UI .config;\
	fi;\
	if [ x$$REPLY == x12 ]; then	\
		cp config/default_config_IMEDIA_HD100 .config;\
	fi;\
	sed '/SECURITY_USE_CPU_BINDING/d' .config > .config.tmp && mv -f .config.tmp .config; \
	make oldconfig

include $(TOP_SCRIPTS_DIR)/Target.mk

.PHONY: oldconfig
oldconfig:
	./scripts/kconfig/conf -o Config.in
	make Target.h 
	make Target.options

.PHONY: menuconfig
menuconfig: init
	./scripts/kconfig/mconf Config.in
	make Target.h 
	make Target.options

.PHONY:	install
install:
#rm -rf $(TOP_INSTALL_ROOTFS_DIR)
#mkdir -p $(TOP_INSTALL_ROOTFS_DIR)
#rm -rf $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)
#mkdir -p $(TOP_INSTALL_ROOTFS_PRIMARY_SYSTEM_DIR)
	make -C $(TOP_MISC_DIR) install
ifeq (x$(CONF_SUPPORT_VIRTUAL_REMOTE),xy)
	make -C $(TOP_SRC_DIR)/vremote install
endif
	make -C $(TOP_LIBS_DIR) install
 
rootfs: init
	make install

update up: init
	@echo "Updating the core_repos ..."	
	$(TOP_UPDATE);
	@echo "Updating the core_repos done"
	
	@echo "Updating the external libs ..."
	make -C $(TOP_LIBS_DIR) update
	@echo "Updating the external libs done" 

status st: init
	@$(TOP_STATUS);
	@make -C $(TOP_LIBS_DIR) status

ifneq (x$(CONF_FIRMWARE_SCRIPT),x)
include $(TOP_SCRIPTS_DIR)/$(CONF_FIRMWARE_SCRIPT)
endif


