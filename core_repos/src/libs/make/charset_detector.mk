
CHARSET_DETECTOR_VERSION	:=

CHARSET_DETECTOR_SERVER_URL		:= ${TOP_LIBS_URL}/charset_detector/
CHARSET_DETECTOR_SOURCE_PACKAGE		:= ${TOP_LIBS_DIR}/charset_detector/charset-detector.tar.gz
CHARSET_DETECTOR_PATCH_SOURCE_DIR	:= ${TOP_LIBS_DIR}/charset_detector/patch/
CHARSET_DETECTOR_SOURCE_DIR		:= ${TOP_LIBS_DIR}/charset_detector/charset-detector
CHARSET_DETECTOR_DIR			:= ${TOP_LIBS_DIR}/charset_detector

#
# Download the source
#
.PHONY:	charset_detector-downloaded

charset_detector-downloaded: ${TOP_LIBS_DIR}/.charset_detector_downloaded

${TOP_LIBS_DIR}/.charset_detector_downloaded:
	@echo "Downloading ${CHARSET_DETECTOR_SOURCE_PACKAGE} from ${CHARSET_DETECTOR_SERVER_URL} ..."
	cd ${TOP_LIBS_DIR}; ${TOP_DOWNLOAD} ${CHARSET_DETECTOR_SERVER_URL};
	@echo "Downloading ${CHARSET_DETECTOR_SOURCE_PACKAGE} done" 
	touch $@

#
# Unpack the source
#
.PHONY: charset_detector-unpacked

charset_detector-unpacked: $(TOP_LIBS_DIR)/.charset_detector_unpacked

$(TOP_LIBS_DIR)/.charset_detector_unpacked: ${TOP_LIBS_DIR}/.charset_detector_downloaded
	@echo "Unpack ${CHARSET_DETECTOR_SOURCE_PACKAGE}..." 
	@rm -rf ${CHARSET_DETECTOR_SOURCE_DIR}
	(cd ${CHARSET_DETECTOR_DIR}; tar xzvf ${CHARSET_DETECTOR_SOURCE_PACKAGE});
	@echo "Unpack ${CHARSET_DETECTOR_SOURCE_PACKAGE} done..."
	touch $@

#
# Patch source
#
.PHONY: charset_detector-patched

charset_detector-patched: $(TOP_LIBS_DIR)/.charset_detector_patched

$(TOP_LIBS_DIR)/.charset_detector_patched: $(TOP_LIBS_DIR)/.charset_detector_unpacked
	(cd ${CHARSET_DETECTOR_DIR}; patch -p0 < $(CHARSET_DETECTOR_PATCH_SOURCE_DIR)/charset-detector.patch);
	(cd ${CHARSET_DETECTOR_DIR}; patch -p0 < $(CHARSET_DETECTOR_PATCH_SOURCE_DIR)/charset-detector.makefile.patch);
	(cd ${CHARSET_DETECTOR_DIR}; patch -p0 < $(CHARSET_DETECTOR_PATCH_SOURCE_DIR)/charset-detector.threshold.patch);
	touch $@

#
# Config
#
.PHONY:	charset_detector-config

charset_detector-config:

#
# Configuration
#
.PHONY:	charset_detector-configured

charset_detector-configured: charset_detector-config $(TOP_LIBS_DIR)/.charset_detector-configured

$(TOP_LIBS_DIR)/.charset_detector-configured:
	touch $@


#
# Compile
#
.PHONY: charset_detector-compile

charset_detector-compile: $(TOP_LIBS_DIR)/.charset_detector-compile

$(TOP_LIBS_DIR)/.charset_detector-compile: $(TOP_LIBS_DIR)/.charset_detector-configured
	@echo "Compiling ${CHARSET_DETECTOR_SOURCE_PACKAGE}..."
	make -C ${CHARSET_DETECTOR_SOURCE_DIR}
	@echo "Compiling ${CHARSET_DETECTOR_SOURCE_PACKAGE} done..."
	@touch $@


#
# Update
#
.PHONY: charset_detector-update

charset_detector-update:
	@echo "Updating $(CHARSET_DETECTOR_SOURCE_PACKAGE) ..."
	@if [ -d "$(CHARSET_DETECTOR_SOURCE_DIR)" ]; then\
		$(TOP_UPDATE) $(CHARSET_DETECTOR_SOURCE_DIR); \
	fi
	@echo "Updating $(CHARSET_DETECTOR_SOURCE_PACKAGE) done"

#
# Status
#
.PHONY: charset_detector-status

charset_detector-status:
	@echo "Statusing $(CHARSET_DETECTOR_SOURCE_PACKAGE) ..."
	@if [ -d "$(CHARSET_DETECTOR_SOURCE_DIR)" ]; then\
		$(TOP_STATUS) $(CHARSET_DETECTOR_SOURCE_DIR); \
	fi
	@echo "Statusing $(CHARSET_DETECTOR_SOURCE_PACKAGE) done"

#
# Clean
#
.PHONY: charset_detector-clean

charset_detector-clean:
	@rm -f $(TOP_LIBS_DIR)/.charset_detector_configured
	make -C ${CHARSET_DETECTOR_SOURCE_DIR} clean

#
# Dist clean
#
.PHONY: charset_detector-distclean

charset_detector-distclean:
	@rm -f $(TOP_LIBS_DIR)/.charset_detector*
#@rm -fr $(CHARSET_DETECTOR_DIR)

#
# Install
#
.PHONY: charset_detector-install

charset_detector-install:
	cp -f $(CHARSET_DETECTOR_SOURCE_DIR)/chardetect.so $(TOP_INSTALL_ROOTFS_DIR)/lib




