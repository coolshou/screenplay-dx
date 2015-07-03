/* Copyright (C) 2006, Alphanetworks, inc.
 * Author:  Tao Yu<tao_yu@alphanetworks.com>
 * $Header: /data/cvsroot/DMA/util/include/mcx_event.h,v 1.1.2.8 2007-10-29 08:10:03 divers_dai Exp $
 * vim:cindent:ts=8:
 */
#ifndef __MCX_EVENT_H__
#define __MCX_EVENT_H__

/* event fifo size 4K, you should be careful.*/

typedef enum {
	SYS_MSG_SUPPRESS_SCREENSAVER = 100,
	SYS_MSG_DEBUG_DEVICEREBOOT,
	SYS_MSG_DEBUG_LAUNCHMEDIACENTER,
	SYS_MSG_STATE_PREPARE,
	SYS_MSG_UNKNOWN_INPUT_KEY,
	SYS_MSG_USER_CLOSE

} SYS_PLATFORM_EXT_MSG_ID;

typedef struct {
	int id;			/* event id */
	char param[128];	/* event param */
}mcx_event_t;

typedef struct {
	int state;		/* e.g.: prepare, connecting, disconnecting...  */
	int status;		/* e.g.: waiting, talking... in connecting state */
}mcx_state_t;

typedef enum
{
	mcx_INNER_STATE_IDLE=0,
	mcx_INNER_STATE_STARTING,
	mcx_INNER_STATE_CONNECTING,
	mcx_INNER_STATE_CONNECTED
}mcx_INNER_STATE;

#define MCX_S2PFIFO	"mcx_s2pfifo"
#define MCX_P2SFIFO	"mcx_p2sfifo"

#endif
