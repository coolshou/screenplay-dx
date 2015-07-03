##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  joshua_lee@alphanetworks.com
# dns_daemon object rules makefile fragments
##############################################################################
#define

ifndef  CONF_SAMBA_VERSION
	SAMBA_VERSION := 3.0.28a#
else
	SAMBA_VERSION := $(CONF_SAMBA_VERSION)#
endif

	SOURCE_FOLDER := source

SAMBA_SOURCE  = $(TOP)/src/libs/samba-$(SAMBA_VERSION)/samba-$(SAMBA_VERSION)/$(SOURCE_FOLDER)
SAMBA_POPT_SOURCE = $(SAMBA_SOURCE)/../lib/popt
#
# include search path section
#
INCLUDES += \
	-I$(TOP)                           \
	-include $(TOP)/Target.h	\
	-I$(SAMBA_SOURCE)/iniparser/src \
	-I$(SAMBA_SOURCE)/libaddns  \
	-I$(SAMBA_SOURCE)/librpc  \
	-I$(SAMBA_SOURCE)/lib/talloc \
	-I$(SAMBA_SOURCE)/tdb/include  \
	-I$(SAMBA_SOURCE)/lib/replace \
	-I$(SAMBA_SOURCE)/include/  \
	-I$(SAMBA_SOURCE)/ \
	-I$(SAMBA_POPT_SOURCE)  \
	-I$(TOP_UTILS_DIR)/include         
#
# CFLAGS section
#
CFLAGS += \
	-DHAVE_CONFIG_H                     \
	-D_SAMBA_BUILD_=3

#
# objects list  section
#
OBJECTS          := smbtree_$(SAMBA_VERSION).o  popt_common_$(SAMBA_VERSION).o

OBJECTS_ALL	:= $(OBJECTS)

