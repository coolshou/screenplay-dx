##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author: wills_yin@alphanetworks.com
# rsa library top-level Makefile
##############################################################################

############################# global settings section ########################
RSAREF_NAME := rsaref
TEST        := 0
TEST_BIN    := rsademo

TOP 	    := $(shell pwd)/../../..#
COMPONENT   := crypto/rsa# comment to remove trailing space
LEAF_LIBS   := $(RSAREF_NAME)
ifeq ($(TEST), 1)
LEAF_BINS   := $(TEST_BIN) 
endif

include ${TOP}/Target.mk
include ${TOP}/Target.options

############################# object rules section ###########################

CFLAGS += -O
# The location of the common source directory.
VPATH         =  source
VPATH_$(TEST) += rdemo
VPATH         += $(VPATH_y)

OBJECTS = \
	  desc.o\
	  digit.o \
	  md2c.o \
	  md5c.o \
	  nn.o \
	  prime.o \
	  rsa.o  \
	  r_encode.o \
	  r_dh.o \
	  r_enhanc.o \
	  r_keygen.o \
	  r_random.o \
	  r_stdlib.o
RSADEMO_OBJS := rdemo.o

OBJECTS_ALL  := $(OBJECTS)
ifeq ($(TEST), 1)
OBJECTS_ALL  += $(RSADEMO_OBJS) 
endif

######################### common rules section #############################

include $(TOP_SCRIPTS_DIR)/rules.mk

######################### command target section #############################

LEAF := $(RSAREF_NAME)
$(LEAF)_OBJECTS := $(OBJECTS)
$(BUILD_LIB_CMD)

LEAF := $(TEST_BIN)
$(LEAF)_OBJECTS := $(RSADEMO_OBJS)
$(LEAF)_DEPLIBS := $(RSAREF_NAME).a
$(BUILD_BIN_CMD)
