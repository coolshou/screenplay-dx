
-include $(TOP)/Target.options
include $(TOP)/scripts/defines.mk
include $(TOP_SCRIPTS_DIR)/commons.mk

ifeq ($(CONF_PLATFORM_SMP8634),y)
-include $(TOP_SCRIPTS_DIR)/target-smp8634.mk
endif
ifeq ($(CONF_PLATFORM_SMP8654),y)
-include $(TOP_SCRIPTS_DIR)/target-smp8654.mk
endif
ifeq ($(CONF_PLATFORM_X86),y)
-include $(TOP_SCRIPTS_DIR)/target-i386.mk
endif

AS              = $(CROSS)as
LD              = $(CROSS)ld
CC              = $(CROSS)gcc
DEPEND_CC       = $(CROSS)gcc
CPP             = $(CROSS)cpp -E
AR              = $(CROSS)ar
NM              = $(CROSS)nm
STRIP           = $(CROSS)strip
OBJCOPY	        = $(CROSS)objcopy
OBJDUMP         = $(CROSS)objdump
RANLIB          = $(CROSS)ranlib
LINKER          = $(CROSS)g++
MAKELIB		= $(CROSS)ar -rcus 
export AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP RANLIB MAKELIB LINKER

