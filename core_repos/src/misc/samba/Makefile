##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  joshua_lee@alphanetworks.com
# dns_damemon top-level Makefile
##############################################################################

############################# global variables section #######################

TOP        := $(shell pwd)/../../..#

COMPONENT  := misc/smbtree# 
LEAF_BINS  := smbtree

include $(TOP)/Target.mk
include $(TOP)/Target.options

############################ object rules section ############################

include objects.mk

############################ common rules section ############################

include $(TOP_SCRIPTS_DIR)/rules.mk

########################### target section ###################################

LEAF := smbtree
$(LEAF)_OBJECTS := $(OBJECTS)
$(LEAF)_DEPLIBS :=  lib_event_proxy.a libcommon_util.a
$(LEAF)_SYSLIBS := -lcrypt -lresolv -ldl -lpopt -lpthread \
	$(TOP_BUILD_DIR)/binary/third_party_build/lib/libsmbclient.a

$(BUILD_BIN_CMD)

########################### install section ##################################

install:
	-cp -f $(BIN_DIR)/smbtree $(TOP_INSTALL_ROOTFS_DIR)/bin
	-chmod +x $(TOP_INSTALL_ROOTFS_DIR)/bin/smbtree

