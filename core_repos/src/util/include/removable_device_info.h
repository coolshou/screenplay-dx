/* Copyright (C) 2006, Alphanetworks, inc.
 * Author:  Tao Yu<tao_yu@alphanetworks.com>
 * $Header: /data/cvsroot/DMA/util/include/removable_device_info.h,v 1.1.2.7 2007-04-05 06:36:23 joshua Exp $
 * vim:cindent:ts=8:
 */
#ifndef __REMOVABLE_DEVICE_INFO_H__
#define __REMOVABLE_DEVICE_INFO_H__

#define RD_TRUE         (1)
#define RD_FALSE        (0)

#define RD_OK           (0)
#define RD_FAIL         (-1)

typedef enum _rd_type_s{
	RD_TYPE_USB,
	RD_TYPE_CARDREADER,
	RD_TYPE_DVD,
	RD_TYPE_UNKNOWN
}rd_type_t;

typedef enum _rd_cmd_s{
        RD_CMD_NONE,

        RD_USB_INIT_PLUG,

        RD_USB_PLUG,
        RD_USB_UNPLUG,

        RD_USB_INIT_MOUNT,

        RD_USB_MOUNT,
        RD_USB_UMOUNT
}rd_cmd_t;

typedef enum _rd_cmd_status_s{
        RD_CMD_STATUS_NONE,

        RD_USB_MOUNT_OK,
        RD_USB_MOUNT_FAILED,
        RD_USB_UMOUNT_OK,
        RD_USB_UMOUNT_FAILED,
        RD_USB_INIT_MOUNT_OK
}rd_cmd_status_t;

typedef enum _rd_status_s{
        RD_USB_NONE,

        RD_USB_PLUGED,
        RD_USB_UNPLUGED
}rd_status_t;

/* event fifo size 4K, you should be careful.*/
#define MAX_MOUNT_POINT_NUM 		8
#define MOUNT_POINT_PATH_LEN 		64

#define MAX_DEV_NODE_NUM 		8
#define DEV_NODE_PATH_LEN 		64

//FIXME, the max mount points is 8
typedef struct _removable_device_info_s{
	rd_type_t type; 				/* usb/cardreader etc. */
	rd_status_t status; 				/* insert/remove/pluged... */
        rd_cmd_t  cmd;
        rd_cmd_status_t cmd_status;
	char devnode[MAX_DEV_NODE_NUM][DEV_NODE_PATH_LEN];		/* max 8 dev nodes */
	char mntpath[MAX_MOUNT_POINT_NUM][MOUNT_POINT_PATH_LEN];	/* max 8 mount points */
}removable_device_info_t;

#define RD_S2PFIFO	"removable_device_s2pfifo"
#define RD_P2SFIFO	"removable_device_p2sfifo"

#endif
