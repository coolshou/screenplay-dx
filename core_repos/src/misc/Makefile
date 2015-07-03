##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author: wills_yin@alphanetworks.com
# misc top-level Makefile
##############################################################################

############################# global settings section ########################

TOP        := $(shell pwd)/../..#
COMPONENT  := misc# comment to remove trailing space 

include $(TOP)/Target.mk
include $(TOP)/Target.options

######################### common rules section #############################

SUBDIRS := 

SUBDIRS_$(CONF_SAMBA)  += samba

SUBDIRS	+= $(SUBDIRS_y)

include $(TOP_SCRIPTS_DIR)/rules.mk

#
# install
#
.PHONY: install install-all

install install_all:
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/bin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/sbin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/bin
	mkdir -p $(TOP_INSTALL_ROOTFS_DIR)/usr/sbin
	for dir in $(SUBDIRS); do \
		make -C $$dir install; \
	done
