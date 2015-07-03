/* Copyright (C) 2006, Alphanetworks, inc.
 * Author:  Tao Yu<tao_yu@alphanetworks.com>
 * $Header: /data/cvsroot/DMA/util/include/removable_device_info.h,v 1.1.2.7 2007-04-05 06:36:23 joshua Exp $
 * vim:cindent:ts=8:
 */
#ifndef __EXTERN_CP_CONTROL_INFO_H__
#define __EXTERN_CP_CONTROL_INFO_H__

#define RD_TRUE         (1)
#define RD_FALSE        (0)

#define RD_OK           (0)
#define RD_FAIL         (-1)

typedef enum {
	DMA_PERMISSION_DENY_IND=0,
	DMA_PERMISSION_ALLOW_IND,
}osd_permission_ind_t;

typedef struct{
	osd_permission_ind_t permission;
}osd_permission_ind_info;

typedef enum{
	EXCP_SETAVTRANSPORTURI_NOTIFY,
	EXCP_PLAY_NOTIFY,
	EXCP_STOP_NOTIFY,
}render_excp_control_notify_t;

typedef struct{
	render_excp_control_notify_t id;
	int servertype;
	char param[128];
}render_excp_notify_info;

#define EXCP_OSD2RENDERFIFO	"externcp_osd2renderfifo"
#define EXCP_RENDER2OSDFIFO	"externcp_render2osdfifo"

#endif
