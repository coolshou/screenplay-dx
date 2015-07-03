TOP        := $(shell pwd)/../..#
include $(TOP)/Target.mk

SIGMA_SDK_DIR         := $(TOP_LIBS_DIR)#
SIGMA_SDK_SOURCE      := $(SIGMA_SDK_DIR)/$(CONF_SIGMA_SDK_VERSION)#

LINKER          = g++
export LINKER
# for inc.Makefile. because Sigma will do "LINKTOOL := $(CROSS)$(LINKER)" in the inc.Makefile. and we assign the LINKER. Sigma assign the CROSS. So the LINKTOOL will be "mipsel-linux-" + "xxxxxx/mipsel-linux-g++"

CROSS_COMPILE          = mipsel-linux-
export CROSS_COMPILE

.PHONY: sigma_driver

sigma_driver:
	(cd $(SIGMA_SDK_SOURCE)/;rm -f proc_pipe;ln -s $(TOP)/src/mediaplayer/proc_pipe/module proc_pipe; export RMCFLAGS='';export UCLINUX_KERNEL=$(TOP_LIBS_DIR)/$(CONF_SIGMA_SDK_VERSION)/linux_kernel_$(CONF_LINUX_KERNEL_VERSION)/ ; cd proc_pipe; make;)

.PHONY: sigma_isdk

sigma_isdk:

sigma_key_tools:

.PHONY: sigma_zboot

sigma_zboot:
