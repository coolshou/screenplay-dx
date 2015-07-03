TARGET_TYPE := RELOCATABLE_OBJECT
TARGET := proc_pipe.o
SRC := device.c pipe.c

COMPILKIND += kernel uclinux
COMPILKIND := $(filter-out withthreads, $(COMPILKIND))

CROSS = mipsel-linux-

#DISABLE_WARNINGS = 1

obj-m := proc_pipe.o
proc_pipe-objs := $(addsuffix .o, $(basename $(SRC)))


#CFLAGS += $(RMCFLAGS) -Werror -DEXPORT_SYMTAB -DNONE_YAFFS -D__LINUX -DCONFIG_PROC_PIPE_64_BITS_SUPPORT
CFLAGS += $(RMCFLAGS) -Werror -DEXPORT_SYMTAB -DNONE_YAFFS -D__LINUX -DCONFIG_PROC_PIPE_KERNEL_SUPPORT_64_BITS


# Find out where is kernel tree
ifdef LINUX_KERNEL
KERNEL_DIR := $(LINUX_KERNEL)
endif
ifdef UCLINUX_KERNEL
KERNEL_DIR := $(UCLINUX_KERNEL)
endif
ifdef MUM_KI
KERNEL_DIR := $(subst /include,,$(subst -I,,$(MUM_KI)))
endif

ifeq ($(KERNEL_DIR),)
# KERNEL_DIR is not set, use the default
KERNEL_DIR := $(PWD)/../../linux_kernel_2.6.15
endif

VERSION_H := $(wildcard $(KERNEL_DIR)/include/linux/version.h)
AUTOCONF_H := $(wildcard $(KERNEL_DIR)/include/linux/autoconf.h)

ifeq ($(VERSION_H),)
$(error (UC)LINUX_KERNEL, or MUM_KI seems to be pointed to wrong location, or kernel is not configured.)
endif
ifeq ($(AUTOCONF_H),)
$(error (UC)LINUX_KERNEL, or MUM_KI seems to be pointed to wrong location, or kernel is not configured.)
endif

.PHONY: all
all: proc_pipe.ko

proc_pipe.ko: FORCE
	echo $(KERNEL_DIR)
	$(MAKE) -C $(KERNEL_DIR) M="$$PWD" V=$(V) modules

.PHONY: cleanall
cleanall:
	$(MAKE) -C $(KERNEL_DIR) M="$$PWD" V=$(V) clean
	@$(RM) Module.symvers

.PHONY: clean
clean:
	$(MAKE) -C $(KERNEL_DIR) M="$$PWD" V=$(V) clean
	@$(RM) Module.symvers

modules_install:
	$(MAKE) -C $(KERNEL_DIR) M="$$PWD" V=$(V) modules_install

.PHONY: FORCE
FORCE:


