
DISKDEV_CMDS_VERSION	:= 332.14#

DISKDEV_CMDS_SERVER_URL		:= ${TOP_LIBS_URL}/diskdev_cmds/
DISKDEV_CMDS_SOURCE_PACKAGE	:= ${TOP_LIBS_DIR}/diskdev_cmds/diskdev_cmds-${DISKDEV_CMDS_VERSION}.tar.gz
DISKDEV_CMDS_SOURCE_DIR		:= ${TOP_LIBS_DIR}/diskdev_cmds/diskdev_cmds-${DISKDEV_CMDS_VERSION}
DISKDEV_CMDS_PATCH		:= ${TOP_LIBS_DIR}/diskdev_cmds/diskdev_cmds-${DISKDEV_CMDS_VERSION}.patch
DISKDEV_CMDS_DIR		:= ${TOP_LIBS_DIR}/diskdev_cmds

export DISKDEV_CFLAGS=-I$(SYSLIB_PREFIX)/include
export DISKDEV_LDFLAGS=-L$(SYSLIB_PREFIX)/lib

#
# Download the source
#
.PHONY:	diskdev_cmds-downloaded

diskdev_cmds-downloaded: ${TOP_LIBS_DIR}/.diskdev_cmds_downloaded

${TOP_LIBS_DIR}/.diskdev_cmds_downloaded:
	@echo "Downloading ${DISKDEV_CMDS_SOURCE_PACKAGE} from ${DISKDEV_CMDS_SERVER_URL} ..."
	cd ${TOP_LIBS_DIR}; ${TOP_DOWNLOAD} ${DISKDEV_CMDS_SERVER_URL};
	@echo "Downloading ${DISKDEV_CMDS_SOURCE_PACKAGE} done" 
	touch $@

#
# Unpack the source
#
.PHONY: diskdev_cmds-unpacked

diskdev_cmds-unpacked: $(TOP_LIBS_DIR)/.diskdev_cmds_unpacked

$(TOP_LIBS_DIR)/.diskdev_cmds_unpacked: ${TOP_LIBS_DIR}/.diskdev_cmds_downloaded
	@echo "Unpack ${DISKDEV_CMDS_SOURCE_PACKAGE}..." 
	@rm -rf ${DISKDEV_CMDS_SOURCE_DIR}
	(cd ${DISKDEV_CMDS_DIR}; tar xzvf ${DISKDEV_CMDS_SOURCE_PACKAGE});
	@echo "Unpack ${DISKDEV_CMDS_SOURCE_PACKAGE} done..."
	touch $@

#
# Patch source
#
.PHONY: diskdev_cmds-patched

diskdev_cmds-patched: $(TOP_LIBS_DIR)/.diskdev_cmds_patched

$(TOP_LIBS_DIR)/.diskdev_cmds_patched: $(TOP_LIBS_DIR)/.diskdev_cmds_unpacked
	(cd ${DISKDEV_CMDS_SOURCE_DIR}; patch -p1 < ${DISKDEV_CMDS_PATCH})
	touch $@

#
# Config
#
.PHONY:	diskdev_cmds-config

diskdev_cmds-config:

#
# Configuration
#
.PHONY:	diskdev_cmds-configured

diskdev_cmds-configured: diskdev_cmds-config $(TOP_LIBS_DIR)/.diskdev_cmds-configured

$(TOP_LIBS_DIR)/.diskdev_cmds-configured: $(TOP_LIBS_DIR)/.diskdev_cmds_patched
	touch $@


#
# Compile
#
.PHONY: diskdev_cmds-compile 

diskdev_cmds-compile: $(TOP_LIBS_DIR)/.diskdev_cmds-compile

$(TOP_LIBS_DIR)/.diskdev_cmds-compile: $(TOP_LIBS_DIR)/.diskdev_cmds-configured
	@echo "Compiling ${DISKDEV_CMDS_SOURCE_PACKAGE}..."
	if [ x$(CONF_HFS_FSCK_SUPPORT) == xy ]; then \
		( cd ${DISKDEV_CMDS_SOURCE_DIR}; make CC=$(CC) SUBDIRS=fsck_hfs.tproj -f Makefile.lnx ) ;\
	fi
	if [ x$(CONF_HFS_MKFS_SUPPORT) == xy ]; then \
		( cd ${DISKDEV_CMDS_SOURCE_DIR}; make CC=$(CC) SUBDIRS=newfs_hfs.tproj -f Makefile.lnx ) ;\
	fi
	@echo "Compiling ${DISKDEV_CMDS_SOURCE_PACKAGE} done..."
	@touch $@


#
# Update
#
.PHONY: diskdev_cmds-update

diskdev_cmds-update:
	@echo "Updating $(DISKDEV_CMDS_SOURCE_PACKAGE) ..."
	@if [ -d "$(DISKDEV_CMDS_SOURCE_DIR)" ]; then\
		$(TOP_UPDATE) $(DISKDEV_CMDS_SOURCE_DIR); \
	fi
	@echo "Updating $(DISKDEV_CMDS_SOURCE_PACKAGE) done"

#
# Status
#
.PHONY: diskdev_cmds-status

diskdev_cmds-status:
	@echo "Statusing $(DISKDEV_CMDS_SOURCE_PACKAGE) ..."
	@if [ -d "$(DISKDEV_CMDS_SOURCE_DIR)" ]; then\
		$(TOP_STATUS) $(DISKDEV_CMDS_SOURCE_DIR); \
	fi
	@echo "Statusing $(DISKDEV_CMDS_SOURCE_PACKAGE) done"

#
# Clean
#
.PHONY: diskdev_cmds-clean

diskdev_cmds-clean:
	@rm -f $(TOP_LIBS_DIR)/.diskdev_cmds-configured
	@rm -f $(TOP_LIBS_DIR)/.diskdev_cmds-compile
	( cd ${DISKDEV_CMDS_SOURCE_DIR}; make CC=$(CC) SUBDIRS=fsck_hfs.tproj -f Makefile.lnx clean)
	( cd ${DISKDEV_CMDS_SOURCE_DIR}; make  CC=$(CC) SUBDIRS=newfs_hfs.tproj -f Makefile.lnx clean)

#
# Dist clean
#
.PHONY: diskdev_cmds-distclean

diskdev_cmds-distclean:
	rm -f $(TOP_LIBS_DIR)/.diskdev_cmds*

#
# Install
#
.PHONY: diskdev_cmds-install

diskdev_cmds-install:
	if [ x$(CONF_HFS_FSCK_SUPPORT) == xy ]; then \
		cp -f $(DISKDEV_CMDS_SOURCE_DIR)/fsck_hfs.tproj/fsck_hfs $(TOP_INSTALL_ROOTFS_DIR)/bin;\
		$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/bin/fsck_hfs ;\
	fi;
	if [ x$(CONF_HFS_MKFS_SUPPORT) == xy ]; then \
		cp -f $(DISKDEV_CMDS_SOURCE_DIR)/newfs_hfs.tproj/newfs_hfs $(TOP_INSTALL_ROOTFS_DIR)/bin;\
		$(CROSS)strip $(TOP_INSTALL_ROOTFS_DIR)/bin/newfs_hfs ;\
	fi;



