/* 
 * Copyright (C) 2006, Alphanetworks, inc.
 * Author: redsonic
 * History:
 *    Split the header file into securesoho_wireless.h securesoho_config.h
 *    securesoho_network.h secureoho_firmware.h
 * vim:cindent:ts=8:sw=8
 */
#ifndef __SECURESOHO_H__
#define __SECURESOHO_H__

//#include "Target.h"
#include "dma_common.h"

#define MSG_ERROR		0x00000001
#define MSG_DMACFG		0x00000002
#define MSG_SEURESOHO_WIRELESS	0x00000004

/**
 * The return code.
 */
/* Correct */
#define ESEC_NONE              0
/* error at open or copy files or other IO transcation */
#define ESEC_IO_ERROR          1
/* The requested value is not found in the database */
#define ESEC_VALUE_NOT_FOUND   2

#define MAX_LINE_LENGTH          512
#define MAX_LLENGTH		 512

#define    CONFIG_PICTURE_FIT      "PICFIT"
#define    CONFIG_BGIMAGE_FIT      "BGIMGFIT"
#define    DESKTOP_PATH 		"DESKTOP_PATH"
#define    THEME_PATH 		"THEME_PATH"



//#define    WEATHER_MAX_HISTORY  8
#define	   WEATHER_LOSE_CITYNAME "Unknown"
#define    WEATHER_CURRENTID    "WEATHER_FAVORITEID"
#define    WEATHER_BROWSEID     "WEATHER_BROWSEID"
#define    WEATHER_CITYNAME     "WEATHER_CITYNAME"

extern void udn16_maker(const char *token, char *udn_container);
extern void udn_maker(const char *token, char *udn_container);
extern void str_dec(char *s);
extern void str_inc(char *s);

extern int  ip_addr_exist(char *ifname);

extern int  decode_str(char *buf, char *key, char *value, const char *delim);
extern int  my_system(char *cmd, ...);
extern int  exist(const char *filename);
extern int  touch(const char *name);
extern int  ps_exist(const char *pidfile);
extern void init_signal_SIGCHLD(void);
extern int  get_child_return( int pid );
extern int  do_cmd(char *fmt, ...);
extern int  do_cmd_quiet(char *fmt, ...);
extern int  do_cmd_bg(char *fmt, ...);
extern int  set_pid_to_file(const char *pidfile);
extern int  kill_pidfile(char *file, int signal);
extern int  kill_pidfile_nowait(char *file, int signal);

extern int  do_mount(char *source, char *target, char *fstype, long flags,
		     int fakeIt, int mountall, int loop);
extern int  do_mkdir(char *dirname);
extern int  do_mkdirhier(char *dirname);
#ifdef __SIMPLEINIT__
extern int  do_mknod(char *name, char *type, char *major, char *minor);
extern long getul(char *num, int lower, int upper);
#endif				// __SIMPLEINIT__
extern int do_umount (char *target);
/*
 * This API is used to do factory default
 *   1) replace the config with factory default ('/conf_src/config_factory_default'->'/conf/config')
 *   2) remove wireless profile settings ('/conf/wireless_profile.xml')
 */
int  securesoho_factory_default(void);

void securesoho_wcn_status_led(int ok);
int  securesoho_save_cert_dir(char *i_dir, char *o_filename);

#ifdef __USE_CRC_CONFIG__
#define CONF_BLOCK 0
#define CONF_NONBLOCK 1
#define MY_SYSTEM my_system
#endif				// __USE_CRC_CONFIG__

extern  int     securesoho_copy(const char *src, const char *dst);
extern  int     securesoho_remove(char *file);

extern	int	DMA_ConfLoad(void);
extern	void	DMA_ConfSave(void);
void PRINTDEBUGMSG(unsigned int level, const char* fmt, ...);

int securesoho_dma_ex_lock();
int securesoho_dma_ex_unlock();
int securesoho_dma_ex_wait_lock();


/* Author: Jack_Hsu
 * This API is used to get cpu key's sha1sum
 *   1) the size of result must larger than 47
 *   2) return 0  : success
 *   3) return -1 : fail
 *   4) cpu key's sha1sum has 46 characters.
 */
int get_cpu_key_sha1sum(char *result);
/*
 * Usage:
 * 	Input: char * result, DIVX_DRM_KEY_LENGTH byte of memory buffer.
 * 	Output:char * result, the Divx DRM key with length DIVX_DRM_KEY_LENGTH
 * 	Return: -1 : fail.
 * 		>=0: bytes read. 
 *
 */
#define DIVX_DRM_KEY_LENGTH 32
int get_divx_drm_key(char *result);


#define SYSCONFIG_PATH 		CONF_RELATIVE_PATH_FOR_RESOURCES "/" CONF_SYSCONFIG_PATH
extern void sysconf_get_string(char *file, char *label, char *value, int value_len);



#include "securesoho_config.h"
#include "securesoho_firmware.h"
#include "securesoho_network2.h"
#include "securesoho_nic_helper.h"
#include "securesoho_wireless.h"
#include "securesoho_server.h"
#include "flash_monitor.h"
#include "config_access.h"
#include "securesoho_firmware.h"
#include "osd_key_event.h"
#endif				// __SECURESOHO_H__
