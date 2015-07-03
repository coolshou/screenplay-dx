/* Copyright (C) 2006, Alphanetworks, inc.
 * Author: wills_yin@alphanetworks.com 
 * $Header: /data/cvsroot/DMA/util/include/flash_monitor.h,v 1.1.2.2 2007-07-31 08:26:55 ken Exp $
 * vim:cindent:ts=8:sw=8
 */
#ifndef __FLASH_MONITOR_H__
#define __FLASH_MONITOR_H__

/*
 * Flash monitor module interface
 */

/* * Initialize the flash monitor internal data structre */
void flash_monitor_init( void );

/* 
 * Check the state of flash monitor and to decide whether write flash or not,
 * which can be called asynchronous or synchorous.
 */
void flash_monitor_checkforwrite( int is_async );

/* delete the monitor dir */
void flash_monitor_del_task(const char *mdir);

/* Use this API to add the flash monitor task, whole files in dir(mdir) will be
 * monitor, any changes of the files will be writen to dest file(ofile)
 */
void flash_monitor_add_task(const char *mdir, const char *ofile, const char *ofile_mirror);

/* * Release all the resource allocated during intialization. */
void flash_monitor_destroy( void );
	
#endif	// __FLASH_MONITOR_H__

