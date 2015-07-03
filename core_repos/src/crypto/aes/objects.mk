##############################################################################
# Copyright (C) alphanetworks 2001--2006 
# All Rights Reserved -- Company Confidential
# Author:  wills_yin@alphanetworks.com
# wmc aes top-level Makefile
##############################################################################

############################# global variables section #######################
COMMON_DEPLIBS       := libhal_player.a

############################# base rules section #############################
#
# CFLAGS 
#
CFLAGS +=  \
	-O3 -fomit-frame-pointer -Wcast-qual 

ifneq ($(ARCH), i386)
CFLAGS += -D__HW_AES__ $(SDK_LIB_FLAGS)
endif

#
# include search path 
#
INCLUDES := \
	-I. \
	-I./include 
	
ifneq ($(ARCH), i386)
INCLUDES += \
	-I$(MRUASDK)/MRUA_src\
	-I$(MRUASDK)/MRUA_src/dcc \
	-I$(MRUASDK)/MRUA_src/samples 
endif

#
# objects list  
#
OBJECTS := \
	aes.o           \
	aes_xcbc_mac.o  \
	aes_cbc.o
	
TEST_AES_TESTX_OBJ  := test_main_mac.o
TEST_AES_TEST_OBJ   := test_main.o
TEST_AES_CTR_OBJ    := test_aes_ctr.o
TEST_AES_ECB_OBJ    := test_aes_ecb.o
MCX_STORE_OBJ       := store.o
	
############################# feature rules section #############################
#
# OBJECTS
#
ASM-$(ARCH_ASM) = 1
ASM_X86 := $(ASM-i586)$(ASM-i686)
ifneq ($(strip $(ASM_X86)),)
OBJECTS += asm/aes-i586.o
endif

############################# target rules section ##############################
OBJECTS_ALL     :=       $(OBJECTS)

