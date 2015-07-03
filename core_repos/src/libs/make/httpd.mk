#
# Defines
#
ifndef  CONF_HTTPD_VERSION 
CONF_HTTPD_VERSION := 2.2.11#
endif

HTTPD             := httpd-$(CONF_HTTPD_VERSION)#
HTTPD_SERVER_URL  := $(TOP_LIBS_URL)/httpd/$(HTTPD)
HTTPD_DIR         := $(TOP_LIBS_DIR)#
HTTPD_SOURCE      := $(HTTPD_DIR)/$(HTTPD)
HTTPD_CONFIG      := 

#
# Download  the source 
#
.PHONY: httpd-downloaded

httpd-downloaded: $(HTTPD_DIR)/.httpd_downloaded

$(HTTPD_DIR)/.httpd_downloaded:
	@echo "Downloading $(HTTPD) from $(HTTPD_SERVER_URL) ..."
	@if [ ! -d "$(HTTPD_SOURCE)" ]; then \
		cd $(HTTPD_DIR); \
		$(TOP_DOWNLOAD) $(HTTPD_SERVER_URL); \
	fi
	@echo "Downloading $(HTTPD) from $(HTTPD_SERVER_URL) done"
	@touch $@

#
# Unpack the source
#
.PHONY: httpd-unpacked

httpd-unpacked: $(HTTPD_DIR)/.httpd_unpacked

$(HTTPD_DIR)/.httpd_unpacked: $(HTTPD_DIR)/.httpd_downloaded $(HTTPD_SOURCE)/$(HTTPD).tar.bz2
	@echo "Unpacking $(HTTPD) ..."
	if [ -d "$(HTTPD_SOURCE)/$(HTTPD)" ]; then \
		rm -fr $(HTTPD_SOURCE)/$(HTTPD); \
	fi
	cd $(HTTPD_SOURCE); tar xjvf $(HTTPD).tar.bz2
	@echo "Unpacking $(HTTPD) done"
	@touch $@


#
# Patch the source
#
.PHONY: httpd-patched

httpd-patched: $(HTTPD_DIR)/.httpd_patched

$(HTTPD_DIR)/.httpd_patched: $(HTTPD_DIR)/.httpd_unpacked
	cd $(HTTPD_SOURCE); patch -p0 < $(HTTPD).patch
	@touch $@

#
# config
#
.PHONY: httpd-config

httpd-config: 

#
# Configuration
#
.PHONY: httpd-configured

httpd-configured:  httpd-config $(HTTPD_DIR)/.httpd_configured

$(HTTPD_DIR)/.httpd_configured: $(HTTPD_DIR)/.httpd_patched $(HTTPD_CONFIG) $(TOP_CURRENT_SET)
	@echo "Configuring $(HTTPD) ..."
ifeq (x$(CONF_SUPPORT_VIRTUAL_REMOTE), x)
	cd $(HTTPD_SOURCE)/$(HTTPD);./configure \
		--prefix=$(CONF_WEB_SERVER_APACHE_INSTALL_PATH) \
		--build=$(BUILD_HOST) \
		--host=$(BUILD_TARGET) \
		--target=$(BUILD_TARGET) \
		--enable-so \
		--enable-static-support \
		--enable-cgi \
		--enable-rewrite \
		--enable-auth-digest \
		--disable-suexec \
		--with-mpm=prefork
else
	cd $(HTTPD_SOURCE)/$(HTTPD);./configure \
		--prefix=$(CONF_WEB_SERVER_APACHE_INSTALL_PATH) \
		--build=$(BUILD_HOST) \
		--host=$(BUILD_TARGET) \
		--target=$(BUILD_TARGET) \
		--enable-so \
		--enable-static-support \
		--enable-cgi \
		--enable-rewrite \
		--enable-auth-digest \
		--disable-suexec \
		--with-mpm=prefork \
		CFLAGS=-DBIG_SECURITY_HOLE
endif
	@echo "Configuring $(HTTPD) done"
	@touch $@

#
# Compile
#
.PHONY: httpd-compile

httpd-compile: $(HTTPD_DIR)/.httpd_compiled

$(HTTPD_DIR)/.httpd_compiled: $(HTTPD_DIR)/.httpd_configured
	@echo "Compiling $(HTTPD) ..."
	make -C $(HTTPD_SOURCE)/$(HTTPD)
	export DESTDIR=$(LIBS_INSTALL_PATH) ;make -C $(HTTPD_SOURCE)/$(HTTPD)  install
	cd $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin; patch -p0 < $(HTTPD_SOURCE)/apxs.patch 
	sed -i -e s,my\ \$$installbuilddir.*,my\ \$$installbuilddir=\"$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/build\"\;, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/apxs
	sed -i -e s,^APR_BINDIR.*,APR_BINDIR=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/bin, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^APR_INCLUDEDIR.*,APR_INCLUDEDIR=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/include, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^APR_CONFIG.*,APR_CONFIG=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/bin/apr-1-config, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^APU_BINDIR.*,APU_BINDIR=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/bin, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^APU_INCLUDEDIR.*,APU_INCLUDEDIR=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/include, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^APU_CONFIG.*,APU_CONFIG=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/bin/apu-1-config, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/config_vars.mk
	sed -i -e s,^SH_LIBTOOL.*,SH_LIBTOOL=$(LIBS_INSTALL_PATH)\/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)\/build/libtool, $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build/instdso.sh


	@echo "Compiling $(HTTPD) done"
	@touch $@

#
# Update
#
.PHONY: httpd-update

httpd-update:
	@echo "Updating $(HTTPD) ..."
	@if [ -d "$(HTTPD_SOURCE)" ]; then\
		$(TOP_UPDATE) $(HTTPD_SOURCE); \
	fi
	@echo "Updating $(HTTPD) done"

#
# Status
#
.PHONY: httpd-status

httpd-status:
	@echo "Statusing $(HTTPD) ..."
	@if [ -d "$(HTTPD_SOURCE)" ]; then\
		$(TOP_STATUS) $(HTTPD_SOURCE); \
	fi
	@echo "Statusing $(HTTPD) done"

#
# Clean
#
.PHONY: httpd-clean

httpd-clean:
	@rm -f $(HTTPD_DIR)/.httpd_configured
	@if [ -d "$(HTTPD_SOURCE)" ]; then\
		make -C $(HTTPD_SOURCE)/$(HTTPD) clean; \
	fi

#
# Dist clean
#
.PHONY: httpd-distclean

httpd-distclean:
	@rm -f $(HTTPD_DIR)/.httpd_*

#
# Install
#
.PHONY: httpd-install

httpd-install:
	cp -ra $(LIBS_INSTALL_PATH)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH) $(TOP_INSTALL_ROOTFS_DIR)
	#rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/htdocs/*
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/man
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/manual
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/include
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/icons
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/extra
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/original
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/lib/*.a
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/lib/pkgconfig
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/error
	rm -rf $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/build
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/ab
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/checkgid
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htcacheclean
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htdbm
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htdigest
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/htpasswd
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/httpd
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/httxt2dbm
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/logresolve
	$(STRIP) --remove-section=.comment --remove-section=.note $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/bin/rotatelogs
ifeq (x$(CONF_SUPPORT_VIRTUAL_REMOTE), xy)
	cd $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH);rm -rf logs;ln -sf /tmp logs
	sed -i 's/User daemon/User root/g' $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/httpd.conf
	sed -i 's/Group daemon/Group root/g' $(TOP_INSTALL_ROOTFS_DIR)/$(CONF_WEB_SERVER_APACHE_INSTALL_PATH)/conf/httpd.conf
endif
