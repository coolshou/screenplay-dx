/* Copyright (C) 2008, Alphanetworks, inc.
 * Author:  Johnson Zhang<johnson_zhang@cn.alphanetworks.com>
 */
#ifndef __LB_THUMB_H__
#define __LB_THUMB_H__

#define DEBUG_LB_THUMB(format,args...)       fprintf(stdout, format, ## args)
#define LB_THUMB_PLUGIN_TYPE_UNKWON		0
#define LB_THUMB_PLUGIN_TYPE_JPG		1
#define LB_THUMB_PLUGIN_TYPE_TIFF		2
#define LB_THUMB_PLUGIN_TYPE_MP3		3
#ifdef CONF_THUMB_MP4
#define LB_THUMB_PLUGIN_TYPE_MP4		4
#endif
#ifdef CONF_MUSIC_FLAC
#define LB_THUMB_PLUGIN_TYPE_FLAC		5
#endif
#define LB_THUMB_PLUGIN_TYPE_WMA		6

#define LB_THUMB_PLUGIN_TYPE_PNG		7
#define LB_THUMB_PLUGIN_TYPE_GIF		8

typedef enum _lb_thumb_status_s{
	LB_THUMB_EXIST,
	LB_THUMB_NO_EXIST,	
	LB_THUMB_ZERO_SIZE,
	LB_THUMB_EXTRACTING
}lb_thumb_status_t;

typedef struct _lb_thumb_plugin_s{
	int type;
	int (*extract)(char *src,char *dest, int w, int h);
	struct _lb_thumb_plugin_s *next;
}lb_thumb_plugin_t;

int lb_thumb_get_type(char * filepath);

void lb_thumb_plugin_factory(void);

lb_thumb_status_t lb_thumb_check(char *dest);

/* used for geting the thumbnail or album art */
int lb_thumb_extract(int type,char *src,char *dest, int w, int h);
#endif
