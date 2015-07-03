
DOSFSTOOLS_VERSION	:= 2.11-6

DOSFSTOOLS_SERVER_URL		:= ${TOP_LIBS_URL}/dosfstools/
DOSFSTOOLS_SOURCE_PACKAGE	:= ${TOP_LIBS_DIR}/dosfstools/dosfstools_${DOSFSTOOLS_VERSION}.tar.gz
DOSFSTOOLS_PATCH_FILE		:= ${TOP_LIBS_DIR}/dosfstools/dosfstools_${DOSFSTOOLS_VERSION}.diff
DOSFSTOOLS_SOURCE_DIR		:= ${TOP_LIBS_DIR}/dosfstools/dosfstools_${DOSFSTOOLS_VERSION}
DOSFSTOOLS_DIR			:= ${TOP_LIBS_DIR}/dosfstools

#
# Download the source
#
.PHONY:	dosfstools-downloaded

dosfstools-downloaded: ${TOP_LIBS_DIR}/.dosfstools_downloaded

${TOP_LIBS_DIR}/.dosfstools_downloaded:
	touch $@

#
# Unpack the source
#
.PHONY: dosfstools-unpacked

dosfstools-unpacked: $(TOP_LIBS_DIR)/.dosfstools_unpacked

$(TOP_LIBS_DIR)/.dosfstools_unpacked: ${TOP_LIBS_DIR}/.dosfstools_downloaded
	@echo "Unpack ${DOSFSTOOLS_SOURCE_PACKAGE}..." 
	@rm -rf ${DOSFSTOOLS_SOURCE_DIR}
	(cd ${DOSFSTOOLS_DIR}; tar xzvf ${DOSFSTOOLS_SOURCE_PACKAGE});
	@echo "Unpack ${DOSFSTOOLS_SOURCE_PACKAGE} done..."
	touch $@

#
# Patch source
#
.PHONY: dosfstools-patched

dosfstools-patched: $(TOP_LIBS_DIR)/.dosfstools_patched

$(TOP_LIBS_DIR)/.dosfstools_patched: $(TOP_LIBS_DIR)/.dosfstools_unpacked
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_PATCH_FILE) ) 
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/01-argfix.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/02-fortify.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/03-label.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/04-unaligned-memory.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/05-o-excl.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/06-determine-sector-size.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/07-manpage-spelling.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/08-manpage-drop.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/09-manpage-fat32.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/10-manpage-synopsis.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/11-memory-efficiency.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/12-zero-slot.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/13-getopt.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/14-bootcode.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/15-manpage-files.dpatch )
	(cd $(DOSFSTOOLS_SOURCE_DIR); patch -p1 < $(DOSFSTOOLS_SOURCE_DIR)/debian/patches/99-conglomeration.dpatch )
	touch $@

#
# Config
#
.PHONY:	dosfstools-config

dosfstools-config:

#
# Configuration
#
.PHONY:	dosfstools-configured

dosfstools-configured: dosfstools-config $(TOP_LIBS_DIR)/.dosfstools-configured

$(TOP_LIBS_DIR)/.dosfstools-configured: $(TOP_LIBS_DIR)/.dosfstools_patched
	@echo "Configuring ${DOSFSTOOLS_SOURCE_PACKAGE}..."
	@echo "Configuring ${DOSFSTOOLS_SOURCE_PACKAGE} done..."
	touch $@


#
# Compile
#
.PHONY: dosfstools-compile

dosfstools-compile: $(TOP_LIBS_DIR)/.dosfstools-compile

$(TOP_LIBS_DIR)/.dosfstools-compile: $(TOP_LIBS_DIR)/.dosfstools-configured
	@echo "Compiling ${DOSFSTOOLS_SOURCE_PACKAGE}..."
	make -C ${DOSFSTOOLS_SOURCE_DIR} CC=$(CC)
	@echo "Compiling ${DOSFSTOOLS_SOURCE_PACKAGE} done..."
	@touch $@


#
# Update
#
.PHONY: dosfstools-update

dosfstools-update:
	@echo "Updating $(DOSFSTOOLS_SOURCE_PACKAGE) ..."
	@if [ -d "$(DOSFSTOOLS_SOURCE_DIR)" ]; then\
		$(TOP_UPDATE) $(DOSFSTOOLS_SOURCE_DIR); \
	fi
	@echo "Updating $(DOSFSTOOLS_SOURCE_PACKAGE) done"

#
# Status
#
.PHONY: dosfstools-status

dosfstools-status:
	@echo "Statusing $(DOSFSTOOLS_SOURCE_PACKAGE) ..."
	@if [ -d "$(DOSFSTOOLS_SOURCE_DIR)" ]; then\
		$(TOP_STATUS) $(DOSFSTOOLS_SOURCE_DIR); \
	fi
	@echo "Statusing $(DOSFSTOOLS_SOURCE_PACKAGE) done"

#
# Clean
#
.PHONY: dosfstools-clean

dosfstools-clean:
	@rm -f $(TOP_LIBS_DIR)/.dosfstools_configured
	make -C ${DOSFSTOOLS_SOURCE_DIR} clean

#
# Dist clean
#
.PHONY: dosfstools-distclean

dosfstools-distclean:
	@rm -f $(TOP_LIBS_DIR)/.dosfstools*

#
# Install
#
.PHONY: dosfstools-install

dosfstools-install:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/bin
	cp -f $(DOSFSTOOLS_SOURCE_DIR)/dosfsck/dosfsck $(TOP_INSTALL_ROOTFS_DIR)/bin
	$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/bin/dosfsck




