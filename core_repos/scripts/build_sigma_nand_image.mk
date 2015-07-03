# 254     0     130560 sigmblocka
# 254     1        512 sigmblockb
# 254     2        256 sigmblockc
# 254     3       3072 sigmblockd
# 254     4       3072 sigmblocke
# 254     5      16384 sigmblockf
# 254     6       8192 sigmblockg
# 254     7      30464 sigmblockh
# 254     8      30464 sigmblocki
# 254     9        128 sigmblockj
# 254    10        128 sigmblockk
# 254    11        128 sigmblockl

# The NAND flash total size
FLASH_TOTAL_SIZE        := ($(CONF_NAND_FLASH_SIZE)/1024/1024)
# Logical Block start
LOGICBLOCK_FLASH_BASE   := 0
# yamon: 0x00080000
YAMON_FLASH_BASE        := ($(CONF_MTD_BEFORE_YAMON_SIZE)/1024)
# linux kernel: 0xc0000
KERNEL1_FLASH_BASE		:= ($(YAMON_FLASH_BASE)+($(CONF_MTD_YAMON_SIZE)/1024))
# linux kernel2: 0x003c0000
KERNEL2_FLASH_BASE		:= ($(KERNEL1_FLASH_BASE)+($(CONF_PRIMARY_SYSTEM_SIZE)/1024))
# imat: 0x006c0000
IMAT_FLASH_BASE			:= ($(KERNEL2_FLASH_BASE)+($(CONF_PRIMARY_SYSTEM_SIZE)/1024))
# xmat: 0x016c0000
XMAT_FLASH_BASE			:= ($(IMAT_FLASH_BASE)+($(CONF_MTD_IMAT_SIZE)/1024))
# rootfs1: 0x01ec0000
ROOTFS1_FLASH_BASE		:= ($(XMAT_FLASH_BASE)+($(CONF_MTD_XMAT_SIZE)/1024))
# rootfs2: 0x078c0000
ROOTFS2_FLASH_BASE		:= ($(ROOTFS1_FLASH_BASE)+($(CONF_APP_ROMFS_SIZE)/1024))
# setting1: 0x0d2c0000
SETTING1_FLASH_BASE		:= ($(ROOTFS2_FLASH_BASE)+($(CONF_STORAGE_PARTITION_SIZE)/1024))

# Counting logical block offset from YAMON starting address
OFFSET_YAMON2KERNEL 	:= ($(KERNEL1_FLASH_BASE)-$(YAMON_FLASH_BASE))
OFFSET_YAMON2ROOTFS 	:= ($(ROOTFS1_FLASH_BASE)-$(YAMON_FLASH_BASE))
OFFSET_YAMON2IMAT 		:= ($(IMAT_FLASH_BASE)-$(YAMON_FLASH_BASE))
OFFSET_YAMON2XMAT 		:= ($(XMAT_FLASH_BASE)-$(YAMON_FLASH_BASE))
TOTAL_ROMFS_SIZE 		:= ($(ROOTFS2_FLASH_BASE)-$(YAMON_FLASH_BASE))
OFFSET_OKOK 			:= (($(ROOTFS2_FLASH_BASE)-$(YAMON_FLASH_BASE))*1024-4)

# Input file
#ZBOOT_FILE=zboot.bin
#YAMON_FILE=zbimage-yamon-2.13
#KERNEL_FILE=zbimage-linux-xload
#ROOTFS_FILE=romfs.bin
#IMAT_FILE=imat.bin
#XMAT_FILE=xmat.bin

# Nand flash image raw data
NAND_IMAGE_YK			:= $(TOP_BUILD_DIR)/flashimage_yk.img
NAND_IMAGE_YKR			:= $(TOP_BUILD_DIR)/flashimage_ykr.img

# Build raw data for nand flash programer
RAW_NAND_ZY				:= $(TOP_BUILD_DIR)/raw_zy.img
RAW_NAND_ZYK			:= $(TOP_BUILD_DIR)/raw_zyk.img
RAW_NAND_ZYKR			:= $(TOP_BUILD_DIR)/raw_zykr.img
RAW_NAND_GEN_PROG		:= $(SIGMA_SDK_SOURCE)/gennandraw/gen_nandv2_raw_img


# Building SATA 
SATA_FLASH_SIZE=16384
#0x0
SATA_ZBOOT2_FLASH_BASE=0
#0x100000
#SATA_YAMON_FLASH_BASH=1024
#0x1C0000
#SATA_KERNEL_FLASH_BASH=1792
SATA_KERNEL_FLASH_BASH=1024

# SATA image raw data
SATA_IMAGE_KERNEL=./flashimage_sata.img

CREATE_FIFO=./create_ff_fifo
FIFO=./sss

#all: create_fifo nand_raw_image
#	killall -9 $(CREATE_FIFO)

#create_fifo:
#	$(CREATE_FIFO) $(FIFO) &


#export RAW_ZY_SIZE=`stat --printf="%s" $(RAW_NAND_ZY)`
#export RAW_ZYK_SIZE=`stat --printf="%s" $(RAW_NAND_ZYK)`
export RAW_ZYKR_SIZE=`stat --printf="%s" $(RAW_NAND_ZYKR)`

nand_image: nand_raw_image
#	@echo "RAW_ZY_SIZE = $(RAW_ZY_SIZE) =================="
#	export SIZE=$(RAW_ZY_SIZE) && TOTAL_BLOCK=`expr $$SIZE / 2112 / 64` && printf "end = 0x%x \t" `expr $$TOTAL_BLOCK + 32` && printf "count = 0x%x\n" `expr $$TOTAL_BLOCK - 8` 
#	@echo "RAW_ZYK_SIZE = $(RAW_ZYK_SIZE) ================="
#	export SIZE=$(RAW_ZYK_SIZE) && TOTAL_BLOCK=`expr $$SIZE / 2112 / 64` && printf "end = 0x%x \t" `expr $$TOTAL_BLOCK + 32` && printf "count = 0x%x\n" `expr $$TOTAL_BLOCK - 8` 
	@echo "RAW_ZYKR_SIZE = $(RAW_ZYKR_SIZE) ================="
	export SIZE=$(RAW_ZYKR_SIZE) && TOTAL_BLOCK=`expr $$SIZE / 2112 / 64` && printf "end = 0x%x \t" `expr $$TOTAL_BLOCK + 32` && printf "count = 0x%x\n" `expr $$TOTAL_BLOCK - 8` 
	
nand_raw_image: raw_image_zkyr
	ls -l $(TOP_BUILD_DIR)/*.img

raw_image_zkyr: nand_image_with_romfs
	$(RAW_NAND_GEN_PROG) b0f=$(ZBOOT_FILE) df=$(NAND_IMAGE_YKR) nf=$(RAW_NAND_ZYKR) size=$$[$(FLASH_TOTAL_SIZE)] count=1000 percent=3 lb=4
	@echo "====================================================="
	@(SIZE=`stat --printf="%s" $(RAW_NAND_ZYKR)`; printf " raw image blocks = 0x%x (135168 bytes per block) \n" `expr $$SIZE / 135168`; printf "    end = 0x%x \n" `expr $$SIZE / 135168 + 32`; printf "    group block count = 0x%x \n" `expr $$SIZE / 135168 - 8`)
	@echo "====================================================="


nand_image_with_romfs:
	-rm -vf $(NAND_IMAGE_YKR)
	dd if=/dev/zero of=$(NAND_IMAGE_YKR) conv=notrunc bs=1k count=$$[$(TOTAL_ROMFS_SIZE)]
ifneq (x$(CONF_NAND_IMAGE_NO_YAMON), xy)
	dd if=$(YAMON_FILE) of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[0] bs=1k
endif
	dd if=$(KERNEL_FILE) of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[$(OFFSET_YAMON2KERNEL)] bs=1k
	dd if=$(IMAT_FILE) of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[$(OFFSET_YAMON2IMAT)] bs=1k
	dd if=$(XMAT_FILE) of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[$(OFFSET_YAMON2XMAT)] bs=1k
	dd if=$(ROOTFS_FILE) of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[$(OFFSET_YAMON2ROOTFS)] bs=1k
	echo "sisi" > /tmp/sisi; dd if=/tmp/sisi of=$(NAND_IMAGE_YKR) conv=notrunc seek=$$[$(OFFSET_OKOK)] bs=1 count=4

nand_image_clean:
	rm -vf $(NAND_IMAGE_ZBOOT_YAMON) $(NAND_IMAGE_KERNEL) $(SATA_IMAGE_KERNEL) $(NAND_IMAGE_ROOTFS)


