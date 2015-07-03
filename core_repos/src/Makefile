TOP        := $(shell pwd)/..#

include $(TOP)/Target.mk

COMPONENT  := src# 

SUBDIRS_$(CONF_BUILD_EXTERNAL_PACKAGES) += libs
#SUBDIRS_y += util
SUBDIRS_y += crypto 
SUBDIRS_$(CONF_BUILD_MEDIALOGIC) += mediaplayer
SUBDIRS_$(CONF_BUILD_MISC) += misc 
#SUBDIRS_$(CONF_BUILD_DMAOSD) += osd
#SUBDIRS_$(CONF_BUILD_DMARENDER) += renderer
#SUBDIRS_$(CONF_CAS) += cas

SUBDIRS += $(SUBDIRS_y)

include $(TOP_SCRIPTS_DIR)/rules.mk

