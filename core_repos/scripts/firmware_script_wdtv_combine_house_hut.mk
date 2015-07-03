
FWO2_DIR	=	$(TOP_BUILD_DIR)/fwo2
FWO2_ROOT	=	$(FWO2_DIR)/root
HOUSE_DIR	=	$(FWO2_DIR)/house
HUT_DIR		=	$(FWO2_DIR)/hut
MKFW		=	$(TOP_BUILD_DIR)/host/bin/mkfw

fwo2:
	@echo -e "\E[1;33mFirmware version of House used is " $(CONF_VERSION) " \E[0m"
	@rm -rf $(FWO2_DIR)
	@mkdir -p $(FWO2_DIR)
	@if [ ! -d $(HOUSE_DIR) ]; then	\
		(cd $(FWO2_DIR); $(TOP_DOWNLOAD) $(TOP_RELEASE_URL)/house_$(CONF_VERSION)/ house);\
	fi
	@echo -e "\E[1;33mFirmware version of Hut used is " $(CONF_VERSION) " \E[0m"
	@if [ ! -d $(HUT_DIR) ]; then \
		(cd $(FWO2_DIR); $(TOP_DOWNLOAD) $(TOP_RELEASE_URL)/hut_$(CONF_VERSION)/ hut);\
	fi
	$(MKFW) $(FWO2_DIR)/combo 1 $(HOUSE_DIR)/romfs.bin 2 $(HUT_DIR)/romfs.bin
	md5sum $(FWO2_DIR)/combo > $(FWO2_DIR)/fw_md5
	dd if=$(FWO2_DIR)/fw_md5 of=$(FWO2_DIR)/$(CONF_FIRMWARE_BIN_FILE) bs=1 count=32
	cat $(FWO2_DIR)/combo >> $(FWO2_DIR)/$(CONF_FIRMWARE_BIN_FILE)
	echo VERSION=\'$(CONF_VERSION)\' > $(FWO2_DIR)/$(CONF_FIRMWARE_VER_FILE) 
	echo LOCATION=\'wdtv.bin\' >> $(FWO2_DIR)/$(CONF_FIRMWARE_VER_FILE)

