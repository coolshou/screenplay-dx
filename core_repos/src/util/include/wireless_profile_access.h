/* Copyright (C) 2006, Alphanetworks, inc.
 * Author:  Tao Yu<tao_yu@alphanetworks.com>
 * $Header: /data/cvsroot/DMA/util/include/wireless_profile_access.h,v 1.1.2.5 2006-08-30 04:54:17 ytao Exp $
 * vim:cindent:ts=8:
 */
#ifndef	__WIRELESS_PROFILE_ACCESS_H__
#define	__WIRELESS_PROFILE_ACCESS_H__

#include "securesoho_config.h"

typedef struct _wp_node_t{
	SecureSOHO_Wireless w;
	struct _wp_node_t *next;
}wp_node;

void	wireless_profile_init(wp_node **wplist, int *count);
void	wireless_profile_uinit(wp_node **wplist);
int	wireless_profile_save(wp_node **wplist);

int	wireless_profile_add(wp_node **wplist, wp_node *node);
int 	wireless_profile_remove(wp_node **wplist, wp_node *node);
int	wireless_profile_moveup(wp_node **wplist, wp_node *node);
int	wireless_profile_movedown(wp_node **wplist, wp_node *node);
#endif
