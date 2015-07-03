/*****************************************
 Copyright  2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   drive_defs.h
  @brief  Drive (loader) related definitions of mount point and device name on the target

  @author Sebastian Manciulea
  @date   2007-12-20

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/drive_defs.h,v 1.4 2008-03-21 19:48:33 smanciulea Exp $

 */

#ifndef _DRIVE_DEFS_H_
#define _DRIVE_DEFS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DRV_MAX_NAME	512

#ifdef __cplusplus
extern "C"
{
#endif
extern char CDROM_MOUNT_POINT[DRV_MAX_NAME];
extern char CDROM_DEVICE_NAME[DRV_MAX_NAME];

/**
	The function sets the CDROM_MOUNT_POINT and CDROM_DEVICE_NAME variables
	to values retrieved from the corresponding environment variables.

	@return 0  - in case of success
            -1 - in case of error (i.e. one of the environment variables was not defined)
 */
int get_drive_definitions(void);

/**
	The function checks the mount status of some device mounted under 'mount_point'

	@return 1  - device is mounted under the mount point
			0  - device is not mounted
			-1 - error
 */
int check_mount_status(char *mount_point);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVE_DEFS_H_ */
