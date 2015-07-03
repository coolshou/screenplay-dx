#
# Defines
#
ifndef  CONF_FONTCONFIG_VERSION
CONF_FONTCONFIG_VERSION := 2.8.0
endif

FONTCONFIG             := fontconfig-$(CONF_FONTCONFIG_VERSION)#
FONTCONFIG_SERVER_URL  := $(TOP_LIBS_URL)/fontconfig/$(FONTCONFIG)
FONTCONFIG_DIR         := $(TOP_LIBS_DIR)#
FONTCONFIG_SOURCE      := $(FONTCONFIG_DIR)/$(FONTCONFIG)
FONTCONFIG_CONFIG      :=

#
# Download  the source 
#
.PHONY: fontconfig-downloaded

fontconfig-downloaded: $(FONTCONFIG_DIR)/.fontconfig_downloaded

$(FONTCONFIG_DIR)/.fontconfig_downloaded:
	@echo "Downloading $(FONTCONFIG) from $(FONTCONFIG_SERVER_URL) ..."
	@if [ ! -d "$(FONTCONFIG_SOURCE)" ]; then \
		cd $(FONTCONFIG_DIR); \
		$(TOP_DOWNLOAD) $(FONTCONFIG_SERVER_URL); \
	fi
	@echo "Downloading $(FONTCONFIG) done" 
	@touch $@

#
# Unpack the source
#
.PHONY: fontconfig-unpacked

fontconfig-unpacked: $(FONTCONFIG_DIR)/.fontconfig_unpacked

$(FONTCONFIG_DIR)/.fontconfig_unpacked: $(FONTCONFIG_DIR)/.fontconfig_downloaded $(wildcard $(FONTCONFIG_SOURCE)/*.tar.*)
	@echo "Unpacking $(FONTCONFIG) ..."
	if [ -d "$(FONTCONFIG_SOURCE)/$(FONTCONFIG)" ]; then \
		rm -fr $(FONTCONFIG_SOURCE)/$(FONTCONFIG); \
	fi
	@cd $(FONTCONFIG_SOURCE); \
	if [ -f $(FONTCONFIG).tar.bz2 ]; then \
		tar jxvf  $(FONTCONFIG).tar.bz2 ; \
	elif [ -f  $(FONTCONFIG).tar.gz ]; then \
		tar zxvf  $(FONTCONFIG).tar.gz ; \
	else \
		(echo "No standard Freetype Library"; error) ; \
	fi
	@echo "Unpacking $(FONTCONFIG) done" 
	@touch $@


#
# Patch the source
#
.PHONY: fontconfig-patched

fontconfig-patched: $(FONTCONFIG_DIR)/.fontconfig_patched

$(FONTCONFIG_DIR)/.fontconfig_patched: $(FONTCONFIG_DIR)/.fontconfig_unpacked
	# Patching...
	@echo "Patching $(FONTCONFIG) ..."
	cd  $(FONTCONFIG_SOURCE); patch -p0 < ignore_fccache_check_timestamp.patch;
	@echo "Patching $(FONTCONFIG) done"
	@touch $@

#
# config
#
.PHONY: fontconfig-config

fontconfig-config: 

#
# Configuration
#
.PHONY: fontconfig-configured

fontconfig-configured:  fontconfig-config $(FONTCONFIG_DIR)/.fontconfig_configured

$(FONTCONFIG_DIR)/.fontconfig_configured: $(FONTCONFIG_DIR)/.fontconfig_patched $(FONTCONFIG_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(FONTCONFIG) ..."
	cd $(FONTCONFIG_SOURCE)/$(FONTCONFIG);./autogen.sh;PKG_CONFIG_PATH="$(LIBS_INSTALL_PATH)/lib/pkgconfig" CC=$(CC) AR=$(CROSS)ar RANLIB=$(CROSS)ranlib LD=$(LD) CFLAGS="-I$(LIBS_INSTALL_PATH)/include" ./configure --prefix=$(LIBS_INSTALL_PATH)  --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --target=$(BUILD_TARGET) --with-arch=mips --enable-shared=$(ENABLE_SHLIB) --with-freetype-config=$(SYSLIB_PREFIX)/bin/freetype-config --enable-libxml2 --disable-docs
	@echo "Configuring $(FONTCONFIG) done"
	@touch $@

#
# Compile
#
.PHONY: fontconfig-compile

fontconfig-compile: $(FONTCONFIG_DIR)/.fontconfig_compiled

$(FONTCONFIG_DIR)/.fontconfig_compiled: $(FONTCONFIG_DIR)/.fontconfig_configured
	@echo "Compiling $(FONTCONFIG) ..."
	make -C $(FONTCONFIG_SOURCE)/$(FONTCONFIG)
	make -C $(FONTCONFIG_SOURCE)/$(FONTCONFIG) install
	@echo "Compiling $(FONTCONFIG) done"
	@touch $@

#
# Update
#
.PHONY: fontconfig-update

fontconfig-update:
	@echo "Updating $(FONTCONFIG) ..."
	@if [ -d "$(FONTCONFIG_SOURCE)" ]; then\
		$(TOP_UPDATE) $(FONTCONFIG_SOURCE); \
	fi
	@echo "Updating $(FONTCONFIG) done"

#
# Status
#
.PHONY: fontconfig-status

fontconfig-status:
	@echo "Statusing $(FONTCONFIG) ..."
	@if [ -d "$(FONTCONFIG_SOURCE)" ]; then\
		$(TOP_STATUS) $(FONTCONFIG_SOURCE); \
	fi
	@echo "Statusing $(FONTCONFIG) done"

#
# Clean
#
.PHONY: fontconfig-clean

fontconfig-clean:
	@rm -f $(FONTCONFIG_DIR)/.fontconfig_configured
	@if [ -d "$(FONTCONFIG_SOURCE)" ]; then\
		make -C $(FONTCONFIG_SOURCE)/$(FONTCONFIG) clean; \
	fi

#
# Dist clean
#
.PHONY: fontconfig-distclean

fontconfig-distclean:
	@rm -f $(FONTCONFIG_DIR)/.fontconfig_*

#
# Install
#
.PHONY: fontconfig-install

fontconfig-install:
