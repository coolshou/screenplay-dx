/* 
 * Copyright (C) 2006, Alphanetworks, inc.
 * $Header: /data/cvsroot/DMA/util/include/securesoho_firmware.h,v 1.1.2.6 2007-06-25 07:53:41 wchen Exp $
 * vim:cindent:ts=8:sw=8
 */
#ifndef __SECURESOHO_FIRMWARE_H__
#define __SECURESOHO_FIRMWARE_H__

struct FIRMWARE_OBJ {
	char pathname[255];
	char version[50];
	struct FIRMWARE_OBJ *next;
};

#define LENGTH_NAME_FIRMWARE               52
#define FIRMWARE_DIR                       "/mnt/"
#define MAGIC_NAME                         "REDSONIC"
#define OPEN_FAIL                          0
#define FIRM_FAIL                          1
#define VERSION_FAIL                       2
#define UPDATE_BEGIN                       3

typedef struct FIRMWARE_HEADER {
	union {
		struct {
			char magic_name[12];	/* magic name: REDSONIC */
			char version[LENGTH_NAME_FIRMWARE];/* 0~52 */
			int has_bootloader;		/* 53~56 */
			int has_kernel;			/* 57~60 */
			int has_rootfs;			/* 61~64 */
			int has_para0;			/* 65~68 */
			unsigned int size_bootloader;	/* 69~72 */
			unsigned int size_kernel;	/* 73~76 */
			unsigned int size_rootfs;	/* 77~80 */
			unsigned int size_para0;	/* 81~84 */
			int do_clean_para0;		/* 85~88 */
			unsigned long CRC;
		} s;
		char unused[256];
	} u;
} FIRMWARE_HEADER;

#define  m_magic_name          u.s.magic_name        
#define  m_version             u.s.version           
#define  m_has_bld             u.s.has_bootloader    
#define  m_has_kernel          u.s.has_kernel        
#define  m_has_rootfs          u.s.has_rootfs        
#define  m_has_para0           u.s.has_para0        
#define  m_size_bld            u.s.size_bootloader   
#define  m_size_kernel         u.s.size_kernel       
#define  m_size_rootfs         u.s.size_rootfs       
#define  m_size_para0          u.s.size_para0        
#define  m_clean_para0         u.s.do_clean_para0    
#define  m_crc                 u.s.CRC               

#define  m_unused              u.unused              

#define DEVICE_REGION_DATA_VERSION	'A'

typedef struct _device_region_data {
	unsigned char version;	/* version: 'A' char */
	unsigned char tv_mode;	/* ntsc, pal, secam */
	unsigned char region;	/* DUSA, WW, EU etc */
	unsigned char location;	/* USA, CA etc */
} device_region_data;

typedef enum {
	DTM_NTSC = 0,
	DTM_PAL,
	DTM_SECAM
} device_tv_mode;

typedef enum {
	DR_AMERICA = 0,
	DR_WW,
	DR_EU,
	DR_ASIA,
	DR_OCEANIA
} device_region;

/* device location will use MODEL_NUMBER for compatible issue 
 * model number will only check last 4 bits: nm & 0xf.
 * so the new added item should less than 16, 
 * or don't override the last 4 bits with old one, e.g.: MN_AUS 0x2E.
 */
typedef enum {
	MN_EU,
	MN_WW,
	MN_WWN,
	MN_WWP,
	MN_CA,
	MN_TW,		/* 5 */
	MN_USA = 15,
	MN_UNKNOWN = 32,
	MN_AUS = 46	/* 0x2E, the last 4 bits is 0xE */
} MODEL_NUMBER;

typedef enum {
	PN_DSM5210R,
	PN_DSM520 = 15
} PRODUCT_NUMBER;

typedef struct model_number {
	unsigned major:4;
	unsigned minor:4;
} model_number_t;

extern MODEL_NUMBER Conf_GetModelNumber(void);
extern int Conf_Firmware_Update_Get_Filename_USB(char *filename);

extern struct FIRMWARE_OBJ *securesoho_locate_firmware(int *cnt);
extern int  securesoho_update(char *pathname, int *result);
extern void free_firmware_obj(struct FIRMWARE_OBJ *firm);

extern int  DMA_GetNewestVersion(struct FIRMWARE_OBJ *pObj);

extern void set_fw_time(int t);
extern int  get_fw_time(void);
extern int securesoho_get_device_region_data(device_region_data *data);
extern int securesoho_set_device_region_data(device_region_data *data);


#endif				//__SECURESOHO_FIRMWARE_H__
