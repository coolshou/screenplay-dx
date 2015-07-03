#
# Defines
#
ifndef  CONF_LIBICONV_VERSION 
CONF_LIBICONV_VERSION := 1.12
endif

LIBICONV             := libiconv-$(CONF_LIBICONV_VERSION)#
LIBICONV_SERVER_URL  := $(TOP_LIBS_URL)/libiconv/$(LIBICONV)
LIBICONV_DIR         := $(TOP_LIBS_DIR)#
LIBICONV_SOURCE      := $(LIBICONV_DIR)/$(LIBICONV)
LIBICONV_CONFIG      := 


#
# Download  the source 
#
.PHONY: libiconv-downloaded

libiconv-downloaded: $(LIBICONV_DIR)/.libiconv_downloaded

$(LIBICONV_DIR)/.libiconv_downloaded:
	@echo "Downloading $(LIBICONV) from $(LIBICONV_SERVER_URL) ..."
	@if [ ! -d "$(LIBICONV_SOURCE)" ]; then \
		cd $(LIBICONV_DIR); \
		$(TOP_DOWNLOAD) $(LIBICONV_SERVER_URL); \
	fi
	@echo "Downloading $(LIBICONV) done"
	@touch $@

#
# Unpack the source
#
.PHONY: libiconv-unpacked

libiconv-unpacked: $(LIBICONV_DIR)/.libiconv_unpacked

$(LIBICONV_DIR)/.libiconv_unpacked: $(LIBICONV_DIR)/.libiconv_downloaded $(LIBICONV_SOURCE)/$(LIBICONV).tar.gz
	@echo "Unpacking $(LIBICONV) ..."
	if [ -d "$(LIBICONV_SOURCE)/$(LIBICONV)" ]; then \
		rm -fr  $(LIBICONV_SOURCE)/$(LIBICONV); \
	fi
	cd $(LIBICONV_SOURCE); tar zxvf $(LIBICONV).tar.gz
	@echo "Unpacking $(LIBICONV) done"
	@touch $@


#
# Patch the source
#
.PHONY: libiconv-patched

libiconv-patched: $(LIBICONV_DIR)/.libiconv_patched

$(LIBICONV_DIR)/.libiconv_patched: $(LIBICONV_DIR)/.libiconv_unpacked
	# Patching...
	@touch $@

#
# config
#
.PHONY: libiconv-config

libiconv-config: 

#
# Configuration
#
.PHONY: libiconv-configured

libiconv-configured:  libiconv-config $(LIBICONV_DIR)/.libiconv_configured

$(LIBICONV_DIR)/.libiconv_configured: $(LIBICONV_DIR)/.libiconv_patched $(LIBICONV_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configring  $(LIBICONV) ..."
	cd $(LIBICONV_SOURCE)/$(LIBICONV);./configure --prefix=$(LIBS_INSTALL_PATH) --build=$(BUILD_HOST) --host=$(BUILD_TARGET) --enable-shared=$(ENABLE_SHLIB) LDFLAGS="-L$(LIBS_INSTALL_PATH)/lib"
	@echo "Configring  $(LIBICONV) done" 
	@touch $@

#
# Compile
#
.PHONY: libiconv-compile

libiconv-compile: $(LIBICONV_DIR)/.libiconv_compiled

$(LIBICONV_DIR)/.libiconv_compiled: $(LIBICONV_DIR)/.libiconv_configured
	@echo "Compiling $(LIBICONV) ..." 
	make -C $(LIBICONV_SOURCE)/$(LIBICONV) CC=$(CC) AR=$(AR) RANLIB=$(RANLIB) STRIP=$(CROSS)strip LD=$(LD) CFLAGS="-I$(LIBS_INSTALL_PATH)/include"
	make -C $(LIBICONV_SOURCE)/$(LIBICONV) install
	rm -f $(LIBS_INSTALL_PATH)/lib/preloadable_libiconv.so
	@echo "Compiling $(LIBICONV) done"
	@touch $@
#
# Update
#
.PHONY: libiconv-update

libiconv-update:
	@echo "Updating $(LIBICONV) ..."
	@if [ -d "$(LIBICONV_SOURCE)" ]; then\
		$(TOP_UPDATE) $(LIBICONV_SOURCE); \
	fi
	@echo "Updating $(LIBICONV) done"

#
# Status
#
.PHONY: libiconv-status

libiconv-status:
	@echo "Statusing $(LIBICONV) ..."
	@if [ -d "$(LIBICONV_SOURCE)" ]; then\
		$(TOP_STATUS) $(LIBICONV_SOURCE); \
	fi
	@echo "Statusing $(LIBICONV) done"

#
# Clean
#
.PHONY: libiconv-clean

libiconv-clean:
	@rm -f $(LIBICONV_DIR)/.libiconv_configured
	@if [ -d "$(LIBICONV_SOURCE)" ]; then\
		make -C $(LIBICONV_SOURCE)/$(LIBICONV) clean; \
	fi

#
# Dist clean
#
.PHONY: libiconv-distclean

libiconv-distclean:
	@rm -f $(LIBICONV_DIR)/.libiconv_*

#
# Install
#
.PHONY: libiconv-install

libiconv-install:
