##############################################################################
# Copyright (C) alphanetworks 2006-- 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# General makefile rules. 
##############################################################################

ifndef RULES_MK_INCLUDED

RULES_MK_INCLUDED := 1

##############################################################################
# Notes
#     This file provides variables which define the necessary command blocks 
# and targets to be used in sublevel Makefiles.  Some of the variables defined 
# below are only defined as building blocks for the others and should not be 
# used directly.  The externally-usable variables are as follows:
#
# COMPONENT:     
#     the relative building path
# OBJECTS_ALL:   
#     all the object files, also used by dependence rules 
#
# PREREQS:       prerequisite targets
# SUBDIRS:       all the prerequsite target directories 
# LEAF_LIBS:     all the library targets
# LEAF_LIBS:     all the binary targets
# LEAF:          the single library or binary name
#
# BUILD_LIB_CMD: the library build template
# BUILD_BIN_CMD: the binary build template
##############################################################################

##############################################################################
# global variables section.
##############################################################################

# current build directory
BUILD_CURDIR    := $(BUILD_ROOT)/$(COMPONENT)

# build dependence and object directory
OBJECTS_DIR  := $(BUILD_CURDIR)
DEPENDS_DIR  := $(BUILD_CURDIR)

RM           := rm -f
RMDIR        := rm -fr
MV           := mv -f 
CP           := cp
MKDIR        := mkdir -p
REDIRECT_TO_NULL := 2> /dev/null

##############################################################################
# Debug level.
##############################################################################

# debug_level: 0(default) quiet, 1 compiling information,2 dependece+compiling
# You can invoke the shell command like that: make debug_level=[0|1|2]
CC_QUIET  :=@
DEP_QUIET :=@

ifeq ($(debug_level),2)
CC_QUIET  :=# 
DEP_QUIET :=# 
endif

ifeq ($(debug_level),1)
CC_QUIET  :=# 
DEP_QUIET :=@ 
endif

##############################################################################
# Make Functions.
##############################################################################

# $(call DEPCC_FN CFLAGS INCLUDES SOURCE TARGET)
DEPCC_FN		?=	$(DEPEND_CC) $(CFLAGS_DEP) $(1) $(2) $(3) > $(4)

# $(call AS_FN $@,$<,$(ASFLAGS))
AS_FN			?=	$(AS) $(ASSEMBLER_FLAGS) $(1) $(2) $(3)

# $(call CC_FN $@,$<,$(INCLUDES),$(CFLAGS_X))
CC_FN			?=	$(CC) $(COMPILER_FLAGS) $(1) $(2) $(3) $(4)

##############################################################################
# Dependece rules section.
##############################################################################

# dependence rules for single file
define FILE_DEP_CMD
	-$(DEP_QUIET)mkdir -p $(@D) $(REDIRECT_TO_NULL)
	@echo \(Dependencies $<\)
	-$(DEP_QUIET)$(call DEPCC_FN,$(CFLAGS),$(INCLUDES),$<,$@ )
	$(DEP_QUIET)${MV} $@ $@.tmp
	$(DEP_QUIET)sed -e 's|.*:|$(patsubst $(DEPENDS_DIR), $(OBJECTS_DIR),$(patsubst %.$(DEPEND_EXT),%.$(OBJ_EXT),$@)) $@:|' < $@.tmp > $@
	$(DEP_QUIET)sed -e 's/.*://' -e 's/\\$$//' < $@.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $@
	$(DEP_QUIET)${RM}  $@.tmp
endef

# dependence rules for patterns
define PATTERN_DEP_CMD
	-$(DEP_QUIET)mkdir -p $(@D) $(REDIRECT_TO_NULL)
	@echo \(Dependencies $<\)
	-$(DEP_QUIET)$(call DEPCC_FN,$(CFLAGS),$(INCLUDES),$<, ${DEPENDS_DIR}/$*.d)
	$(DEP_QUIET)$(MV) $(DEPENDS_DIR)/$*.d ${DEPENDS_DIR}/$*.d.tmp
	$(DEP_QUIET)sed -e 's|.*:|$(OBJECTS_DIR)/$*.$(OBJ_EXT) $(DEPENDS_DIR)/$*.$(DEPEND_EXT):|' < ${DEPENDS_DIR}/$*.d.tmp > ${DEPENDS_DIR}/$*.d
	$(DEP_QUIET)sed -e 's/.*://' -e 's/\\$$//' < ${DEPENDS_DIR}/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> ${DEPENDS_DIR}/$*.d
	$(DEP_QUIET)${RM}  ${DEPENDS_DIR}/$*.d.tmp
endef

# C source dependencies
$(DEPENDS_DIR)/%.$(DEPEND_EXT):	%.c
	$(PATTERN_DEP_CMD)

# C++ source dependencies 
$(DEPENDS_DIR)/%.$(DEPEND_EXT):	%.cpp
	$(PATTERN_DEP_CMD)

# Assembler source dependencies
$(DEPENDS_DIR)/%.$(DEPEND_EXT):	%.$(ASM_EXT)
	-$(DEP_QUIET)mkdir -p $(@D) $(REDIRECT_TO_NULL)
	@echo \(Dependencies $<\)
	$(DEP_QUIET)echo $(DEPENDS_DIR)/$*.$(OBJ_EXT) $(OBJ_DIR)/$*.$(OBJ_EXT): $(DEPENDS_DIR)/$*.$(DEPEND_EXT) $< > $@

##############################################################################
# Compiling rules section
##############################################################################

# C => object
$(OBJECTS_DIR)/%.$(OBJ_EXT):	%.c
	-$(CC_QUIET)mkdir -p $(@D) $(REDIRECT_TO_NULL)
	@echo Compiling $<
	$(CC_QUIET)$(call CC_FN,$@,$<,$(INCLUDES),$(CFLAGS))

# C++ => object
$(OBJECTS_DIR)/%.$(OBJ_EXT):	%.cpp
	-$(CC_QUIET)mkdir -p $(@D) $(REDIRECT_TO_NULL)
	@echo Compiling $<
	$(CC_QUIET)$(call CC_FN,$@,$<,$(INCLUDES),$(CFLAGS))

# assembler => object
$(OBJECTS_DIR)/%.$(OBJ_EXT):	%.$(ASM_EXT)
	-$(CC_QUIET)mkdir -p $(@D)
	@echo Assembling $<
	$(CC_QUIET)$(call AS_FN,$@,$<,$(ASFLAGS))

##############################################################################
# Target command rules(command block) section 
##############################################################################

# library build command
define BUILD_LIB_CMD
$(LIB_DIR)/$(LEAF).$(LIB_EXT): $($(LEAF)_OBJECTS:%=$(OBJECTS_DIR)/%); \
	echo Making $$@; \
	mkdir -p $(LIB_DIR) $(REDIRECT_TO_NULL); \
	$(RM) $$@; \
	$(MAKELIB) $$@ $$^
endef

# binary build command
define BUILD_BIN_CMD
$(BIN_DIR)/$(LEAF): $($(LEAF)_OBJECTS:%=$(OBJECTS_DIR)/%) $($(LEAF)_DEPLIBS:%=$(LIB_DIR)/%); \
	echo Making $$@; \
	mkdir -p $(BIN_DIR) $(REDIRECT_TO_NULL); \
	$(RM) $$@; \
	$(LINKER) $(LDFLAGS) -o $$@ $($(LEAF)_OBJECTS:%=$(OBJECTS_DIR)/%)  -Wl,--start-group $($(LEAF)_DEPLIBS:%=$(LIB_DIR)/%) $($(LEAF)_SYSLIBS) -Wl,--end-group; \
	chmod a+x $$@
endef

##############################################################################
# Default command rules section
##############################################################################

.PHONY: dummy default subdirs $(SUBDIRS:%=subdir-%)

ifneq (x$(LEAF_LIBS),x)
LEAF_LIB_LIST := $(LEAF_LIBS:%=$(LIB_DIR)/%.$(LIB_EXT))
endif

ifneq (x$(LEAF_BINS),x)
LEAF_BIN_LIST := $(LEAF_BINS:%=$(BIN_DIR)/%)
endif

ifneq (x$(LEAF_ASMS),x)
LEAF_ASM_LIST := $(LEAF_ASMS:%=$(BIN_DIR)/%)
endif

all: $(PREREQS) default 

# A rule to do nothing
dummy:

default:  subdirs $(LEAF_LIB_LIST) $(LEAF_BIN_LIST) 
	@#

subdirs: $(SUBDIRS:%=subdir-%)
	@#

$(SUBDIRS:%=subdir-%): dummy
	$(MAKE) -C $(subst subdir-,,$@)

##############################################################################
# Clean command rules section
##############################################################################

.PHONY: clean distclean

# make clean will reserve all the dependence files.
clean:
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) clean;)

# make distclean will remove all the outputed files(dependence/object/target).
distclean:
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) distclean;)

.PHONY: asm
asm:
	@mkdir -p $(ASM_DIR);
	@for file in $(LEAF_ASM_LIST); do \
		FILE=`basename $$file`;	\
		if [ -f $$file ]; then \
			echo -e "\E[1;33mDumping " $$FILE "to assembly......\E[0m";\
			$(OBJDUMP) -D -S -h -l $$file > $(ASM_DIR)/$$FILE.asm.$(CONF_VERSION);\
			echo $$file;\
		fi ;\
	done 
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) asm;)

#############################################################################
# help command rules section
#############################################################################

.PHONY: help 

help:
	@echo "Command for every directory: "
	@echo
	@echo "    make help"
	@echo "        print this help message"
	@echo
	@echo "    make debug_level=[0|1|2]"
	@echo "        0, default mode, print only the compiling warnings and errors"
	@echo "        1, print the detailed compiling message"
	@echo "        2, print the detailed compiling and dependence message"
	@echo
	@echo "    clean remove only the compiling objects and keep the dependence files"
	@echo "    make clean"
	@echo "        clean only its own direcory"
	@echo
	@echo "    distclean would remove both the compiled objects and dependence files"
	@echo "    make distclean"
	@echo "        distclean its own direcory"
	@echo
	@echo "Command only for top directory: "
	@echo 
	@echo "    make toolchain"
	@echo "        download and install the toolchain"
	@echo
	@echo "    make rootfs"
	@echo "        build the romfs.bin and it will be put in build directory"
	@echo
	@echo "    make dist"
	@echo "        build the firmware flashimage and it will be put in build/flashimage directory"
	@echo
	@echo "    make update/up"
	@echo "        update the whole codebase include product and libs"
	@echo
	@echo "    make status/st"
	@echo "        show the status of the whole codebase include product and libs"
	@echo
	@echo "Steps to release a firmware: "
	@echo "    make"
	@echo "    make rootfs"
	@echo "    make dist"
	@echo

##############################################################################
# Included dependency files
##############################################################################

# include dependence file
BASENAMES   := $(basename $(OBJECTS_ALL))
DEPENDS     := $(BASENAMES:%=$(DEPENDS_DIR)/%.$(DEPEND_EXT))
ifeq "$(findstring clean,$(MAKECMDGOALS))" ""
ifneq "$(strip $(DEPENDS))" ""
ifeq "$(NODEPENDS)" ""
ifeq "$(CLEAN)" ""
-include $(DEPENDS)
endif              # CLEAN
endif              # NODEPENDS
endif              # strip DEPENDS
endif              # findstring MAKECMDGOALS


endif              # RULES_MK_INCLUDED
