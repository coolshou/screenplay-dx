
DMALLOC_SERVER_URL		:= ${TOP_LIBS_URL}/dmalloc/
DMALLOC_SOURCE_PACKAGE		:= ${TOP_LIBS_DIR}/dmalloc/dmalloc-${CONF_DMALLOC_VERSION}.tar.gz
DMALLOC_PATCH_SOURCE_DIR	:= ${TOP_LIBS_DIR}/dmalloc/patch-${CONF_DMALLOC_VERSION}
DMALLOC_SOURCE_DIR		:= ${TOP_LIBS_DIR}/dmalloc/dmalloc-${CONF_DMALLOC_VERSION}
DMALLOC_DIR			:= ${TOP_LIBS_DIR}/dmalloc

#
# Download the source
#
.PHONY:	dmalloc-downloaded

dmalloc-downloaded: ${TOP_LIBS_DIR}/.dmalloc_downloaded

${TOP_LIBS_DIR}/.dmalloc_downloaded:
	@echo "Downloading ${DMALLOC_SOURCE_PACKAGE} from ${DMALLOC_SERVER_URL} ..."
	cd ${TOP_LIBS_DIR}; ${TOP_DOWNLOAD} ${DMALLOC_SERVER_URL};
	@echo "Downloading ${DMALLOC_SOURCE_PACKAGE} done" 
	touch $@

#
# Unpack the source
#
.PHONY: dmalloc-unpacked

dmalloc-unpacked: ${TOP_LIBS_DIR}/.dmalloc_downloaded $(TOP_LIBS_DIR)/.dmalloc_unpacked

$(TOP_LIBS_DIR)/.dmalloc_unpacked: ${TOP_LIBS_DIR}/.dmalloc_downloaded
	@echo "Unpack ${DMALLOC_SOURCE_PACKAGE}..." 
	@rm -rf ${DMALLOC_SOURCE_DIR}
	(cd ${DMALLOC_DIR}; tar xzvf ${DMALLOC_SOURCE_PACKAGE});
	@echo "Unpack ${DMALLOC_SOURCE_PACKAGE} done..."
	touch $@

#
# Patch source
#
.PHONY: dmalloc-patched

dmalloc-patched: $(TOP_LIBS_DIR)/.dmalloc_patched

$(TOP_LIBS_DIR)/.dmalloc_patched: $(TOP_LIBS_DIR)/.dmalloc_unpacked
	(cd $(DMALLOC_SOURCE_DIR); patch -p1 < $(DMALLOC_PATCH_SOURCE_DIR)/dmalloc-${CONF_DMALLOC_VERSION}.patch)
	(cd $(DMALLOC_SOURCE_DIR); patch -p1 < $(DMALLOC_PATCH_SOURCE_DIR)/dmalloc-mips.patch)
	(cd $(DMALLOC_SOURCE_DIR); patch -p0 < $(DMALLOC_PATCH_SOURCE_DIR)/settings.dist.patch)
	sed -i -e 's/^ac_cv_page_size=0$$/ac_cv_page_size=12/' ${DMALLOC_SOURCE_DIR}/configure
	sed -i -e 's/(ld -/(${LD-ld} -/' ${DMALLOC_SOURCE_DIR}/configure
	sed -i -e 's/'\''ld -/"${LD-ld}"'\'' -/' ${DMALLOC_SOURCE_DIR}/configure
	sed -i -e 's/ar cr/$${AR} cr/' ${DMALLOC_SOURCE_DIR}/configure
	touch $@

#
# Config
#
.PHONY:	dmalloc-config

dmalloc-config:

#
# Configuration
#
.PHONY:	dmalloc-configured

dmalloc-configured: dmalloc-config $(TOP_LIBS_DIR)/.dmalloc-configured

$(TOP_LIBS_DIR)/.dmalloc-configured: $(TOP_LIBS_DIR)/.dmalloc_patched
	@echo "Configuring ${DMALLOC_SOURCE_PACKAGE}..."
	cd ${DMALLOC_SOURCE_DIR}; CFLAGS="-g -Os -mips32r2 -pipe" LDFLAGS="-g " ./configure --prefix=${LIBS_INSTALL_PATH} --target=mipsel-linux --host=mipsel-linux --build=i386-pc-linux-gnu --enable-shlib --enable-cxx --enable-threads 
	@echo "Configuring ${DMALLOC_SOURCE_PACKAGE} done..."
	touch $@


#
# Compile
#
.PHONY: dmalloc-compile

dmalloc-compile: $(TOP_LIBS_DIR)/.dmalloc-compile

$(TOP_LIBS_DIR)/.dmalloc-compile: $(TOP_LIBS_DIR)/.dmalloc-configured
	@echo "Compiling ${DMALLOC_SOURCE_PACKAGE}..."
	make -C ${DMALLOC_SOURCE_DIR}
	make -C ${DMALLOC_SOURCE_DIR} install
	@echo "Compiling ${DMALLOC_SOURCE_PACKAGE} done..."
	@touch $@


#
# Update
#
.PHONY: dmalloc-update

dmalloc-update:
	@echo "Updating $(DMALLOC_SOURCE_PACKAGE) ..."
	@if [ -d "$(DMALLOC_SOURCE_DIR)" ]; then\
		$(TOP_UPDATE) $(DMALLOC_SOURCE_DIR); \
	fi
	@echo "Updating $(DMALLOC_SOURCE_PACKAGE) done"

#
# Status
#
.PHONY: dmalloc-status

dmalloc-status:
	@echo "Statusing $(DMALLOC_SOURCE_PACKAGE) ..."
	@if [ -d "$(DMALLOC_SOURCE_DIR)" ]; then\
		$(TOP_STATUS) $(DMALLOC_SOURCE_DIR); \
	fi
	@echo "Statusing $(DMALLOC_SOURCE_PACKAGE) done"

#
# Clean
#
.PHONY: dmalloc-clean

dmalloc-clean:
	@rm -f $(TOP_LIBS_DIR)/.dmalloc_configured
	make -C ${DMALLOC_SOURCE_DIR} clean

#
# Dist clean
#
.PHONY: dmalloc-distclean

dmalloc-distclean:
	@rm -f $(TOP_LIBS_DIR)/.dmalloc_*

#
# Install
#
.PHONY: dmalloc-install

dmalloc-install:
	cp -f $(DMALLOC_SOURCE_DIR)/dmalloc $(TOP_INSTALL_ROOTFS_DIR)/bin 




