##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author: wills_yin@alphanetworks.com
# wmc aes top-level Makefile
##############################################################################

############################# global settings section ########################
TOP          := $(shell pwd)/../../..#
COMPONENT    := crypto/aes# comment to remove trailing space 

#
LIB_AES_NAME        := libaes

#
LEAF_LIBS    := $(LIB_AES_NAME)
LEAF_BINS    :=

include $(TOP)/Target.mk
include $(TOP)/Target.options

############################# object rules section ###########################

include objects.mk

######################### common rules section ###############################

include $(TOP_SCRIPTS_DIR)/rules.mk

######################### command target section #############################
LEAF := $(LIB_AES_NAME)
$(LEAF)_OBJECTS := $(OBJECTS)
$(BUILD_LIB_CMD)

