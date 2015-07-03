##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# Makfefile fragments for common global building variables.
##############################################################################

ifndef COMMONS_MK_INCLUDED

COMMONS_MK_INCLUDED := 1

# build root 
BUILD_ROOT   := $(TOP)/build/binary

# all the library and binary directory
LIB_DIR		= $(BUILD_ROOT)/lib
BIN_DIR		= $(BUILD_ROOT)/bin
ETC_DIR		= $(BUILD_ROOT)/etc
ASM_DIR		= $(TOP)/build/asm
SYSLIB_PREFIX	= $(BUILD_ROOT)/third_party_build
HOST_TOOL_DIR	= $(TOP)/build/host/bin
export BUILD_ROOT LIB_DIR BIN_DIR ETC_DIR SYSLIB_PREFIX HOST_TOOL_DIR

endif        # COMMONS_MK_INCLUDED
