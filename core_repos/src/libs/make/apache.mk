#
# Defines
#
ifndef  CONF_APACHE_VERSION 
CONF_APACHE_VERSION := 1.3.42#
endif

APACHE             := apache_$(CONF_APACHE_VERSION)#
APACHE_SERVER_URL  := $(TOP_LIBS_URL)/apache/$(APACHE)
APACHE_DIR         := $(TOP_LIBS_DIR)#
APACHE_SOURCE      := $(APACHE_DIR)/$(APACHE)
APACHE_CONFIG      := 

#
# Download  the source 
#
.PHONY: apache-downloaded

apache-downloaded: $(APACHE_DIR)/.apache_downloaded

$(APACHE_DIR)/.apache_downloaded:
	@echo "Downloading $(APACHE) from $(APACHE_SERVER_URL) ..."
	@if [ ! -d "$(APACHE_SOURCE)" ]; then \
		cd $(APACHE_DIR); \
		$(TOP_DOWNLOAD) $(APACHE_SERVER_URL); \
	fi
	@echo "Downloading $(APACHE) from $(APACHE_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: apache-unpacked

apache-unpacked: $(APACHE_DIR)/.apache_unpacked

$(APACHE_DIR)/.apache_unpacked: $(APACHE_DIR)/.apache_downloaded $(APACHE_SOURCE)/$(APACHE).tar.gz
	@echo "Unpacking $(APACHE) ..."
	if [ -d "$(APACHE_SOURCE)/$(APACHE)" ]; then \
		rm -fr $(APACHE_SOURCE)/$(APACHE); \
	fi
	cd $(APACHE_SOURCE); tar xzvf $(APACHE).tar.gz
	@echo "Unpacking $(APACHE) done"
	@touch $@


#
# Patch the source
#
.PHONY: apache-patched

apache-patched: $(APACHE_DIR)/.apache_patched

$(APACHE_DIR)/.apache_patched: $(APACHE_DIR)/.apache_unpacked
	cd $(APACHE_SOURCE); patch -p0 < pre_compile_patch
	cd $(APACHE_SOURCE)/$(APACHE); sed -i -e "s,^root[ ]*=,root=$(LIBS_INSTALL_PATH)", Makefile.tmpl
	@touch $@

#
# config
#
.PHONY: apache-config

apache-config: 

#
# Configuration
#
.PHONY: apache-configured

apache-configured:  apache-config $(APACHE_DIR)/.apache_configured

$(APACHE_DIR)/.apache_configured: $(APACHE_DIR)/.apache_patched $(APACHE_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(APACHE) ..."
	cd $(APACHE_SOURCE)/$(APACHE);./configure  --prefix=$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)
	@echo "Configuring $(APACHE) done"
	@touch $@

#
# Compile
#
.PHONY: apache-compile

apache-compile: $(APACHE_DIR)/.apache_compiled

$(APACHE_DIR)/.apache_compiled: $(APACHE_DIR)/.apache_configured
	@echo "Compiling $(APACHE) ..."
	make -C $(APACHE_SOURCE)/$(APACHE)
	make -C $(APACHE_SOURCE)/$(APACHE)  install
	@echo "Compiling $(APACHE) done"
	@touch $@

#
# Update
#
.PHONY: apache-update

apache-update:
	@echo "Updating $(APACHE) ..."
	@if [ -d "$(APACHE_SOURCE)" ]; then\
		$(TOP_UPDATE) $(APACHE_SOURCE); \
	fi
	@echo "Updating $(APACHE) done"

#
# Status
#
.PHONY: apache-status

apache-status:
	@echo "Statusing $(APACHE) ..."
	@if [ -d "$(APACHE_SOURCE)" ]; then\
		$(TOP_STATUS) $(APACHE_SOURCE); \
	fi
	@echo "Statusing $(APACHE) done"

#
# Clean
#
.PHONY: apache-clean

apache-clean:
	@rm -f $(APACHE_DIR)/.apache_configured
	@if [ -d "$(APACHE_SOURCE)" ]; then\
		make -C $(APACHE_SOURCE)/$(APACHE) clean; \
	fi

#
# Dist clean
#
.PHONY: apache-distclean

apache-distclean:
	@rm -f $(APACHE_DIR)/.apache_*
#@rm -fr $(APACHE_SOURCE)

#
# Install
#
.PHONY: apache-install

apache-install:
	cp -ra $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH) $(TOP_INSTALL_ROOTFS_DIR)
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/htdocs/*
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/man
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/include
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/icons
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/*.default
	sed -i -e "s,Group nogroup,Group\ \"\#\-1\"," $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/httpd.conf
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/ab
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/checkgid
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htdigest
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htpasswd
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/httpd
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/logresolve
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/rotatelogs


