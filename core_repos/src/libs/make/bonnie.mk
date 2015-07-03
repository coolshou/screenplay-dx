#
# Defines
#
ifndef  CONF_BONNIE_VERSION 
CONF_BONNIE_VERSION := 1.03e# 
endif

BONNIE             := bonnie++-$(CONF_BONNIE_VERSION)#
BONNIE_SERVER_URL  := $(TOP_LIBS_URL)/bonnie++/$(BONNIE)
BONNIE_DIR         := $(TOP_LIBS_DIR)#
BONNIE_SOURCE      := $(BONNIE_DIR)/$(BONNIE)
BONNIE_CONFIG      := 

#
# Download  the source 
#
.PHONY: bonnie-downloaded

bonnie-downloaded: $(BONNIE_DIR)/.bonnie_downloaded

$(BONNIE_DIR)/.bonnie_downloaded:
	@echo "Downloading $(BONNIE) from $(BONNIE_SERVER_URL) ..."
	@if [ ! -d "$(BONNIE_SOURCE)" ]; then \
		cd $(BONNIE_DIR); \
		$(TOP_DOWNLOAD) $(BONNIE_SERVER_URL); \
	fi
	@echo "Downloading $(BONNIE) from $(BONNIE_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: bonnie-unpacked

bonnie-unpacked: $(BONNIE_DIR)/.bonnie_unpacked

$(BONNIE_DIR)/.bonnie_unpacked: $(BONNIE_DIR)/.bonnie_downloaded $(BONNIE_SOURCE)/$(BONNIE).tgz
	@echo "Unpacking $(BONNIE) ..."
	if [ -d "$(BONNIE_SOURCE)/$(BONNIE)" ]; then \
		rm -fr $(BONNIE_SOURCE)/$(BONNIE); \
	fi
	cd $(BONNIE_SOURCE); tar xzvf $(BONNIE).tgz
	@echo "Unpacking $(BONNIE) done"
	@touch $@


#
# Patch the source
#
.PHONY: bonnie-patched

bonnie-patched: $(BONNIE_DIR)/.bonnie_patched

$(BONNIE_DIR)/.bonnie_patched: $(BONNIE_DIR)/.bonnie_unpacked
	@touch $@

#
# config
#
.PHONY: bonnie-config

bonnie-config: 

#
# Configuration
#
.PHONY: bonnie-configured

bonnie-configured:  bonnie-config $(BONNIE_DIR)/.bonnie_configured

$(BONNIE_DIR)/.bonnie_configured: $(BONNIE_DIR)/.bonnie_patched $(BONNIE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(BONNIE) ..."
	cd $(BONNIE_SOURCE)/$(BONNIE); 	./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) 
	@echo "Configuring $(BONNIE) done"
	@touch $@

#
# Compile
#
.PHONY: bonnie-compile

bonnie-compile: $(BONNIE_DIR)/.bonnie_compiled

$(BONNIE_DIR)/.bonnie_compiled: $(BONNIE_DIR)/.bonnie_configured
	@echo "Compiling $(BONNIE) ..."
	make -C $(BONNIE_SOURCE)/$(BONNIE)
	@echo "Compiling $(BONNIE) done"
	@touch $@

#
# Update
#
.PHONY: bonnie-update

bonnie-update:
	@echo "Updating $(BONNIE) ..."
	@if [ -d "$(BONNIE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(BONNIE_SOURCE); \
	fi
	@echo "Updating $(BONNIE) done"

#
# Status
#
.PHONY: bonnie-status

bonnie-status:
	@echo "Statusing $(BONNIE) ..."
	@if [ -d "$(BONNIE_SOURCE)" ]; then\
		$(TOP_STATUS) $(BONNIE_SOURCE); \
	fi
	@echo "Statusing $(BONNIE) done"

#
# Clean
#
.PHONY: bonnie-clean

bonnie-clean:
	@rm -f $(BONNIE_DIR)/.bonnie_configured
	@if [ -d "$(BONNIE_SOURCE)" ]; then\
		make -C $(BONNIE_SOURCE)/$(BONNIE) clean; \
	fi

#
# Dist clean
#
.PHONY: bonnie-distclean

bonnie-distclean:
	@rm -f $(BONNIE_DIR)/.bonnie_*
#@rm -fr $(BONNIE_SOURCE)

#
# Install
#
.PHONY: bonnie-install

bonnie-install:
	cp -f $(BONNIE_SOURCE)/$(BONNIE)/bonnie++ $(TOP_INSTALL_ROOTFS_DIR)/bin

